// Fill out your copyright notice in the Description page of Project Settings.


#include "Core\CPP_BattleGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/CPP_BlueTeamSpawnPoint.h"
#include "Actors/CPP_RedTeamSpawnPoint.h"
#include "Core/CPP_GameState.h"
#include "Core/CPP_PlayerState.h"
#include "Interfaces/PlayerControllerInterface.h"
#include "OAK_Test/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

ACPP_BattleGameMode::ACPP_BattleGameMode()
{
	if (!GameModeSettings)
	{
		GameModeSettings = GetMutableDefault<UCPP_GameModeSettingsDataAsset>();
		if (!GameModeSettings)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to initialize GameModeSettings"));
		}
	}

}

void ACPP_BattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Fetch and Store Spawn Points
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_RedTeamSpawnPoint::StaticClass(), RedTeamSpawnPoints);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_BlueTeamSpawnPoint::StaticClass(), BlueTeamSpawnPoints);

	GameState = Cast<ACPP_GameState>(GetWorld()->GetGameState());

	UpdateGamePhaseUI(EGamePhase::WaitingForPlayers);

}

void ACPP_BattleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	//register the new player
	UE_LOG(LogTemp,Warning, TEXT("PostLogin: %s"), *NewPlayer->GetName());
	Players.AddUnique(NewPlayer);

	//Assign New Player to Team
	if (BlueTeam.Num() <= RedTeam.Num())
	{
		BlueTeam.AddUnique(NewPlayer);
	}
	else
	{
		RedTeam.AddUnique(NewPlayer);
	}
	
	//Check if all players have joined and start the match
	if (Players.Num() == GameModeSettings->MaxPlayers)
	{
		UE_LOG(LogTemp,Warning, TEXT("All Players Joined"));
		OnGameStarted.Broadcast(GameModeSettings->MatchDuration);
		StartRound();
	}
}

void ACPP_BattleGameMode::StartRound()
{
	UpdateGamePhaseUI(EGamePhase::Prepare);

	//spawn players
	for (auto Player : Players)
	{
		RespawnPlayer(Player);
	}
	
	//Begin Battle after a certain amount of time
	GetWorld()->GetTimerManager().SetTimer(StartBattleTimer, this, &ACPP_BattleGameMode::StartBattle, GameModeSettings->PreRoundDuration, false);
}

void ACPP_BattleGameMode::EndGame()
{
	//Should add the logic where the player with the most health wins
	StartRound();
}

void ACPP_BattleGameMode::StartBattle()
{
	UpdateGamePhaseUI(EGamePhase::Battle);

	//fire a dispatcher (to open player's bases) 
	OnBattleStarted.Broadcast();

	UE_LOG(LogTemp,Warning, TEXT("Battle Started"));
	GetWorld()->GetTimerManager().SetTimer(EndGameTimerHandle, this, &ACPP_BattleGameMode::EndGame, GameModeSettings->MatchDuration, false);

}

void ACPP_BattleGameMode::EndMatch() const
{
	if (BlueTeamScore > RedTeamScore)
	{
		UE_LOG(LogTemp,Warning, TEXT("Blue Team Won"));

		HandleEndGameForTeamMembers(BlueTeam, true);
		HandleEndGameForTeamMembers(RedTeam, false);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("Red Team Won"));

		HandleEndGameForTeamMembers(RedTeam, true);
		HandleEndGameForTeamMembers(BlueTeam, false);
	}
}

void ACPP_BattleGameMode::OnPlayerKilled(APlayerController* Killer, APlayerController* Killed)
{
	if (BlueTeam.Contains(Killed))
	{
		RedTeamScore++;
	}
	else
	{
		BlueTeamScore++;
	}

	if (BlueTeamScore == GameModeSettings->MaxRounds || RedTeamScore == GameModeSettings->MaxRounds)
	{
		EndMatch();
		return;
	}
	
	EndGameTimerHandle.Invalidate();

	OnBattleEnded.Broadcast();
	OnTeamsScoreUpdated.Broadcast(BlueTeamScore, RedTeamScore);
	StartRound();
}

void ACPP_BattleGameMode::RespawnPlayer(APlayerController* Player)
{
	if (Player->GetPawn())
	{
		Player->GetPawn()->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FTransform SpawnTransform;
	if (BlueTeam.Contains(Player))
	{
		SpawnTransform = BlueTeamSpawnPoints[FMath::RandRange(0, BlueTeamSpawnPoints.Num() - 1)]->GetActorTransform();
	}
	else
	{
		SpawnTransform = RedTeamSpawnPoints[FMath::RandRange(0, RedTeamSpawnPoints.Num() - 1)]->GetActorTransform();
	}

	ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(GameModeSettings->PlayerCharacter, SpawnTransform, SpawnParams);


	if (NewCharacter)
	{
		Player->Possess(NewCharacter);
		
		UE_LOG(LogTemp, Warning, TEXT("Player Respawned: %s"), *Player->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to respawn player: %s"), *Player->GetName());
	}
}

void ACPP_BattleGameMode::UpdateGamePhaseUI(const EGamePhase NewGamePhase) const
{
	if (GameState)
	{
		GameState->SetGamePhase(NewGamePhase);
	}
}

void ACPP_BattleGameMode::HandleEndGameForTeamMembers(const TArray<APlayerController*>& TeamMembers, bool bIsWinner)
{
	for (auto Player : TeamMembers)
	{
		IPlayerControllerInterface* PlayerController = Cast<IPlayerControllerInterface>(Player);
		if (PlayerController)
		{
			PlayerController->Execute_DisplayEndGameScreen(Player,bIsWinner);
		}
	}
}

