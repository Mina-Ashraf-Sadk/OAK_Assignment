// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CPP_TeamSpawnPoint.h"

#include "Components/ArrowComponent.h"

// Sets default values
ACPP_TeamSpawnPoint::ACPP_TeamSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//static mesh and color
	UStaticMesh* SpawnPointMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UMaterialInterface* SpawnPointMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Main/Art/LevelPrototyping/Materials/MI_Solid_Blue"));

	//a static mesh to represent the spawn location
	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint->SetStaticMesh(SpawnPointMesh);
	SpawnPoint->SetMaterial(0, SpawnPointMaterial);
	

	//an arrow component to represent the spawn rotation
	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Direction->SetupAttachment(SpawnPoint);

	
}

// Called when the game starts or when spawned
void ACPP_TeamSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	//set this actor hidden in game
	SetActorHiddenInGame(true);
}

// Called every frame
void ACPP_TeamSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

