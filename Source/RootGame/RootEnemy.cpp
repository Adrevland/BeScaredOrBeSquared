// Fill out your copyright notice in the Description page of Project Settings.


#include "RootEnemy.h"

#include <string>
#include "RootCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	TimeLeft = TimeSeconds;
	auto player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player)
	{
		player->Health = player->MaxHealth;
	}
	SetRandQuestion();
	PlaySound(EnterCombatSound);
}

// Called every frame
void ARootEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeLeft -= DeltaTime;
	if (TimeLeft < 0)
	{
		TimeOut();
	}
}

// Called to bind functionality to input
void ARootEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARootEnemy::SetRandQuestion()
{
	TimeLeft = TimeSeconds;
	int r = FMath::RandRange(0, Questions.Num() - 1);
	Question = Questions[r];
	Answer = Answers[r];

	ResetInput();
}

float ARootEnemy::CalcAnswer()
{
	return Answer;
}

void ARootEnemy::LeaveFight()
{
	auto player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player)
	{
		player->PlayerGameState = PlayerGameState::Roaming;
		player->Health = player->MaxHealth;
		GetWorldTimerManager().SetTimer(player->combatTimer, player, &ARootCharacter::EnableEnterCombat, 2, false);
		player->LeavingFight();
	}
}

void ARootEnemy::AddInput(int in)
{
	InputArray.Emplace(in);
	if (InputArray.Num() > 2)
	{
		RemoveLastElement();
	}

	calcInput();
}

void ARootEnemy::SubmitPressed()
{
	auto player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (input == CalcAnswer())
	{
		SetRandQuestion();
		if (player)
			player->XP += 1 * XPMultiplayer;

		QuestionAnswered++;
		if (QuestionAnswered < QuestionCount)
		{
			SetRandQuestion();
		}
		else
		{
			LeaveFight();
			K2_DestroyActor();
		}
	}
	else
	{
		ResetInput();
		if (player)
		{
			player->Health -= Damage;
			PlaySound(DamageSound);
			player->XP -= 0.5 * XPMultiplayer;
		}


		if (player->Health <= 0)
		{
			player->XP -= 1 * XPMultiplayer;
			PlaySound(LooseSound);
			
			player->SetActorLocation(player->EnterGrassLoc);

			LeaveFight();
			K2_DestroyActor();
		}
	}
}

void ARootEnemy::ResetInput()
{
	input = 0;
	InputArray.Empty();
	calcInput();

	if (GEngine && BDebugMessages)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Input Reset"));
}

void ARootEnemy::TimeOut()
{
	auto player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player)
		player->Health -= Damage;
	PlaySound(DamageSound);
	player->XP -= 0.5 * XPMultiplayer;
	if (player->Health <= 0)
	{
		PlaySound(LooseSound);
		player->XP -= 1 * XPMultiplayer;

		player->SetActorLocation(player->EnterGrassLoc);

		LeaveFight();
		K2_DestroyActor();
	}
	else
	{
		player->XP -= 0.5 * XPMultiplayer;
	}
	TimeLeft = TimeSeconds;
	SetRandQuestion();
	ResetInput();
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

void ARootEnemy::Flee()
{
	PlaySound(FleeSound);
	auto player = Cast<ARootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player)
	{
		player->XP -= 1 * XPMultiplayer;
		player->SetActorLocation(player->EnterGrassLoc);
	}

	LeaveFight();
	K2_DestroyActor();
}

void ARootEnemy::PlaySound(USoundBase* sound)
{
	if (sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), sound, GetActorLocation(), GetActorRotation());
	}
}

void ARootEnemy::RemoveLastElement()
{
	InputArray.RemoveAt(InputArray.Num() - 1);
	calcInput();

	if (GEngine && BDebugMessages)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Removed Last Element"));
}
