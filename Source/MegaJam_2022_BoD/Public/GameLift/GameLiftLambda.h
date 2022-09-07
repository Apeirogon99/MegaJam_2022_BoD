// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"

/**
 * 
 */
class MEGAJAM_2022_BOD_API GameLiftLambda
{
public:
	GameLiftLambda();
	~GameLiftLambda();

public:
	template <typename UserClass>
	void HttpPostRequset(UserClass* uClass, TSharedPtr<FJsonObject>& JsonObject, FString URI, void (UserClass::*InFunc)(FHttpRequestPtr, FHttpResponsePtr, bool));

	template <typename UserClass>
	void HttpGetRequset(UserClass* uClass,FString URI, FString idt, void (UserClass::* InFunc)(FHttpRequestPtr, FHttpResponsePtr, bool));

	bool GetResponse(TSharedPtr<FJsonObject>& JsonObject, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	UPROPERTY(EditAnywhere)
		FString m_ApiGatewayEndpoint;
private:
	FHttpModule* Http;
};

template<typename UserClass>
inline void GameLiftLambda::HttpPostRequset(UserClass* uClass, TSharedPtr<FJsonObject>& JsonObject, FString URI, void(UserClass::* InFunc)(FHttpRequestPtr, FHttpResponsePtr, bool))
{
	FString JsonBody;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = Http->CreateRequest();

	HttpRequest->SetVerb("POST");
	HttpRequest->SetURL(m_ApiGatewayEndpoint + URI);
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetContentAsString(JsonBody);
	HttpRequest->OnProcessRequestComplete().BindUObject(uClass, InFunc);
	HttpRequest->ProcessRequest();
}

template<typename UserClass>
inline void GameLiftLambda::HttpGetRequset(UserClass* uClass, FString URI, FString idt, void(UserClass::* InFunc)(FHttpRequestPtr, FHttpResponsePtr, bool))
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = Http->CreateRequest();

	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(m_ApiGatewayEndpoint + URI);
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetHeader("Authorization", idt);
	HttpRequest->OnProcessRequestComplete().BindUObject(uClass, InFunc);
	HttpRequest->ProcessRequest();
}
