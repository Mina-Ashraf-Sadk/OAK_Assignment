// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CPP_GameState.h"

#include "Net/UnrealNetwork.h"

ACPP_GameState::ACPP_GameState()
{
	bReplicates = true;
}

void ACPP_GameState::SetGamePhase(EGamePhase NewGamePhase)
{
	GamePhase = NewGamePhase;
	OnPhaseChanged.Broadcast(NewGamePhase);
}

void ACPP_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_GameState,GamePhase);
}

void ACPP_GameState::OnRep_Phase()
{
	OnPhaseChanged.Broadcast(GamePhase);

}
