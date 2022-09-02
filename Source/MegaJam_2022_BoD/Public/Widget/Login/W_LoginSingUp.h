// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_LoginSingUp.generated.h"

/**
 * 
 */

class UEditableTextBox;
class UTextBlock;
class UButton;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LoginSingUp : public UUserWidget
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
		void Committed_Email(const FText& message, ETextCommit::Type commitType);

	UFUNCTION()
		void Committed_Password(const FText& message, ETextCommit::Type commitType);

	UFUNCTION()
		void Click_SingUp();

	UFUNCTION()
		void Click_Exit();

protected:
	UFUNCTION()
		void CheckSingUp();

	UFUNCTION()
		bool isSpecial(int _C);

private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_singUpResultLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_userNameLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_emailLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_lowerCaseLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_UpperCaseLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_SpeicalCaseLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_NumberCaseLog;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_leastNumberCaseLog;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_username;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_email;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_password;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_singUp;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_exit;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Case")
		bool  m_bLowerCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Case")
		bool  m_bUpperCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Case")
		bool  m_bSpeicalCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Case")
		bool  m_bNumberCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Case")
		bool  m_bLeastCharacterCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Case")
		bool  m_buserNameCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Case")
		bool  m_bemailCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action")
		bool  m_bCanSingUp;
};
