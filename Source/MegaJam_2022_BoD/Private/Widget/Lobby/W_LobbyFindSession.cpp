// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyFindSession.h"
#include "Widget/Lobby/W_LobbyRoomList.h"
#include "Online/BoD_GameInstance.h"
#include <Components/Button.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"
#include <Kismet/GameplayStatics.h>
#include "GameLift/GameLiftCallbackStructs.h"

void UW_LobbyFindSession::NativeConstruct()
{
	Super::NativeConstruct();

	//URI
	m_findSessionURI = FString::Printf(TEXT("/resgamelift/findsession"));

	//Button
	m_FindSession = Cast<UButton>(GetWidgetFromName(TEXT("m_FindSession")));

	//Onclick
	if (m_FindSession != nullptr)
	{
		m_FindSession->OnClicked.AddDynamic(this, &UW_LobbyFindSession::Click_FindSession);
	}

}

void UW_LobbyFindSession::Click_FindSession()
{
	FindSessionRequest();
}

void UW_LobbyFindSession::FindSessionRequest()
{
	UBoD_GameInstance* gameinstance = Cast<UBoD_GameInstance>(GetWorld()->GetGameInstance());
	FString TokenID = gameinstance->m_TokenID;
	m_lambda.HttpGetRequset<UW_LobbyFindSession>(this, m_findSessionURI, TokenID, &UW_LobbyFindSession::OnFindSessionResponse);
}

void UW_LobbyFindSession::OnFindSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (false == m_lambda.GetResponse(JsonObject, Response, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail GetResponse"));
		return;
	}

	if (!IsValid(m_RoomListWidget))
	{
		m_RoomListWidget = Cast<UW_LobbyRoomList>(CreateWidget(GetWorld(), m_RoomListWidgetClass));
	}

	auto GameSessionArray = JsonObject->GetArrayField("GameSessions");
	TArray<FGameSessionsInfo> gameSessionsInfos;
	
	for(auto GameSessionInfo : GameSessionArray)
	{
		FGameSessionsInfo gameSessionsInfo;
		//gameSessionsInfo.m_CurrentPlayerSessionCount = JsonObject->GetObjectField("GameSessions")->GetNumberField("CurrentPlayerSessionCount");
		gameSessionsInfo.m_CurrentPlayerSessionCount	= GameSessionInfo.Get()->AsObject()->GetNumberField("CurrentPlayerSessionCount");
		gameSessionsInfo.m_MaximumPlayerSessionCount	= GameSessionInfo.Get()->AsObject()->GetNumberField("MaximumPlayerSessionCount");
		gameSessionsInfo.m_IpAddress					= GameSessionInfo.Get()->AsObject()->GetStringField("IpAddress");
		gameSessionsInfo.m_Port							= GameSessionInfo.Get()->AsObject()->GetNumberField("Port");
		gameSessionsInfo.m_Location						= GameSessionInfo.Get()->AsObject()->GetStringField("Location");
		gameSessionsInfo.m_Status						= GameSessionInfo.Get()->AsObject()->GetStringField("Status");
		gameSessionsInfos.Add(gameSessionsInfo);
	}

	m_RoomListWidget->UpdateRoomList(gameSessionsInfos);
	m_RoomListWidget->AddToViewport(1);
}
