// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_WaitingReady.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;

UCLASS()
class MEGAJAM_2022_BOD_API UW_WaitingReady : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void Tick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* m_readyButton;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_readyText;

	UFUNCTION()
		void SetWidgetVisible(bool visible);

	UFUNCTION(BlueprintCallable)
		void SetOtherReady(bool ready);

	UFUNCTION()
		void SetHostReady(bool hostReady);
};
