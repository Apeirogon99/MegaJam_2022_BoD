// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLift/GameLiftLambda.h"
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"

GameLiftLambda::GameLiftLambda()
{
	Http = &FHttpModule::Get();

	m_ApiGatewayEndpoint = FString::Printf(TEXT("https://llya2kr955.execute-api.ap-northeast-2.amazonaws.com/betaTest01"));
}

GameLiftLambda::~GameLiftLambda()
{
}

bool GameLiftLambda::GetResponse(TSharedPtr<FJsonObject>& JsonObject, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful) 
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			return true;
		}
	}
	return false;
}
