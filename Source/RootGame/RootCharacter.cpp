// Fill out your copyright notice in the Description page of Project Settings.


#include "RootCharacter.h"

// Sets default values
ARootCharacter::ARootCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARootCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void ARootCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerGameState == Roaming)
	{
		AddMovementInput(WishDir);
	}
	
	EndTick(DeltaTime);
}

void ARootCharacter::EndTick(float DeltaTime) {
	WishDir = FVector::ZeroVector;
}

void ARootCharacter::UpdateRightInput(float Value) {
	WishDir += FVector::RightVector * Value;
}

void ARootCharacter::UpdateForwardInput(float Value) {
	WishDir += FVector::ForwardVector * Value;
}

// Called to bind functionality to input
void ARootCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ARootCharacter::UpdateForwardInput);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ARootCharacter::UpdateRightInput);
}

