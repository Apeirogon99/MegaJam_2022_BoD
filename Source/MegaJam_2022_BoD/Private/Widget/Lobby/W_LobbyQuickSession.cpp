// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyQuickSession.h"
#include "Online/BoD_GameInstance.h"
#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include <Kismet/GameplayStatics.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_LobbyQuickSession::NativeConstruct()
{
	Super::NativeConstruct();
	m_quickSessionURI = FString::Printf(TEXT("/resgamelift/quicksession"));

	//Button
	m_quickSession = Cast<UButton>(GetWidgetFromName(TEXT("m_quickSession")));

	if (m_quickSession != nullptr)
	{
		m_quickSession->OnClicked.AddDynamic(this, &UW_LobbyQuickSession::Click_QuickSession);
	}
}

void UW_LobbyQuickSession::Click_QuickSession()
{
	QuickSessionRequest();
}

void UW_LobbyQuickSession::QuickSessionRequest()
{
	UBoD_GameInstance* gameinstance = Cast<UBoD_GameInstance>(GetWorld()->GetGameInstance());
	FString TokenID = gameinstance->m_TokenID;
	m_lambda.HttpGetRequset<UW_LobbyQuickSession>(this,m_quickSessionURI, TokenID,&UW_LobbyQuickSession::OnQuickSessionResponse);
}

void UW_LobbyQuickSession::OnQuickSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (false == m_lambda.GetResponse(JsonObject, Response, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail GetResponse"))
		return;
	}

	FString IpAddress = JsonObject->GetObjectField("PlayerSession")->GetStringField("IpAddress");
	FString Port = JsonObject->GetObjectField("PlayerSession")->GetStringField("Port");

	FString LevelName = IpAddress + ":" + Port;

	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), false);
}
