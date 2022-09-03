// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/W_LoginSingIn.h"
#include "Widget/Login/W_LoginSingUp.h"
#include "Online/Login/PC_Login.h"
#include <Kismet/GameplayStatics.h>
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_LoginSingIn::NativeConstruct()
{
	Super::NativeConstruct();

	//SingIn Log
	m_singInResultLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_singInResultLog")));

	//Button
	m_singIn = Cast<UButton>(GetWidgetFromName(TEXT("m_singIn")));
	m_singUp = Cast<UButton>(GetWidgetFromName(TEXT("m_singUp")));

	//EditBox
	m_username = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_username")));
	m_password = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_password")));

	//Commit
	if (m_username != nullptr)
	{
		m_username->OnTextCommitted.AddDynamic(this, &UW_LoginSingIn::Committed_UserName);
	}

	if (m_password != nullptr)
	{
		m_password->OnTextCommitted.AddDynamic(this, &UW_LoginSingIn::Committed_Password);
	}

	//OnClick Button
	if (m_singUp != nullptr)
	{
		m_singUp->OnClicked.AddDynamic(this, &UW_LoginSingIn::Click_AddToSingUp);
	}

	if (m_singIn != nullptr)
	{
		m_singIn->OnClicked.AddDynamic(this, &UW_LoginSingIn::Click_SingIn);
	}

	AwsLoginInit();

}

void UW_LoginSingIn::Committed_UserName(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_currentUserName = message.ToString();
	}
}

void UW_LoginSingIn::Committed_Password(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_currentPassword = message.ToString();
	}
}

void UW_LoginSingIn::Click_AddToSingUp()
{
	APC_Login* playerController = Cast<APC_Login>(GetWorld()->GetFirstPlayerController());
	playerController->CreateLoginWidgets(WidgetType::LOGIN_SINGUP);
}

void UW_LoginSingIn::Click_SingIn()
{
	LoginRequest(m_currentUserName, m_currentPassword);
}

void UW_LoginSingIn::AwsLoginInit()
{
	Http = &FHttpModule::Get();

	m_ApiGatewayEndpoint = FString::Printf(TEXT("https://llya2kr955.execute-api.ap-northeast-2.amazonaws.com/betaTest01"));
	m_LoginURI = FString::Printf(TEXT("/singin"));
}

void UW_LoginSingIn::LoginRequest(FString usr, FString pwd)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("username"), *FString::Printf(TEXT("%s"), *usr));
	JsonObject->SetStringField(TEXT("password"), *FString::Printf(TEXT("%s"), *pwd));

	FString JsonBody;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> LoginHttpRequest = Http->CreateRequest();

	LoginHttpRequest->SetVerb("POST");
	LoginHttpRequest->SetURL(m_ApiGatewayEndpoint + m_LoginURI);
	LoginHttpRequest->SetHeader("Content-Type", "application/json");
	LoginHttpRequest->SetContentAsString(JsonBody);
	LoginHttpRequest->OnProcessRequestComplete().BindUObject(this, &UW_LoginSingIn::OnLoginResponse);
	LoginHttpRequest->ProcessRequest();
}

void UW_LoginSingIn::OnLoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {

			FString Status = JsonObject->GetStringField("status");
			if (Status == TEXT("success"))
			{
				FString IdToken = JsonObject->GetObjectField("tokens")->GetStringField("IdToken");
				FName LobbyName = TEXT("L_Lobby");
				UGameplayStatics::OpenLevel(GetWorld(), LobbyName);
			}
			else
			{
				FString msg = JsonObject->GetStringField("msg");
				m_singInResultLog->SetVisibility(ESlateVisibility::Visible);
				m_singInResultLog->SetText(FText::FromString(msg));
			}
		}
	}
}
