// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RootEnemy.generated.h"

UCLASS()
class ROOTGAME_API ARootEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARootEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere)
	FString Question{"Insert Question?"};
	
	//sqrt of Question 
	UPROPERTY(EditAnywhere)
	int Number{1};
	
	void CalcAnswer();
	//todo calculate answer
	float Answer{0};
};
