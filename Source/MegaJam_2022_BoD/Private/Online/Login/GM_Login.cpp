// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/Login/GM_Login.h"
#include "Online/Login/PC_Login.h"

AGM_Login::AGM_Login()
{
	PlayerControllerClass = APC_Login::StaticClass();
}

void AGM_Login::BeginPlay()
{
    
}
