// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_GameState.h"
#include "GameFramework/GameMode.h"
#include "Data/CPP_GameModeSettingsDataAsset.h"
#include "CPP_BattleGameMode.generated.h"

class ACPP_GameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartGameDelegate, int32, GameTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartBattleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndBattleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateTeamsScoreDelegate, int32, BlueTeamScore, int32, RedTeamScore);

/**
 * 
 */
UCLASS()
class OAK_TEST_API ACPP_BattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPP_BattleGameMode();

	//Bound On BP_BaseGate
	UPROPERTY(BlueprintAssignable)
	FStartBattleDelegate OnBattleStarted;

	//Bound On BP_BaseGate
	UPROPERTY(BlueprintAssignable)
	FEndBattleDelegate OnBattleEnded;

	//bound on the PlayerController to display Game Time
	UPROPERTY(BlueprintAssignable)
	FStartGameDelegate OnGameStarted;

	//bound on the PlayerController to display Team Scores
	UPROPERTY(BlueprintAssignable)
	FUpdateTeamsScoreDelegate OnTeamsScoreUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime Variables")
	TArray<APlayerController*> Players;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime Variables")
	TArray<APlayerController*> BlueTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runtime Variables")
	TArray<APlayerController*> RedTeam;

	//Called from the Health Component when a player dies
	void OnPlayerKilled(APlayerController* Killer, APlayerController* Killed);

protected:
	
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	//Sets the GameMode Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "GameMode Settings",meta = (AllowPrivateAccess = "true"))
	UCPP_GameModeSettingsDataAsset* GameModeSettings;
	
private:
	
	//Game Cycle Functions
	void StartBattle();
	void StartRound();
	void EndGame();
	void EndMatch() const;

	//Helper Functions
	void RespawnPlayer(APlayerController* Player);
	void UpdateGamePhaseUI(EGamePhase NewGamePhase) const;
	static void HandleEndGameForTeamMembers(const TArray<APlayerController*>& TeamMembers,bool bIsWinner);
	
	FTimerHandle EndGameTimerHandle;
	FTimerHandle StartBattleTimer;

	//SpawnPoints are collected at the beginning of the game (BeginPlay)
	TArray<AActor*> BlueTeamSpawnPoints;
	TArray<AActor*> RedTeamSpawnPoints;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams Scores", meta = (AllowPrivateAccess = "true"))
	int32 BlueTeamScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams Scores", meta = (AllowPrivateAccess = "true"))
	int32 RedTeamScore = 0;

	//game state reference
	ACPP_GameState* GameState;
};
