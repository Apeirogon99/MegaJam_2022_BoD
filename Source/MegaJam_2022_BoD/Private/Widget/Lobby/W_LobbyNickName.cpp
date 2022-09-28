// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyNickName.h"
#include "Widget/Lobby/W_LobbyUpdateNickName.h"
#include "Online/BoD_GameInstance.h"
#include <Components/TextBlock.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_LobbyNickName::NativeConstruct()
{
	Super::NativeConstruct();

	m_nickNameLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_nickNameLog")));
	m_nicknameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_nicknameText")));

	AwsURIInit();
}

void UW_LobbyNickName::GetNickName()
{
	GetNickNameRequest();
}

void UW_LobbyNickName::UpdateNickName(FString nickname)
{
	m_nicknameText->SetText(FText::FromString(nickname));
}

void UW_LobbyNickName::AwsURIInit()
{
	m_NickNameURI = FString::Printf(TEXT("/get_nickname"));
}

void UW_LobbyNickName::GetNickNameRequest()
{
	UBoD_GameInstance* LocalGameinstance = Cast<UBoD_GameInstance>(GetWorld()->GetGameInstance());
	if (LocalGameinstance)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetStringField(TEXT("username"), *FString::Printf(TEXT("%s"), *LocalGameinstance->m_username));
		m_lambda.HttpPostRequset<UW_LobbyNickName>(this, JsonObject, m_NickNameURI, &UW_LobbyNickName::GetNickNameResponse);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("None LocalGameInstance"));
	}
}

void UW_LobbyNickName::GetNickNameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (false == m_lambda.GetResponse(JsonObject, Response, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail GetResponse"))
			return;
	}

	FString Status = JsonObject->GetStringField("status");
	if (Status == TEXT("success"))
	{
		UBoD_GameInstance* LocalGameinstance = Cast<UBoD_GameInstance>(GetWorld()->GetGameInstance());
		FString nickname = JsonObject->GetStringField("nickname");
		LocalGameinstance->m_nickName = nickname;

		if (nickname != TEXT(""))
		{
			UpdateNickName(nickname);
		}
		else
		{
			UW_LobbyUpdateNickName* updateNickNameWidget = Cast<UW_LobbyUpdateNickName>(CreateWidget(GetWorld(), m_UpdateWidgetClass));
			if (updateNickNameWidget)
			{
				updateNickNameWidget->AddToViewport();
			}
		}

	}
	else
	{
		FString msg = JsonObject->GetStringField("msg");
		m_nickNameLog->SetVisibility(ESlateVisibility::Visible);
		m_nickNameLog->SetText(FText::FromString(msg));
	}
}
