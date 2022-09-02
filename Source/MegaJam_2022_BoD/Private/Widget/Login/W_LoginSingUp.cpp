// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/W_LoginSingUp.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

void UW_LoginSingUp::NativeConstruct()
{
	Super::NativeConstruct();

	m_bLowerCase			= false;
	m_bUpperCase			= false;
	m_bSpeicalCase			= false;
	m_bNumberCase			= false;
	m_bLeastCharacterCase	= false;

	//SingUp Log
	m_singUpLog				= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_singUpLog")));

	//Password Log
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

}

void UW_LoginSingUp::Committed_UserName(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{

	}
}

void UW_LoginSingUp::Committed_Email(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{

	}
}

void UW_LoginSingUp::Committed_Password(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		if (message.ToString().Len() >= 8)
		{
			m_bLeastCharacterCase = true;
		}
	}
}

void UW_LoginSingUp::Click_SingUp()
{
	if (m_bLowerCase && m_bUpperCase && m_bSpeicalCase && m_bNumberCase && m_bLeastCharacterCase)
	{

	}
}
