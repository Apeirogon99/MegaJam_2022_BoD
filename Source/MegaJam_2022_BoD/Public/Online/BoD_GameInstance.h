// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BoD_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API UBoD_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_nickName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_TokenID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_playerSessionID;
};
