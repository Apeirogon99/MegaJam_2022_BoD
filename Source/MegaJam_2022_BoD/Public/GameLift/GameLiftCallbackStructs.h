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
