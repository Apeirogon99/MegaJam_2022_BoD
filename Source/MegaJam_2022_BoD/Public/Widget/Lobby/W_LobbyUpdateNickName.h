// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftLambda.h"
#include "W_LobbyUpdateNickName.generated.h"

/**
 * 
 */
class UEditableTextBox;
class UButton;
class UTextBlock;
class GameLiftLambda;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyUpdateNickName : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	UFUNCTION()
		void Committed_NickName(const FText& message, ETextCommit::Type commitType);

	UFUNCTION()
		void Click_Update();

public:
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_editNickname;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_nickNameLog;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_updateButton;

	UPROPERTY()
		FString m_nickname;


	UPROPERTY()
		FString m_NickNameURI;

private:
	GameLiftLambda m_lambda;
	void AwsURIInit();
	void UpdateNickNameRequest(FString nickname);
	void UpdateNickNameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
