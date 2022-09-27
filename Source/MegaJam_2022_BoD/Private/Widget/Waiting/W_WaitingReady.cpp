// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Waiting/W_WaitingReady.h"
#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Online/WaitingRoom/PS_WaitingRoom.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UW_WaitingReady::NativeConstruct()
{

	m_readyButton = Cast<UButton>(GetWidgetFromName(TEXT("m_readyButton")));
	m_readyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_readyText")));
}

void UW_WaitingReady::SetWidgetVisible(bool ready)
{
	ESlateVisibility currentVisible = GetVisibility();
	if (currentVisible == ESlateVisibility::Visible && ready)
		return;

	if (ready)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}

	SetOtherReady(ready);
}

void UW_WaitingReady::SetOtherReady(bool ready)
{
	FLinearColor ReadyColor;
	ReadyColor.Green;
	ReadyColor.A = 1.0f;

	FLinearColor NotReadyColor;
	NotReadyColor.Red;
	NotReadyColor.A = 1.0f;

	APS_WaitingRoom* playState = Cast<APS_WaitingRoom>(GetOwningPlayerState());

	if (playState)
	{
		if (!playState->m_host)
		{
			if (ready)
			{
				m_readyText->SetText(FText::FromString(TEXT("READY")));
				m_readyButton->SetColorAndOpacity(ReadyColor);
			}
			else
			{
				m_readyText->SetText(FText::FromString(TEXT("READY")));
				m_readyButton->SetColorAndOpacity(NotReadyColor);
			}
		}
	}
}

void UW_WaitingReady::SetHostReady(bool hostReady)
{
	FLinearColor ReadyColor;
	ReadyColor.Green;
	ReadyColor.A = 1.0f;

	FLinearColor NotReadyColor;
	NotReadyColor.Red;
	NotReadyColor.A = 1.0f;

	if (hostReady)
	{
		m_readyText->SetText(FText::FromString(TEXT("GAME START")));
		m_readyButton->SetColorAndOpacity(ReadyColor);
	}
	else
	{
		m_readyText->SetText(FText::FromString(TEXT("GAME START")));
		m_readyButton->SetColorAndOpacity(NotReadyColor);
	}
}
