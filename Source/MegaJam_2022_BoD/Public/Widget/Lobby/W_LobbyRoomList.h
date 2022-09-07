// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftCallbackStructs.h"
#include "W_LobbyRoomList.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;
class UListView;
class UW_LobbyRoomInfo;
struct FGameSessionsInfo;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyRoomList : public UUserWidget
{
	GENERATED_BODY()
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_joinRoom;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_refresh;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_exit;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_roomListLog;

	UPROPERTY(Meta = (BindWidget))
		UListView* m_roomListView;

public:
	UFUNCTION()
		void Click_JoinRoom();

	UFUNCTION()
		void Click_Refresh();

	UFUNCTION()
		void Click_Exit();


public:
	UFUNCTION()
		void UpdateRoomList(TArray<FGameSessionsInfo>& infos);

	UFUNCTION()
		void SetClickLevel(FString level);

private:
	UPROPERTY()
		FString m_currentClickLevel;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UW_LobbyRoomInfo> m_RoomInfoClass;

	UPROPERTY()
		TArray<UW_LobbyRoomInfo*> m_SearchRoomInfos;
};
