// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CPP_HealthComponent.h"
#include "Core/CPP_BattleGameMode.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCPP_HealthComponent::UCPP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	//get owner
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		
		//log the owner name
		UE_LOG(LogTemp,Warning, TEXT("Owner: %s"), *GetOwner()->GetName());
	}
}

void UCPP_HealthComponent::DamagePlayer(float Damage, APlayerController* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0)
	{
		Health = 0;

		//Notify GameMode (Blunder!! better be done with a delegate or in Blueprints Via an Interface. left it this way for simplicity)
		ACPP_BattleGameMode* GameMode = Cast<ACPP_BattleGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnPlayerKilled(DamageCauser, Cast<APlayerController>(OwnerCharacter->GetController()));
		}
	}
}

void UCPP_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCPP_HealthComponent, Health);
}


// Called when the game starts
void UCPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


