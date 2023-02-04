// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RootCharacter.generated.h"

UENUM(BlueprintType)
enum PlayerGameState
{
	Paused,
	Roaming,
	Fighting,
};
UENUM(BlueprintType)
enum PlayerAnimState
{
	Walk,
	Idle,
	Fight,
};

UCLASS()
class ROOTGAME_API ARootCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARootCharacter();
	UFUNCTION(BlueprintImplementableEvent)
		void EnterFight();
	UFUNCTION(BlueprintImplementableEvent)
		void LeavingFight();
	
	FVector WishDir = FVector::ZeroVector;
	float ForwardAmount = 0.f;
	float RotationAmount = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<PlayerAnimState> AnimState{PlayerAnimState::Walk};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<PlayerGameState> PlayerGameState{PlayerGameState::Roaming};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void EndTick(float DeltaTime);

	void UpdateRightInput(float Value);
	void UpdateForwardInput(float Value);

	FVector EnterGrassLoc{0};
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health{100.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth{100.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XP{0.f};
	
};
