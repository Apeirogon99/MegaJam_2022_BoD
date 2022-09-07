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
	UPROPERTY(EditAnywhere)
		FString m_nickName;

	UPROPERTY(EditAnywhere)
		FString m_TokenID;
};
