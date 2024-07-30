// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_TeamSpawnPoint.h"
#include "GameFramework/Actor.h"
#include "CPP_BlueTeamSpawnPoint.generated.h"


UCLASS()
class OAK_TEST_API ACPP_BlueTeamSpawnPoint : public ACPP_TeamSpawnPoint
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_BlueTeamSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
