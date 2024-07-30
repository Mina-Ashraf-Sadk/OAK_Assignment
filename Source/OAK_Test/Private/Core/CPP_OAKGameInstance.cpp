// Fill out your copyright notice in the Description page of Project Settings.


#include "Core\CPP_OAKGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UCPP_OAKGameInstance::UCPP_OAKGameInstance()
{
}

void UCPP_OAKGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
        SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCPP_OAKGameInstance::OnSessionCreated);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCPP_OAKGameInstance::OnSessionFound);
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UCPP_OAKGameInstance::OnSessionJoined);
        	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCPP_OAKGameInstance::OnSessionDestroyed);
        }
		
		
	}
	

}

void UCPP_OAKGameInstance::OnSessionCreated(FName SessionName, bool bWasSuccessful)
{

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete Success"));
		GetWorld()->ServerTravel("/Game/Main/Maps/BattleMap?listen");
	}
}

void UCPP_OAKGameInstance::OnSessionFound(bool bWasSuccessful)
{

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Search Success, NumResults: %d"), SessionSearch->SearchResults.Num());

		if (SessionSearch->SearchResults.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Joining Session: %s"), *SessionSearch->SearchResults[0].GetSessionIdStr());
			SessionInterface->JoinSession(0, FName("DevSession"), SessionSearch->SearchResults[0]);
		}
	}

}

void UCPP_OAKGameInstance::OnSessionJoined(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp,Warning,TEXT("Joined Session: %s"), *SessionSearch->SearchResults[0].GetSessionIdStr());

	//travel local player
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FString Address = "";
		SessionInterface->GetResolvedConnectString(SessionName,Address);
		UE_LOG(LogTemp,Warning,TEXT("Travelling to Address: %s"), *Address);
		if (Address != "") PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
	
}

void UCPP_OAKGameInstance::OnSessionDestroyed(FName Name, bool bArg)
{

	UE_LOG(LogTemp, Warning, TEXT("OnSessionDestroyed"));

	//travel to main menu
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->ClientTravel("/Game/Main/Maps/MainMenu?listen", ETravelType::TRAVEL_Absolute);
	}
}

void UCPP_OAKGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateSession"));

	FOnlineSessionSettings SessionSettings;
	
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bIsLANMatch = true;
	
	SessionInterface->CreateSession(0, FName("DevSession"), SessionSettings);
	
	
}

void UCPP_OAKGameInstance::LeaveCurrentSession()
{
	UE_LOG(LogTemp, Warning, TEXT("LeaveSession"));
	SessionInterface->DestroySession(FName("DevSession"));
	
}

void UCPP_OAKGameInstance::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinSession"));
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = true;
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set("SEARCH_PRESENCE", true, EOnlineComparisonOp::Equals);
	
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}
