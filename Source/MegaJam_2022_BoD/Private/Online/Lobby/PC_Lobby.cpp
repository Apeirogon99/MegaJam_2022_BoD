// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/Lobby/PC_Lobby.h"

APC_Lobby::APC_Lobby()
{
	SetShowMouseCursor(true);
}

void APC_Lobby::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	Mode.SetHideCursorDuringCapture(true);
	SetInputMode(Mode);
}