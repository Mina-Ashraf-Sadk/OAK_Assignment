// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TeamSpawnPoint.generated.h"

class UArrowComponent;

UCLASS()
class OAK_TEST_API ACPP_TeamSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TeamSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Visual representation for the spawn point
	UStaticMeshComponent* SpawnPoint;
	UArrowComponent* Direction;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
