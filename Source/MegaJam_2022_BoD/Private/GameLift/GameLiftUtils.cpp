// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLift/GameLiftUtils.h"

GameLiftUtils::GameLiftUtils()
{
}

GameLiftUtils::~GameLiftUtils()
{
}

FString GameLiftUtils::LocationToString(FString location)
{
	if (location == "ap-northeast-2")
		return TEXT("KOR");

	return TEXT("UKNOWN");
}
