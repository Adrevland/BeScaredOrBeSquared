// Fill out your copyright notice in the Description page of Project Settings.


#include "RootEnemy.h"

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

