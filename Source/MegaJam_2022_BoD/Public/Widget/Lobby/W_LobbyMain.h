// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_LobbyMain.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LobbyMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

protected:
	UFUNCTION()
		void Click_CreateSession();

	UFUNCTION()
		void Click_JoinSession();

	UFUNCTION()
		void Click_QuickMatch();

	UFUNCTION()
		void Click_Logout();

private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_lobbyLog;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_createSession;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_joinSession;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_quickMatch;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_logout;
};
