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

// Called when the game starts or when spawned
void ADialogActor::BeginPlay()
{
	Super::BeginPlay();
	
	DialogTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADialogActor::OnBeginOverlap);
}

void ADialogActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (ARootCharacter* Player = Cast<ARootCharacter>(OtherActor)) {
		DisplayDialog();
	}
}

// Called every frame
void ADialogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

