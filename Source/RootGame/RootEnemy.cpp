// Fill out your copyright notice in the Description page of Project Settings.


#include "RootEnemy.h"

#include <string>

// Sets default values
ARootEnemy::ARootEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARootEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARootEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARootEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARootEnemy::CalcAnswer()
{
}

void ARootEnemy::AddInput(int in)
{
	InputArray.Emplace(in);
	
	calcInput();
}

void ARootEnemy::SubmitPressed()
{
}

void ARootEnemy::ResetInput()
{
	input = 0;
	InputArray.Empty();
	calcInput();

	if (GEngine && BDebugMessages)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Input Reset"));
}

void ARootEnemy::calcInput()
{
	input = 0;
	for (int i{0}; i < InputArray.Num(); i++)
	{
		int ten = FMath::Pow(10, InputArray.Num() - i - 1);
		int output = ten * InputArray[i];
		input += output;
		if (GEngine && BDebugMessages)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, std::to_string(output).c_str());
	}
	
	PrintArray();
}

void ARootEnemy::PrintArray()
{
	std::string output{""};
	for (int i{0}; i < InputArray.Num(); i++)
	{
		output += std::to_string(InputArray[i]);
	}

	if (GEngine && BDebugMessages)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, output.c_str());
}

void ARootEnemy::RemoveLastElement()
{
	InputArray.RemoveAt(InputArray.Num() - 1);
	calcInput();

	if (GEngine && BDebugMessages)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Removed Last Element"));
}
