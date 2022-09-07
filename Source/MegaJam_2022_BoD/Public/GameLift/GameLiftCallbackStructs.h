// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLiftCallbackStructs.generated.h"

USTRUCT()
struct FTestStructs
{
	GENERATED_BODY()
public:
	FTestStructs();

public:
	UPROPERTY()
		bool Status;
};

USTRUCT(Atomic, BlueprintType)
struct FGameSessionsInfo
{
	GENERATED_BODY()

public:
	FGameSessionsInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 m_CurrentPlayerSessionCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 m_MaximumPlayerSessionCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_IpAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 m_Port;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_Status;
};