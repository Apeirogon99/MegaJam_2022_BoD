// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "W_WaitingChatInfo.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class MEGAJAM_2022_BOD_API UW_WaitingChatInfo : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

public:
	UFUNCTION(BlueprintCallable)
		void SetChatInfo(FString Name, FText ChatLog);

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_Name;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_ChatLog;

private:
	UPROPERTY()
		FString m_currentName;

	UPROPERTY()
		FText m_currentChatLog;
};
