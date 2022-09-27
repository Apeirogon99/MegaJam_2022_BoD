// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/GS_WaitingRoom.h"
#include "Online/WaitingRoom/GM_WaitingRoom.h"
#include "Online/WaitingRoom/PS_WaitingRoom.h"
#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Kismet/GameplayStatics.h"

AGS_WaitingRoom::AGS_WaitingRoom()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGS_WaitingRoom::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
