// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftLambda.h"
#include "W_LobbyCreateSession.generated.h"

/**
 * 
 */
class GameLiftLambda;
class UButton;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyCreateSession : public UUserWidget
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
		void Click_CreateSession();

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_createSession;

public:
	UPROPERTY(EditAnywhere)
		FString m_createSessionURI;

private:
	GameLiftLambda m_lambda;
	void CreateSessionRequest();
	void OnCreateSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
