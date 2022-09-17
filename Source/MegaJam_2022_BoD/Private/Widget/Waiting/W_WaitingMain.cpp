// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Waiting/W_WaitingMain.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UW_WaitingMain::NativeConstruct()
{
	Super::NativeConstruct();

	m_ReadyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_ReadyText")));

	m_Ready = Cast<UButton>(GetWidgetFromName(TEXT("m_Ready")));
	m_isReady = false;

	m_ReadyText->SetText(FText::FromString(TEXT("READY")));

	if (m_Ready != nullptr)
	{
		m_Ready->OnClicked.AddDynamic(this, &UW_WaitingMain::Click_Ready);
	}
}

void UW_WaitingMain::Click_Ready()
{
	if (m_isReady)
	{
		m_isReady = false;
		m_ReadyText->SetText(FText::FromString(TEXT("READY")));
	}
	else
	{
		m_isReady = true;
		m_ReadyText->SetText(FText::FromString(TEXT("CANCLE")));
	}
}
