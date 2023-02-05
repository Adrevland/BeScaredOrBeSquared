// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogActor.generated.h"

UCLASS()
class ROOTGAME_API ADialogActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Multiline = true))
	FString DialogText = "";

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DialogTrigger = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayDialog();

	class ARootCharacter* OverlappedPlayer = nullptr;

	virtual void Destroyed() override;

	bool UsedDialog = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
