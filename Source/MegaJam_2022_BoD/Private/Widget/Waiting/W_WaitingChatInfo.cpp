// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Waiting/W_WaitingChatInfo.h"
#include <Components/TextBlock.h>

void UW_WaitingChatInfo::NativeConstruct()
{
	Super::NativeConstruct();

	m_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_Name")));
	m_ChatLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_ChatLog")));
}

void UW_WaitingChatInfo::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UW_WaitingChatInfo* pItemData = Cast<UW_WaitingChatInfo>(ListItemObject);

	m_Name->SetText(FText::FromString(pItemData->m_currentName));
	m_ChatLog->SetText(pItemData->m_currentChatLog);
}

void UW_WaitingChatInfo::NativeOnItemSelectionChanged(bool bIsSelected)
{
}

void UW_WaitingChatInfo::SetChatInfo(FString Name, FText ChatLog)
{
	m_currentName = Name;
	m_currentChatLog = ChatLog;
}
