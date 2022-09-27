// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/PS_WaitingRoom.h"
#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Online/WaitingRoom/GS_WaitingRoom.h"
#include <Net/UnrealNetwork.h>

APS_WaitingRoom::APS_WaitingRoom()
{
	m_ready = false;
}

void APS_WaitingRoom::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APS_WaitingRoom, m_ready);
	DOREPLIFETIME(APS_WaitingRoom, m_host);
}