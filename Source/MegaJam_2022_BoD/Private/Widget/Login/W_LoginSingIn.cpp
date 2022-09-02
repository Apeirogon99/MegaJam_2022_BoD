// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/W_LoginSingIn.h"
#include "Widget/Login/W_LoginSingUp.h"
#include "Online/Login/PC_Login.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

void UW_LoginSingIn::NativeConstruct()
{
	Super::NativeConstruct();

	//SingIn Log
	m_singInResultLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_singInResultLog")));

	//Button
	m_singIn = Cast<UButton>(GetWidgetFromName(TEXT("m_singIn")));
	m_singUp = Cast<UButton>(GetWidgetFromName(TEXT("m_singUp")));

	//EditBox
	m_username = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_username")));
	m_password = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_password")));

	//Commit
	if (m_username != nullptr)
	{
		m_username->OnTextCommitted.AddDynamic(this, &UW_LoginSingIn::Committed_UserName);
	}

	if (m_password != nullptr)
	{
		m_password->OnTextCommitted.AddDynamic(this, &UW_LoginSingIn::Committed_Password);
	}

	//OnClick Button
	if (m_singUp != nullptr)
	{
		m_singUp->OnClicked.AddDynamic(this, &UW_LoginSingIn::Click_AddToSingUp);
	}

	if (m_singIn != nullptr)
	{
		m_singIn->OnClicked.AddDynamic(this, &UW_LoginSingIn::Click_SingIn);
	}
}

void UW_LoginSingIn::Committed_UserName(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_currentUserName = message.ToString();
	}
}

void UW_LoginSingIn::Committed_Password(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_currentPassword = message.ToString();
	}
}

void UW_LoginSingIn::Click_AddToSingUp()
{
	APC_Login* playerController = Cast<APC_Login>(GetWorld()->GetFirstPlayerController());
	playerController->ShowWidget(WidgetType::LOGIN_SINGUP);
}

void UW_LoginSingIn::Click_SingIn()
{
}
