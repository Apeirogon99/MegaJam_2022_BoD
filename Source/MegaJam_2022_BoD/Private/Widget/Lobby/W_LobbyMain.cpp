// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyMain.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UW_LobbyMain::NativeConstruct()
{
	Super::NativeConstruct();

	m_lobbyLog		= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_lobbyLog")));
	m_createSession = Cast<UButton>(GetWidgetFromName(TEXT("m_createSession")));
	m_joinSession	= Cast<UButton>(GetWidgetFromName(TEXT("m_joinSession")));
	m_quickMatch	= Cast<UButton>(GetWidgetFromName(TEXT("m_quickMatch")));
	m_logout		= Cast<UButton>(GetWidgetFromName(TEXT("m_logout")));

	if (m_createSession != nullptr)
	{
		m_createSession->OnClicked.AddDynamic(this, &UW_LobbyMain::Click_CreateSession);
	}

	if (m_joinSession != nullptr)
	{
		m_joinSession->OnClicked.AddDynamic(this, &UW_LobbyMain::Click_JoinSession);
	}

	if (m_quickMatch != nullptr)
	{
		m_quickMatch->OnClicked.AddDynamic(this, &UW_LobbyMain::Click_QuickMatch);
	}

	if (m_logout != nullptr)
	{
		m_logout->OnClicked.AddDynamic(this, &UW_LobbyMain::Click_Logout);
	}
}

void UW_LobbyMain::Click_CreateSession()
{
	m_lobbyLog->SetText(FText::FromString("CreateSession"));
}

void UW_LobbyMain::Click_JoinSession()
{
	m_lobbyLog->SetText(FText::FromString("JoinSession"));
}

void UW_LobbyMain::Click_QuickMatch()
{
	m_lobbyLog->SetText(FText::FromString("QuickMatch"));
}

void UW_LobbyMain::Click_Logout()
{
	m_lobbyLog->SetText(FText::FromString("Logout"));
}
