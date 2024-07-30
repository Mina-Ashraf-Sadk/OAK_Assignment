// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CPP_RedTeamSpawnPoint.h"

// Sets default values
ACPP_RedTeamSpawnPoint::ACPP_RedTeamSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	UMaterialInterface* SpawnPointMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Main/Art/LevelPrototyping/Materials/MI_Solid_Red"));
	SpawnPoint->SetMaterial(0,SpawnPointMaterial);
}

// Called when the game starts or when spawned
void ACPP_RedTeamSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_RedTeamSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

