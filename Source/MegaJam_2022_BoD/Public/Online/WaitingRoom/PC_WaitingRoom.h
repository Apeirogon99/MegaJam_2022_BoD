// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_WaitingRoom.generated.h"

/**
 * 
 */

UENUM()
enum class WaitingWidgetType
{
	MAIN,

};

class UW_WaitingMain;

UCLASS()
class MEGAJAM_2022_BOD_API APC_WaitingRoom : public APlayerController
{
	GENERATED_BODY()

public:
	APC_WaitingRoom();

protected:
	virtual void BeginPlay() override;
	void LoadWidget();
	
public:
	//WIDGET

	UFUNCTION()
		UUserWidget* CreateWaitingWidgets(WaitingWidgetType type);


private:
	TSubclassOf<UW_WaitingMain> m_WaitingMainClass;
	
	UPROPERTY()
		UW_WaitingMain* m_WaitingMain;
};
