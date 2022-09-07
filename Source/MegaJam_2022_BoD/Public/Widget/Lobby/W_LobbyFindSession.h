// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftLambda.h"
#include "W_LobbyFindSession.generated.h"

/**
 * 
 */
class UButton;
class UW_LobbyRoomList;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyFindSession : public UUserWidget
{
	GENERATED_BODY()
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
		void Click_FindSession();

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_FindSession;

public:
	UPROPERTY(EditAnywhere)
		FString m_findSessionURI;
	
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UW_LobbyRoomList> m_RoomListWidgetClass;
	
	UPROPERTY()
		UW_LobbyRoomList* m_RoomListWidget;

private:
	GameLiftLambda m_lambda;
	void FindSessionRequest();
	void OnFindSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
