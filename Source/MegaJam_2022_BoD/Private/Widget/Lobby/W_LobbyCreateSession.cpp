// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyCreateSession.h"
#include "Online/BoD_GameInstance.h"
#include <Components/Button.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"
#include <Kismet/GameplayStatics.h>

void UW_LobbyCreateSession::NativeConstruct()
{
	Super::NativeConstruct();

	m_createSessionURI = FString::Printf(TEXT("/resgamelift/createsession"));

	m_createSession = Cast<UButton>(GetWidgetFromName(TEXT("m_createSession")));

	//Onclick
	if (m_createSession != nullptr)
	{
		m_createSession->OnClicked.AddDynamic(this, &UW_LobbyCreateSession::Click_CreateSession);
	}
}

void UW_LobbyCreateSession::Click_CreateSession()
{
	CreateSessionRequest();
}

void UW_LobbyCreateSession::CreateSessionRequest()
{
	UBoD_GameInstance* gameinstance = Cast<UBoD_GameInstance>(GetWorld()->GetGameInstance());
	FString TokenID = gameinstance->m_TokenID;
	m_lambda.HttpGetRequset<UW_LobbyCreateSession>(this, m_createSessionURI, TokenID, &UW_LobbyCreateSession::OnCreateSessionResponse);
}

void UW_LobbyCreateSession::OnCreateSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (false == m_lambda.GetResponse(JsonObject, Response, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail GetResponse"));
		return;
	}

	FString IpAddress = JsonObject->GetObjectField("PlayerSession")->GetStringField("IpAddress");
	FString Port = JsonObject->GetObjectField("PlayerSession")->GetStringField("Port");

	FString LevelName = IpAddress + ":" + Port;

	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), false);
}
