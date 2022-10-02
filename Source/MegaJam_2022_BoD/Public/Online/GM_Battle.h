// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Battle.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API AGM_Battle : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_Battle();

public:
	void GameLiftLocalTest();
};
