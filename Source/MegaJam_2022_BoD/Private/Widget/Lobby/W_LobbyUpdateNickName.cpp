// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/W_LobbyUpdateNickName.h"
#include "Online/BoD_GameInstance.h"
#include "Online/Lobby/PC_Lobby.h"
#include <Components/TextBlock.h>
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_LobbyUpdateNickName::NativeConstruct()
{

	Super::NativeConstruct();

	m_updateButton	= Cast<UButton>(GetWidgetFromName(TEXT("m_updateButton")));
	m_editNickname	= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_editNickname")));
	m_nickNameLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_nickNameLog")));


	if (m_editNickname != nullptr)
	{
		m_editNickname->OnTextCommitted.AddDynamic(this, &UW_LobbyUpdateNickName::Committed_NickName);
	}


	if (m_updateButton != nullptr)
	{
		m_updateButton->OnClicked.AddDynamic(this, &UW_LobbyUpdateNickName::Click_Update);
	}

	AwsURIInit();
}

void UW_LobbyUpdateNickName::Committed_NickName(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_nickname = message.ToString();
	}
}

void UW_LobbyUpdateNickName::Click_Update()
{
	if(!m_nickname.IsEmpty())
		UpdateNickNameRequest(m_nickname);
}

void UW_LobbyUpdateNickName::UpdateNickNameRequest(FString nickname)
{
	UBoD_GameInstance* LocalGameinstance = Cast<UBoD_GameInstance>(GetWorld()->GetGameInstance());
	if (LocalGameinstance)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetStringField(TEXT("username"), *FString::Printf(TEXT("%s"), *LocalGameinstance->m_username));
		JsonObject->SetStringField(TEXT("nickname"), *FString::Printf(TEXT("%s"), *nickname));

		m_lambda.HttpPostRequset<UW_LobbyUpdateNickName>(this, JsonObject, m_NickNameURI, &UW_LobbyUpdateNickName::UpdateNickNameResponse);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("None LocalGameInstance"));
	}
}

void UW_LobbyUpdateNickName::UpdateNickNameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

		APC_Lobby* playerController = Cast<APC_Lobby>(GetOwningPlayerPawn()->GetController());
		if (playerController)
		{
			playerController->UpdateNickName();
		}

		this->RemoveFromParent();
	}
	else
	{
		FString msg = JsonObject->GetStringField("msg");
		m_nickNameLog->SetVisibility(ESlateVisibility::Visible);
		m_nickNameLog->SetText(FText::FromString(msg));
	}
}

void UW_LobbyUpdateNickName::AwsURIInit()
{
	m_NickNameURI = FString::Printf(TEXT("/update_nickname"));
}
