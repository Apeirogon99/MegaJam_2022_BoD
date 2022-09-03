// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/W_LoginSingUp.h"
#include "Widget/Login/W_LoginVerification.h"
#include "Online/Login/PC_Login.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

void UW_LoginSingUp::NativeConstruct()
{
	Super::NativeConstruct();

	//Case
	m_bLowerCase			= false;
	m_bUpperCase			= false;
	m_bSpeicalCase			= false;
	m_bNumberCase			= false;
	m_bLeastCharacterCase	= false;
	m_buserNameCase			= false;
	m_bemailCase			= false;
	m_bCanSignUp			= false;

	//SingUp Log
	m_signUpResultLog		= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_signUpResultLog")));

	//Case Log
	m_userNameLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_userNameLog")));
	m_emailLog				= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_emailLog")));
	m_lowerCaseLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_lowerCaseLog")));
	m_UpperCaseLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_UpperCaseLog")));
	m_SpeicalCaseLog		= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_SpeicalCaseLog")));
	m_NumberCaseLog			= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_NumberCaseLog")));
	m_leastNumberCaseLog	= Cast<UTextBlock>(GetWidgetFromName(TEXT("m_leastNumberCaseLog")));

	//EditBox

	m_username				= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_username")));
	m_email					= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_email")));
	m_password				= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_password")));

	//Button

	m_signUp				= Cast<UButton>(GetWidgetFromName(TEXT("m_signUp")));
	m_exit					= Cast<UButton>(GetWidgetFromName(TEXT("m_exit")));

	//TextBlock
	m_userNameLog->SetText(FText::FromString("User name cannot be blank"));
	m_emailLog->SetText(FText::FromString("Please include @ in your email address"));
	m_lowerCaseLog->SetText(FText::FromString("Password must contain a lower case letter"));
	m_UpperCaseLog->SetText(FText::FromString("Password must contain an upper case letter"));
	m_SpeicalCaseLog->SetText(FText::FromString("Password must contain a special character"));
	m_NumberCaseLog->SetText(FText::FromString("Password must contain a number"));
	m_leastNumberCaseLog->SetText(FText::FromString("Password must contain at least 8 characters"));

	//Commit
	if (m_username != nullptr)
	{
		m_username->OnTextCommitted.AddDynamic(this, &UW_LoginSingUp::Committed_UserName);
	}

	if (m_email != nullptr)
	{
		m_email->OnTextCommitted.AddDynamic(this, &UW_LoginSingUp::Committed_Email);
	}

	if (m_password != nullptr)
	{
		m_password->OnTextCommitted.AddDynamic(this, &UW_LoginSingUp::Committed_Password);
	}

	//OnClick Button

	if (m_signUp != nullptr)
	{
		m_signUp->OnClicked.AddDynamic(this, &UW_LoginSingUp::Click_SignUp);
	}

	if (m_exit != nullptr)
	{
		m_exit->OnClicked.AddDynamic(this, &UW_LoginSingUp::Click_Exit);
	}

	AwsSignInit();

}

void UW_LoginSingUp::Committed_UserName(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		FString Fmessage = FString(message.ToString());

		if (false == Fmessage.IsEmpty())
		{
			m_userNameLog->SetVisibility(ESlateVisibility::Hidden);
			m_buserNameCase = true;
		}
		else
		{
			m_userNameLog->SetVisibility(ESlateVisibility::Visible);
			m_buserNameCase = false;
		}

		m_currentUsername = Fmessage;

		CheckSignUp();
	}
}

void UW_LoginSingUp::Committed_Email(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		FString Fmessage = FString(message.ToString());

		int32 targetPos = INDEX_NONE;
		Fmessage.FindChar(TCHAR('@'), targetPos);

		if (targetPos != INDEX_NONE)
		{
			m_emailLog->SetVisibility(ESlateVisibility::Hidden);
			m_bemailCase = true;
		}
		else
		{
			m_emailLog->SetVisibility(ESlateVisibility::Visible);
			m_bemailCase = false;
		}

		m_currentEmail = Fmessage;

		CheckSignUp();
	}
}

void UW_LoginSingUp::Committed_Password(const FText& message, ETextCommit::Type commitType)
{
	bool lower = false;
	bool upper = false;
	bool special = false;
	bool number = false;

	if (ETextCommit::Type::OnEnter == commitType || ETextCommit::Type::OnUserMovedFocus == commitType)
	{
		FString Fmessage = FString(message.ToString());

		for (TCHAR word : Fmessage)
		{
			if (islower(word))
				lower = true;

			if (isupper(word))
				upper = true;

			if (isSpecial(word))
				special = true;

			if (isdigit(word))
				number = true;
		}

		m_bLowerCase = lower ? true : false;
		m_bUpperCase = upper ? true : false;
		m_bSpeicalCase = special ? true : false;
		m_bNumberCase = number ? true : false;
		m_bLeastCharacterCase = (Fmessage.Len() >= 8) ? true : false;

		m_currentPassword = Fmessage;

		CheckSignUp();
	}
}

void UW_LoginSingUp::Click_SignUp()
{
	if (m_bCanSignUp)
	{
		SignUpRequest(m_currentUsername, m_currentPassword, m_currentEmail);
	}
	else
	{
		m_signUpResultLog->SetVisibility(ESlateVisibility::Visible);
		//m_signUpResultLog->SetText(FText::FromString(TEXT("Check every case")));
	}
}

void UW_LoginSingUp::Click_Exit()
{
	this->RemoveFromParent();
}

void UW_LoginSingUp::CheckSignUp()
{
	if (m_bLowerCase && m_bUpperCase && m_bSpeicalCase && m_bNumberCase && m_bLeastCharacterCase && m_buserNameCase && m_bemailCase)
	{
		//FLinearColor ActiveColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//m_signUp->SetBackgroundColor(ActiveColor);
		m_bCanSignUp = true;
	}
	else
	{
		//FLinearColor inactiveColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.4f);
		//m_signUp->SetBackgroundColor(inactiveColor);
		m_bCanSignUp = false;
	}

}

bool UW_LoginSingUp::isSpecial(int _C)
{
	if (21 <= _C && _C <= 47 ||
		58 <= _C && _C <= 64 ||
		91 <= _C && _C <= 96 ||
		123 <= _C && _C <= 126)
	{
		return true;
	}

	return false;
}

void UW_LoginSingUp::AwsSignInit()
{
	Http = &FHttpModule::Get();

	m_ApiGatewayEndpoint = FString::Printf(TEXT("https://llya2kr955.execute-api.ap-northeast-2.amazonaws.com/betaTest01"));
	m_SignUpURI = FString::Printf(TEXT("/singup"));
}

void UW_LoginSingUp::SignUpRequest(FString usr, FString pwd, FString emi)
{
	UE_LOG(LogTemp, Log, TEXT("SignUpRequest"));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("username"), *FString::Printf(TEXT("%s"), *usr));
	JsonObject->SetStringField(TEXT("password"), *FString::Printf(TEXT("%s"), *pwd));
	JsonObject->SetStringField(TEXT("email"), *FString::Printf(TEXT("%s"), *emi));

	FString JsonBody;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> SignUpHttpRequest = Http->CreateRequest();

	SignUpHttpRequest->SetVerb("POST");
	SignUpHttpRequest->SetURL(m_ApiGatewayEndpoint + m_SignUpURI);
	SignUpHttpRequest->SetHeader("Content-Type", "application/json");
	SignUpHttpRequest->SetContentAsString(JsonBody);
	SignUpHttpRequest->OnProcessRequestComplete().BindUObject(this, &UW_LoginSingUp::OnSignUpResponse);
	SignUpHttpRequest->ProcessRequest();
}

void UW_LoginSingUp::OnSignUpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("OnSignUpResponse"));
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {

			FString Status = JsonObject->GetStringField("status");
			if (Status == TEXT("success"))
			{
				APC_Login* Controller = Cast<APC_Login>(GetWorld()->GetFirstPlayerController());
				UW_LoginVerification* verificationWidget = Cast<UW_LoginVerification>(Controller->CreateLoginWidgets(WidgetType::LOGIN_VERIFICATION));
				verificationWidget->SetUsername(m_currentUsername);
				
				this->RemoveFromParent();
			}
			else if(Status == TEXT("fail"))
			{
				FString msg = JsonObject->GetStringField("msg");
				m_signUpResultLog->SetVisibility(ESlateVisibility::Visible);
				m_signUpResultLog->SetText(FText::FromString(msg));
			}
		}
	}
}
