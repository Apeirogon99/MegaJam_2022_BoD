// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/PS_WaitingRoom.h"

APS_WaitingRoom::APS_WaitingRoom()
{
	m_ready = false;
}

bool APS_WaitingRoom::GetReady()
{
	return m_ready;
}
