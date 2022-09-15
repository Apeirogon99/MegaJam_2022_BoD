// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_Login.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS()
class MEGAJAM_2022_BOD_API AGM_Login : public AGameMode
{
	GENERATED_BODY()
	
public:
	AGM_Login();


public:
	virtual void BeginPlay() override;

public:
	void GameLiftInit();
};
