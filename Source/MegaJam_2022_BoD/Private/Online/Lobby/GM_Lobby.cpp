// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/Lobby/GM_Lobby.h"
#include "Online/Lobby/PC_Lobby.h"

AGM_Lobby::AGM_Lobby()
{
	PlayerControllerClass = APC_Lobby::StaticClass();
}

void AGM_Lobby::BeginPlay()
{

}
