// Fill out your copyright notice in the Description page of Project Settings.


#include "DangerZone.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "RootCharacter.h"
#include "RootEnemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADangerZone::ADangerZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DangerZoneBox = CreateDefaultSubobject<UBoxComponent>(FName("Danger Zone"));

	DangerZoneBox->SetGenerateOverlapEvents(true);
	DangerZoneBox->OnComponentBeginOverlap.AddDynamic(this, &ADangerZone::OnBeginOverlap);
	DangerZoneBox->OnComponentEndOverlap.AddDynamic(this, &ADangerZone::OnEndOverlap);
}

// Called when the game starts or when spawned
void ADangerZone::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player && GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Danger Zone Cant find Player!"));
}

// Called every frame
void ADangerZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawZone();


	if (InsideDangerZone && Player && Player->PlayerGameState == PlayerGameState::Roaming)
	{
	}
}

void ADangerZone::DrawZone()
{
	DrawDebugBox(GetWorld(), GetActorLocation(), DangerZoneBox->GetScaledBoxExtent(), FColor::Green);
}

void ADangerZone::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<ARootCharacter>(OtherActor))
		return;
	
	HasEnteredFight = false;
	GetWorldTimerManager().SetTimer(timer, this, &ADangerZone::TrySpawn, spawnRate, true);
	
	auto player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(player)
		player->EnterGrassLoc = player->GetActorLocation();
	InsideDangerZone = true;
}

void ADangerZone::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(timer);

	InsideDangerZone = false;
	if(!HasEnteredFight)
	{
		//random check for enemy
		const int r = FMath::RandRange(0, SpawnChance);
		if (r == 1)
		{
			Player->PlayerGameState = PlayerGameState::Fighting;
			Player->EnterFight(); // triggers in BP

			auto type = EnemyTypes[FMath::RandRange(0,EnemyTypes.Num()-1)];
			ActiveEnemy = GetWorld()->SpawnActor<ARootEnemy>(type,GetActorLocation(),GetActorRotation());
			
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

			GetWorld()->GetTimerManager().ClearTimer(timer);
		}
	}
}

void ADangerZone::TrySpawn()
{
	if(EnemyTypes.Num() < 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Missing Enemy Type in DangerZone"));
		return;
	}
	if (Player && Player->PlayerGameState == PlayerGameState::Roaming && Player->CanEnterCombat)
	{
		//random check for enemy
		const int r = FMath::RandRange(0, SpawnChance);
		if (r == 1)
		{
			GetWorld()->GetTimerManager().ClearTimer(timer);
			HasEnteredFight = true;
			Player->PlayerGameState = PlayerGameState::Fighting;
			Player->EnterFight(); // triggers in BP

			auto type = EnemyTypes[FMath::RandRange(0,EnemyTypes.Num()-1)];
			ActiveEnemy = GetWorld()->SpawnActor<ARootEnemy>(type,GetActorLocation(),GetActorRotation());
			
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
			Player->CanEnterCombat = false;
		}
	}
}
