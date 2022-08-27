// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MegaJam_2022_BoDGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API AMegaJam_2022_BoDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMegaJam_2022_BoDGameModeBase();
	
public:
	void GameLiftLocalTest();
};
