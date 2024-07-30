// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PlayerControllerInterface.h"
#include "CPP_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OAK_TEST_API ACPP_PlayerController : public APlayerController , public IPlayerControllerInterface
{
	GENERATED_BODY()
	
};
