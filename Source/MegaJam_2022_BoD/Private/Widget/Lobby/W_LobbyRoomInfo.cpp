// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyRoomInfo.h"
#include "GameLift/GameLiftUtils.h"
#include "GameLift/GameLiftCallbackStructs.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/Border.h>

void UW_LobbyRoomInfo::NativeConstruct()
{
	Super::NativeConstruct();

	m_host = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_host")));
	m_curPlayer = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_curPlayer")));
	m_maxPlayer = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_maxPlayer")));
	m_location = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_location")));

	m_border = Cast<UBorder>(GetWidgetFromName(TEXT("m_border")));
}

void UW_LobbyRoomInfo::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UW_LobbyRoomInfo* pItemData = Cast<UW_LobbyRoomInfo>(ListItemObject);

	m_border->SetBrushColor(FLinearColor(0.0f, 0.3f, 1.0f, 0.0f));

	m_curPlayer->SetText(FText::FromString(FString::FromInt(pItemData->m_info.m_CurrentPlayerSessionCount)));
	m_maxPlayer->SetText(FText::FromString(FString::FromInt(pItemData->m_info.m_MaximumPlayerSessionCount)));
	m_location->SetText(FText::FromString(GameLiftUtils::LocationToString(pItemData->m_info.m_Location)));

	SetRoomListParent(pItemData->m_owner);
	SetRoomInfo(pItemData->m_info);
}

void UW_LobbyRoomInfo::NativeOnItemSelectionChanged(bool bIsSelected)
{
	UE_LOG(LogTemp, Log, TEXT("Click room"));
	m_border->SetBrushColor(FLinearColor(0.0f, 0.3f, 1.0f, 0.5f * (float)bIsSelected));

	UE_LOG(LogTemp, Log, TEXT("%s"), *GetLevel());
	if (IsValid(m_owner))
	{
		m_owner->SetClickLevel(GetLevel());
	}
}

void UW_LobbyRoomInfo::SetRoomListParent(UW_LobbyRoomList* owner)
{
	m_owner = owner;
}

void UW_LobbyRoomInfo::SetRoomInfo(FGameSessionsInfo& info)
{
	m_info = info;
}

FString UW_LobbyRoomInfo::GetLevel()
{
	FString LevelName = m_info.m_IpAddress + ":" + FString::FromInt(m_info.m_Port);
	return LevelName;
}
