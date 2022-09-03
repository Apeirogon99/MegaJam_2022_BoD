// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/W_LoginVerification.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_LoginVerification::NativeConstruct()
{
	Super::NativeConstruct();

	m_verificationLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_verificationLog")));
	m_resend = Cast<UButton>(GetWidgetFromName(TEXT("m_resend")));
	m_confirmAccount = Cast<UButton>(GetWidgetFromName(TEXT("m_confirmAccount")));
	m_verification = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_verification")));

	//Commit
	if (m_verification != nullptr)
	{
		m_verification->OnTextCommitted.AddDynamic(this, &UW_LoginVerification::Committed_Verification);
	}

	//OnClick Button
	if (m_resend != nullptr)
	{
		m_resend->OnClicked.AddDynamic(this, &UW_LoginVerification::Click_ReSend);
	}

	if (m_confirmAccount != nullptr)
	{
		m_confirmAccount->OnClicked.AddDynamic(this, &UW_LoginVerification::Click_Confirm);
	}

	AwsVerificationInit();
}

void UW_LoginVerification::Committed_Verification(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		m_verificationCode = message.ToString();
	}
}

void UW_LoginVerification::Click_ReSend()
{
	VerificationRequest(m_username, m_verificationCode, TEXT("true"));
}

void UW_LoginVerification::Click_Confirm()
{
	VerificationRequest(m_username, m_verificationCode, TEXT("false"));
}

void UW_LoginVerification::SetUsername(FString username)
{
	m_username = username;
}

void UW_LoginVerification::AwsVerificationInit()
{
	Http = &FHttpModule::Get();

	m_ApiGatewayEndpoint = FString::Printf(TEXT("https://llya2kr955.execute-api.ap-northeast-2.amazonaws.com/betaTest01"));
	m_verificationURI = FString::Printf(TEXT("/verification"));
}

void UW_LoginVerification::VerificationRequest(FString username, FString verification, FString resend)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("username"), *FString::Printf(TEXT("%s"), *username));
	JsonObject->SetStringField(TEXT("verification"), *FString::Printf(TEXT("%s"), *verification));
	JsonObject->SetStringField(TEXT("resend"), *FString::Printf(TEXT("%s"), *resend));

	FString JsonBody;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> LoginHttpRequest = Http->CreateRequest();

	LoginHttpRequest->SetVerb("POST");
	LoginHttpRequest->SetURL(m_ApiGatewayEndpoint + m_verificationURI);
	LoginHttpRequest->SetHeader("Content-Type", "application/json");
	LoginHttpRequest->SetContentAsString(JsonBody);
	LoginHttpRequest->OnProcessRequestComplete().BindUObject(this, &UW_LoginVerification::OnVerificationResponse);
	LoginHttpRequest->ProcessRequest();
}

void UW_LoginVerification::OnVerificationResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {

			FString Status = JsonObject->GetStringField("status");
			if (Status == TEXT("success"))
			{
				this->RemoveFromParent();
			}
			if (Status == TEXT("resendsuccess"))
			{
				m_verificationLog->SetVisibility(ESlateVisibility::Visible);
				m_verificationLog->SetText(FText::FromString(TEXT("resend code success")));
			}
			else
			{
				FString msg = JsonObject->GetStringField("msg");
				m_verificationLog->SetVisibility(ESlateVisibility::Visible);
				m_verificationLog->SetText(FText::FromString(msg));
			}
		}
	}
}
