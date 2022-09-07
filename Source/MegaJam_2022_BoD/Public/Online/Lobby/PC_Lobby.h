// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_2022_BOD_API APC_Lobby : public APlayerController
{
	GENERATED_BODY()
	
public:
	APC_Lobby();

public:
	virtual void BeginPlay() override;
};
