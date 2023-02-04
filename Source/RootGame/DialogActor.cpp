// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogActor.h"

#include "Components/BoxComponent.h"

#include "RootCharacter.h"

// Sets default values
ADialogActor::ADialogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DialogTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DialogTrigger"));
	RootComponent = DialogTrigger;
	DialogTrigger->SetGenerateOverlapEvents(true);
}

void ADialogActor::Destroyed() {
	Super::Destroyed();
	UE_LOG(LogTemp, Warning, TEXT("DialogActor Destroyed"));
	if (OverlappedPlayer != nullptr && OverlappedPlayer->PlayerGameState == PlayerGameState::Paused) {
		OverlappedPlayer->PlayerGameState = PlayerGameState::Roaming;
		UE_LOG(LogTemp, Warning, TEXT("Player state set to Roaming from Dialog actor destroyed"));
	}
}

// Called when the game starts or when spawned
void ADialogActor::BeginPlay()
{
	Super::BeginPlay();
	
	DialogTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADialogActor::OnBeginOverlap);
}

void ADialogActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (ARootCharacter* Player = Cast<ARootCharacter>(OtherActor)) {
		UE_LOG(LogTemp, Warning, TEXT("Player overlapping with dialog actor. Setting player state to Paused."));
		OverlappedPlayer = Player;
		Player->PlayerGameState = PlayerGameState::Paused;
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		DisplayDialog();
	}
}

// Called every frame
void ADialogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

