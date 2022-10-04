// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Battle.generated.h"

/**
 * 
 */

class APC_Battle;

UCLASS()
class MEGAJAM_2022_BOD_API AGM_Battle : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitSeamlessTravelPlayer(AController* newPlayer) override;
	AGM_Battle();

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnConnected(APC_Battle* controller);
	virtual void OnConnected_Implementation(APC_Battle* controller);

public:
	void TravelActorList();
	void GameLiftLocalTest();
	void GameLiftEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APC_Battle*> m_players;
};
