// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyRoomInfo.h"
#include "GameLift/GameLiftUtils.h"
#include "GameLift/GameLiftCallbackStructs.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UW_LobbyRoomInfo::NativeConstruct()
{
	Super::NativeConstruct();

	m_room = Cast<UButton>(GetWidgetFromName(TEXT("m_room")));

	m_host = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_host")));
	m_curPlayer = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_curPlayer")));
	m_maxPlayer = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_maxPlayer")));
	m_location = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_location")));

	//Onclick
	if (m_room != nullptr)
	{
		m_room->OnClicked.AddDynamic(this, &UW_LobbyRoomInfo::Click_Room);
	}
}

void UW_LobbyRoomInfo::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
}

void UW_LobbyRoomInfo::NativeOnItemSelectionChanged(bool bIsSelected)
{

}

void UW_LobbyRoomInfo::SetRoomListParent(UW_LobbyRoomList* owner)
{
	m_owner = owner;
}

void UW_LobbyRoomInfo::Click_Room()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *GetLevel());
	if (IsValid(m_owner))
	{
		m_owner->SetClickLevel(GetLevel());
	}
}

void UW_LobbyRoomInfo::SetRoomInfo(FGameSessionsInfo info)
{
	m_info = info;

	m_curPlayer->SetText(FText::FromString(FString::FromInt(m_info.m_CurrentPlayerSessionCount)));
	m_maxPlayer->SetText(FText::FromString(FString::FromInt(m_info.m_MaximumPlayerSessionCount)));
	m_location->SetText(FText::FromString(GameLiftUtils::LocationToString(m_info.m_Location)));
}

FString UW_LobbyRoomInfo::GetLevel()
{
	FString LevelName = m_info.m_IpAddress + ":" + FString::FromInt(m_info.m_Port);
	return LevelName;
}
