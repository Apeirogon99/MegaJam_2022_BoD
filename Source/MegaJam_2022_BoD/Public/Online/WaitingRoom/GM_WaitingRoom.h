// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_WaitingRoom.generated.h"

/**
 * 
 */

class APlayerController;
class AC_WaitingRoom;
class APC_WaitingRoom;
class AGS_WaitingRoom;
class APS_WaitingRoom;

UCLASS()
class MEGAJAM_2022_BOD_API AGM_WaitingRoom : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_WaitingRoom();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		bool GameStart();

	UFUNCTION()
		void TestAWSStartServer();

public:
	//RPC

	UFUNCTION()
	void ProcessChatting(const FString& sender, const FText& message);

protected:
	UFUNCTION(BlueprintCallable)
		bool TravelLevel(const FString levelName, FString& Description);

public:
	UPROPERTY()
	TArray<APC_WaitingRoom*> m_players;

	UPROPERTY()
	FString m_travelLevelName;
};
