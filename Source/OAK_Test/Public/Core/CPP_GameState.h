// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CPP_GameState.generated.h"


//enum for game phase
UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	WaitingForPlayers,
	Prepare,
	Battle
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EGamePhase, NewGamePhase);

/**
 * 
 */
UCLASS()
class OAK_TEST_API ACPP_GameState : public AGameStateBase
{
	GENERATED_BODY()
public:

	ACPP_GameState();
	
	void SetGamePhase(EGamePhase NewGamePhase);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable)
	FOnPhaseChanged OnPhaseChanged;
	
private:

	UPROPERTY(ReplicatedUsing = OnRep_Phase,EditAnywhere,BlueprintReadOnly,Category="Score",meta=(AllowPrivateAccess="true"))
	EGamePhase GamePhase = EGamePhase::WaitingForPlayers;

	UFUNCTION()
	void OnRep_Phase();
};
