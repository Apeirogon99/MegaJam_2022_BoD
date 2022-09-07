// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftLambda.h"
#include "W_JoinSession.generated.h"

/**
 * 
 */
class GameLiftLambda;
class UEditableTextBox;
class UButton;

UCLASS()
class MEGAJAM_2022_BOD_API UW_JoinSession : public UUserWidget
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
		void Click_JoinSession();

	UFUNCTION()
		void Committed_SessionCode(const FText& message, ETextCommit::Type commitType);

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_joinSession;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_joinSessionCode;

public:
	UPROPERTY(EditAnywhere)
		FString m_joinSessionURI;

	UPROPERTY(EditAnywhere)
		FString m_sessionCode;

private:
	GameLiftLambda m_lambda;
	void JoinSessionRequest(FString code);
	void OnJoinSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
