// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_WaitingRoom.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API APS_WaitingRoom : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_WaitingRoom();


public:
	UFUNCTION()
		bool GetReady();


private:
	UPROPERTY()
		bool m_ready;
};
