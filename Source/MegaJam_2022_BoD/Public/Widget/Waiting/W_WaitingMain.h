// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_WaitingMain.generated.h"

/**
 * 
 */

class UW_WaitingChatting;

UCLASS()
class MEGAJAM_2022_BOD_API UW_WaitingMain : public UUserWidget
{
	GENERATED_BODY()

protected:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	UFUNCTION(BlueprintCallable)
		void OpenChattingBox();

public:
	UPROPERTY(Meta = (BindWidget))
		UW_WaitingChatting* m_chatting;

};
