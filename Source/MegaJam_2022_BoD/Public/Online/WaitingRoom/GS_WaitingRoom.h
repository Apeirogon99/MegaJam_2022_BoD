// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GS_WaitingRoom.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API AGS_WaitingRoom : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGS_WaitingRoom();

protected:
	virtual void Tick(float DeltaSeconds) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_isAllReady;

	float DebugTick = 1.0f;
};
