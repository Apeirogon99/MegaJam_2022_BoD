// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_WaitingChatting.generated.h"

/**
 * 
 */

class UEditableTextBox;
class UBorder;
class UListView;
class UW_WaitingChatInfo;

UCLASS()
class MEGAJAM_2022_BOD_API UW_WaitingChatting : public UUserWidget
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
	void UpdateChatting(const FString& name, const FText& chatLog);

	UFUNCTION()
		void FocusChatting();

	UFUNCTION()
		void Committed_Chatting(const FText& message, ETextCommit::Type commitType);

public:
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_ChattingBox;

	UPROPERTY(Meta = (BindWidget))
		UBorder* m_border;

	UPROPERTY(Meta = (BindWidget))
		UListView* m_ChatListView;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UW_WaitingChatInfo> m_ChatInfoClass;
};
