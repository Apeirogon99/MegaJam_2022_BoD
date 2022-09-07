// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyRoomList.h"
#include "GameLift/GameLiftUtils.h"
#include "GameLift/GameLiftCallbackStructs.h"
#include "Widget/Lobby/W_LobbyRoomInfo.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/ListView.h>
#include <Kismet/GameplayStatics.h>

void UW_LobbyRoomList::NativeConstruct()
{
	Super::NativeConstruct();

	m_joinRoom = Cast<UButton>(GetWidgetFromName(TEXT("m_joinRoom")));
	m_refresh = Cast<UButton>(GetWidgetFromName(TEXT("m_refresh")));
	m_exit = Cast<UButton>(GetWidgetFromName(TEXT("m_exit")));

	m_roomListView = Cast<UListView>(GetWidgetFromName(TEXT("m_roomListView")));

	m_roomListLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_roomListLog")));
	m_roomListLog->SetVisibility(ESlateVisibility::Hidden);

	//Onclick
	if (m_joinRoom != nullptr)
	{
		m_joinRoom->OnClicked.AddDynamic(this, &UW_LobbyRoomList::Click_JoinRoom);
	}

	if (m_refresh != nullptr)
	{
		m_refresh->OnClicked.AddDynamic(this, &UW_LobbyRoomList::Click_Refresh);
	}

	if (m_exit != nullptr)
	{
		m_exit->OnClicked.AddDynamic(this, &UW_LobbyRoomList::Click_Exit);
	}
}

void UW_LobbyRoomList::Click_JoinRoom()
{
	if (m_currentClickLevel.IsEmpty())
	{
		m_roomListLog->SetText(FText::FromString("Please select a room"));
		m_roomListLog->SetVisibility(ESlateVisibility::Visible);
		
		FTimerHandle WaitHandle;
		float WaitTime = 3.0f; 
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				m_roomListLog->SetVisibility(ESlateVisibility::Hidden);
				
			}), WaitTime, false); 
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*m_currentClickLevel), false);
	}
}

void UW_LobbyRoomList::Click_Refresh()
{
	m_roomListView->ClearListItems();
}

void UW_LobbyRoomList::Click_Exit()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UW_LobbyRoomList::UpdateRoomList(TArray<FGameSessionsInfo>& infos)
{
	if (infos.Num() == 0)
	{
		m_roomListLog->SetText(FText::FromString("No room exists"));
		m_roomListLog->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("No room exists"));
	}
	else
	{
		m_roomListView->ClearListItems();

		if (IsValid(m_RoomInfoClass))
		{
			for (FGameSessionsInfo SessionsInfo : infos)
			{
				UW_LobbyRoomInfo* roomInfoWidget = CreateWidget<UW_LobbyRoomInfo>(GetWorld(), m_RoomInfoClass);
				if (roomInfoWidget)
				{
					roomInfoWidget->SetRoomListParent(this);
					roomInfoWidget->SetRoomInfo(SessionsInfo);
					m_roomListView->AddItem(roomInfoWidget);
					m_SearchRoomInfos.Add(roomInfoWidget);
				}
			}
		}

		m_roomListView->RegenerateAllEntries();
	}
}


void UW_LobbyRoomList::SetClickLevel(FString level)
{
	m_currentClickLevel = level;
}
