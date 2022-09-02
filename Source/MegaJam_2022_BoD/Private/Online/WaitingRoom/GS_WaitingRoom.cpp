// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/GS_WaitingRoom.h"
#include "Online/WaitingRoom/PS_WaitingRoom.h"

AGS_WaitingRoom::AGS_WaitingRoom()
{
}

bool AGS_WaitingRoom::EnoughPlayers(int32 minPlayers, int32 maxPlayers, FString& description)
{
	if (minPlayers <= PlayerArray.Num() && PlayerArray.Num() >= maxPlayers )
	{
		description = FString::Printf(TEXT("Enough players"));

		return true;
	}

	description = TEXT("Not enough players");

	return false;
}

bool AGS_WaitingRoom::GetAllReady(FString& description)
{
	for (APlayerState* state : PlayerArray)
	{
		APS_WaitingRoom* waitPlayerState = Cast<APS_WaitingRoom>(state);
		if (false == waitPlayerState->GetReady())
		{
			description = FString::Printf(TEXT("Please check that all the players are ready"));

			return false;
		}
	}

	description = "All players are ready";

	return true;
}
