// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPP_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged,int32,NewScore);
/**
 * 
 */
UCLASS()
class OAK_TEST_API ACPP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:


	void AddScore(int32 ScoreToAdd);
	

	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
private:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Score",meta=(AllowPrivateAccess="true"))
	int32 PlayerScore = 0;


};
