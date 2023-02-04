// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DangerZone.generated.h"

UCLASS()
class ROOTGAME_API ADangerZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADangerZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool InsideDangerZone{false};
	
	class ARootCharacter* Player{nullptr};
	
	FTimerHandle timer;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UBoxComponent* DangerZoneBox = nullptr;

	void DrawZone();
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//1 in x chance
	UPROPERTY(EditAnywhere)
	int SpawnChance{10};
	UPROPERTY(EditAnywhere)
	float spawnRate{1.f};
	
	UPROPERTY(EditAnywhere)
	int DifficultyLevel{0};

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ARootEnemy>> EnemyTypes;

	void TrySpawn();

	bool HasEnteredFight{false};
	
	class ARootEnemy* ActiveEnemy{nullptr};
};
