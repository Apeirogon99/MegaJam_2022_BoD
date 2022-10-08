// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameLiftServerSDK.h"
#include "GM_WaitingRoom.generated.h"

/**
 * 
 */

class APlayerController;
class AC_WaitingRoom;
class APC_WaitingRoom;
class AGS_WaitingRoom;
class APS_WaitingRoom;

class FGameLiftServerSDKModule;

UCLASS()
class MEGAJAM_2022_BOD_API AGM_WaitingRoom : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_WaitingRoom();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void TestAWSStartServer();

public:
	//RPC

	UFUNCTION()
	void ProcessChatting(const FString& sender, const FText& message);

	UFUNCTION(BlueprintCallable)
	void ProcessGameReady();

	UFUNCTION(BlueprintCallable)
	void ProcessStartGame();

	UFUNCTION(BlueprintCallable)
	void ProcessCancleGame();

	UFUNCTION(BlueprintCallable)
	void ProcessGameEnd();

	UFUNCTION(BlueprintNativeEvent)
	void EvnetGameEnd();
	virtual void EvnetGameEnd_Implementation();

protected:
	UFUNCTION()
	void UpdateHostPlayer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APC_WaitingRoom*> m_players;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APC_WaitingRoom* m_hostPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString m_travelLevelName;

	UPROPERTY()
	int32 m_hostIndex;

	UPROPERTY()
	bool m_startMatch;

public:
	FGameLiftServerSDKModule* gameLiftSdkModule;
	
	FString sessionId;
};
