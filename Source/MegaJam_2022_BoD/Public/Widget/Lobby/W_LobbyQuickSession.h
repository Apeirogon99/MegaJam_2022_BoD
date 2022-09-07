// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftLambda.h"
#include "W_LobbyQuickSession.generated.h"

/**
 * 
 */
class GameLiftLambda;
class UButton;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyQuickSession : public UUserWidget
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
		void Click_QuickSession();

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_quickSession;

public:
	UPROPERTY(EditAnywhere)
		FString m_quickSessionURI;

private:
	GameLiftLambda m_lambda;
	void QuickSessionRequest();
	void OnQuickSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
