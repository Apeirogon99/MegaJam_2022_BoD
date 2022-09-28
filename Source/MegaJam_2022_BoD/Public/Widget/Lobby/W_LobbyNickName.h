// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLift/GameLiftLambda.h"
#include "W_LobbyNickName.generated.h"

/**
 * 
 */

class UW_LobbyUpdateNickName;
class UTextBlock;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyNickName : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_nicknameText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_nickNameLog;

	UPROPERTY()
		FString m_NickNameURI;

	UFUNCTION(BlueprintCallable)
		void GetNickName();

	UFUNCTION()
		void UpdateNickName(FString nickname);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UW_LobbyUpdateNickName> m_UpdateWidgetClass;

private:
	GameLiftLambda m_lambda;
	void AwsURIInit();
	void GetNickNameRequest();
	void GetNickNameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
