// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_LoginSingIn.generated.h"

/**
 * 
 */

class UW_LoginSingUp;
class UTextBlock;
class UButton;
class UEditableTextBox;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LoginSingIn : public UUserWidget
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
		void Committed_UserName(const FText& message, ETextCommit::Type commitType);

	UFUNCTION()
		void Committed_Password(const FText& message, ETextCommit::Type commitType);

	UFUNCTION()
		void Click_AddToSingUp();

	UFUNCTION()
		void Click_SingIn();

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_singInResultLog;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_username;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_password;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_singUp;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_singIn;

private:
	UPROPERTY()
		FString m_currentUserName;

	UPROPERTY()
		FString m_currentPassword;
};
