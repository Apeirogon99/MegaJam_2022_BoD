// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftCallbackStructs.h"
#include "Widget/Lobby/W_LobbyRoomList.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "W_LobbyRoomInfo.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;
class UW_LobbyRoomList;
struct FGameSessionsInfo;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyRoomInfo : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_room;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_host;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_curPlayer;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_maxPlayer;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_location;

public:
	UFUNCTION()
		void SetRoomListParent(UW_LobbyRoomList* owner);

	UFUNCTION()
		void Click_Room();

	UFUNCTION()
		void SetRoomInfo(FGameSessionsInfo info);

	UFUNCTION()
		FString GetLevel();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameSessionsInfo m_info;

	UPROPERTY()
		UW_LobbyRoomList* m_owner;
};
