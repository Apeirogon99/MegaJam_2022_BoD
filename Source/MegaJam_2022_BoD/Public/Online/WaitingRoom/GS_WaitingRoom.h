// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GS_WaitingRoom.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API AGS_WaitingRoom : public AGameState
{
	GENERATED_BODY()
	
public:
	AGS_WaitingRoom();

public:
	UFUNCTION(BlueprintCallable)
		bool EnoughPlayers(int32 minPlayers, int32 maxPlayers, FString& description);

	UFUNCTION()
		bool GetAllReady(FString& description);

private:


};
