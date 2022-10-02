// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/GM_Battle.h"

AGM_Battle::AGM_Battle()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MegaJam_2022_BOD/Online/Battle/FirstPersonCharacter"));

    DefaultPawnClass = PlayerPawnBPClass.Class;

    GameLiftLocalTest();
}

void AGM_Battle::GameLiftLocalTest()
{
#if WITH_GAMELIFT

    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

    gameLiftSdkModule->InitSDK();
#endif
}