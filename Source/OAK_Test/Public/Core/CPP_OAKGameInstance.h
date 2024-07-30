// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Engine/GameInstance.h"
#include "CPP_OAKGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OAK_TEST_API UCPP_OAKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UCPP_OAKGameInstance();


protected:
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable)
	void JoinServer();

	UFUNCTION(BlueprintCallable)
	void CreateServer();

	//Leave current session and back to main menu
	UFUNCTION(BlueprintCallable)
	void LeaveCurrentSession();
	
	virtual void OnSessionCreated(FName SessionName, bool bWasSuccessful);
	virtual void OnSessionFound(bool bWasSuccessful) ;
	virtual void OnSessionJoined(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnSessionDestroyed(FName Name, bool bArg);

private:

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
