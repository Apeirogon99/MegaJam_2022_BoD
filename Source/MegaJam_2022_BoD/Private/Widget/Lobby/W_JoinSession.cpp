// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_JoinSession.h"
#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include <Kismet/GameplayStatics.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_JoinSession::NativeConstruct()
{
	Super::NativeConstruct();

	m_joinSessionURI = FString::Printf(TEXT("/resgamelift/joinsession"));

	//Button
	m_joinSession = Cast<UButton>(GetWidgetFromName(TEXT("m_joinSession")));

	//Commit
	m_joinSessionCode = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_joinSessionCode")));

	//COMMIT
	if (m_joinSessionCode != nullptr)
	{
		m_joinSessionCode->OnTextCommitted.AddDynamic(this, &UW_JoinSession::Committed_SessionCode);
	}

	//Onclick
	if (m_joinSession != nullptr)
	{
		m_joinSession->OnClicked.AddDynamic(this, &UW_JoinSession::Click_JoinSession);
	}
}

void UW_JoinSession::Click_JoinSession()
{
	if(!m_sessionCode.IsEmpty())
		JoinSessionRequest(m_sessionCode);
}

void UW_JoinSession::Committed_SessionCode(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_sessionCode = message.ToString();
	}
}

void UW_JoinSession::JoinSessionRequest(FString code)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("gamesessionId"), *FString::Printf(TEXT("%s"), *code));

	m_lambda.HttpPostRequset<UW_JoinSession>(this, JsonObject, m_joinSessionURI, &UW_JoinSession::OnJoinSessionResponse);
}

void UW_JoinSession::OnJoinSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
