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

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Questions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Answers;
	
	//sqrt of Question 
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Answer{0};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Question{"None Selected"};

	void SetRandQuestion();
	float CalcAnswer();
	//todo calculate answer

	void LeaveFight();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage{10.f};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float XPMultiplayer{10.f};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<int> InputArray;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int input{0};


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int QuestionCount{1};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int QuestionAnswered{0};
	
	UFUNCTION(BlueprintCallable)
	void AddInput(int i);
	
	UFUNCTION(BlueprintCallable)
	void SubmitPressed();

	UFUNCTION(BlueprintCallable)
	void RemoveLastElement();
	
	UFUNCTION(BlueprintCallable)
	void ResetInput();

	UFUNCTION(BlueprintCallable)
	void TimeOut();
	
	void calcInput();

	void PrintArray();

	UFUNCTION(BlueprintCallable)
	void Flee();
	
	UPROPERTY(EditAnywhere)
	bool BDebugMessages{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeSeconds{5};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeLeft{0};
};
