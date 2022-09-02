// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/W_LoginSingUp.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UW_LoginSingUp::NativeConstruct()
{
	Super::NativeConstruct();

	//Case
	m_bLowerCase			= false;
	m_bUpperCase			= false;
	m_bSpeicalCase			= false;
	m_bNumberCase			= false;
	m_bLeastCharacterCase	= false;
	m_buserNameCase			= false;
	m_bemailCase			= false;
	m_bCanSingUp			= false;

	//SingUp Log
	m_singUpResultLog		= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_singUpResultLog")));

	//Case Log
	m_userNameLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_userNameLog")));
	m_emailLog				= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_emailLog")));
	m_lowerCaseLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_lowerCaseLog")));
	m_UpperCaseLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_UpperCaseLog")));
	m_SpeicalCaseLog		= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_SpeicalCaseLog")));
	m_NumberCaseLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_NumberCaseLog")));
	m_leastNumberCaseLog	= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_leastNumberCaseLog")));

	//EditBox
	m_username				= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_username")));
	m_email					= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_email")));
	m_password				= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_password")));

	//Button
	m_singUp				= Cast<UButton>(GetWidgetFromName(TEXT("m_singUp")));
	m_exit					= Cast<UButton>(GetWidgetFromName(TEXT("m_exit")));

	//TextBlock
	m_userNameLog->SetText(FText::FromString("User name cannot be blank"));
	m_emailLog->SetText(FText::FromString("Please include @ in your email address"));
	m_lowerCaseLog->SetText(FText::FromString("Password must contain a lower case letter"));
	m_UpperCaseLog->SetText(FText::FromString("Password must contain an upper case letter"));
	m_SpeicalCaseLog->SetText(FText::FromString("Password must contain a special character"));
	m_NumberCaseLog->SetText(FText::FromString("Password must contain a number"));
	m_leastNumberCaseLog->SetText(FText::FromString("Password must contain at least 8 characters"));

	//Commit
	if (m_username != nullptr)
	{
		m_username->OnTextCommitted.AddDynamic(this, &UW_LoginSingUp::Committed_UserName);
	}

	if (m_email != nullptr)
	{
		m_email->OnTextCommitted.AddDynamic(this, &UW_LoginSingUp::Committed_Email);
	}

	if (m_password != nullptr)
	{
		m_password->OnTextCommitted.AddDynamic(this, &UW_LoginSingUp::Committed_Password);
	}

	//OnClick Button
	if (m_singUp != nullptr)
	{
		m_singUp->OnClicked.AddDynamic(this, &UW_LoginSingUp::Click_SingUp);
	}

	if (m_exit != nullptr)
	{
		m_exit->OnClicked.AddDynamic(this, &UW_LoginSingUp::Click_Exit);
	}

}

void UW_LoginSingUp::Committed_UserName(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		FString Fmessage = FString(message.ToString());

		if (false == Fmessage.IsEmpty())
		{
			m_userNameLog->SetVisibility(ESlateVisibility::Hidden);
			m_buserNameCase = true;
		}
		else
		{
			m_userNameLog->SetVisibility(ESlateVisibility::Visible);
			m_buserNameCase = false;
		}

		CheckSingUp();
	}
}

void UW_LoginSingUp::Committed_Email(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		FString Fmessage = FString(message.ToString());

		int32 targetPos = INDEX_NONE;
		Fmessage.FindChar(TCHAR('@'), targetPos);

		if (targetPos != INDEX_NONE)
		{
			m_emailLog->SetVisibility(ESlateVisibility::Hidden);
			m_bemailCase = true;
		}
		else
		{
			m_emailLog->SetVisibility(ESlateVisibility::Visible);
			m_bemailCase = false;
		}

		CheckSingUp();
	}
}

void UW_LoginSingUp::Committed_Password(const FText& message, ETextCommit::Type commitType)
{
	bool lower = false;
	bool upper = false;
	bool special = false;
	bool number = false;

	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		FString Fmessage = FString(message.ToString());

		for (TCHAR word : Fmessage)
		{
			if (islower(word))
				lower = true;

			if (isupper(word))
				upper = true;

			if (isSpecial(word))
				special = true;

			if (isdigit(word))
				number = true;
		}

		m_bLowerCase = lower ? true : false;
		m_bUpperCase = upper ? true : false;
		m_bSpeicalCase = special ? true : false;
		m_bNumberCase = number ? true : false;
		m_bLeastCharacterCase = (Fmessage.Len() >= 8) ? true : false;

		CheckSingUp();
	}
}

void UW_LoginSingUp::Click_SingUp()
{
	m_singUpResultLog->SetVisibility(ESlateVisibility::Hidden);
	m_singUpResultLog->SetVisibility(ESlateVisibility::Visible);
}

void UW_LoginSingUp::Click_Exit()
{
	this->RemoveFromParent();
}

void UW_LoginSingUp::CheckSingUp()
{
	if (m_bLowerCase && m_bUpperCase && m_bSpeicalCase && m_bNumberCase && m_bLeastCharacterCase && m_buserNameCase && m_bemailCase)
	{
		m_bCanSingUp = true;
	}
	else
	{
		m_bCanSingUp = false;
	}

}

bool UW_LoginSingUp::isSpecial(int _C)
{
	if (21 <= _C && _C <= 47 ||
		58 <= _C && _C <= 64 ||
		91 <= _C && _C <= 96 ||
		123 <= _C && _C <= 126)
	{
		return true;
	}

	return false;
}
