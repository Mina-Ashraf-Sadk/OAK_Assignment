// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPP_GameModeSettingsDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class OAK_TEST_API UCPP_GameModeSettingsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//max number of players
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	int32 MaxPlayers = 2;

	//Max Number of rounds (after that the match is over)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	int32 MaxRounds = 3;

	//duration of the match in Seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	float MatchDuration = 60.0f;

	//pre-round Duration in Seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	float PreRoundDuration = 3.0f;

	//Character Class for the Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	TSubclassOf<ACharacter> PlayerCharacter;
	
};
