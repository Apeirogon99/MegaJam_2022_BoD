// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/Login/GM_Login.h"
#include "Online/Login/PC_Login.h"
#include "GameLiftServerSDK.h"

AGM_Login::AGM_Login()
{
	PlayerControllerClass = APC_Login::StaticClass();
}

void AGM_Login::BeginPlay()
{
    
}

void AGM_Login::GameLiftInit()
{
#if WITH_GAMELIFT

    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

    gameLiftSdkModule->InitSDK();
#endif
}
