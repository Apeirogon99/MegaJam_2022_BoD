// Copyright Epic Games, Inc. All Rights Reserved.


#include "MegaJam_2022_BoDGameModeBase.h"
#include <UObject/ConstructorHelpers.h>
#include "GameLiftServerSDK.h"

AMegaJam_2022_BoDGameModeBase::AMegaJam_2022_BoDGameModeBase()
{
    
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MegaJam_2022_BOD/Online/Battle/FirstPersonCharacter"));

    DefaultPawnClass = PlayerPawnBPClass.Class;

    GameLiftLocalTest();
}

void AMegaJam_2022_BoDGameModeBase::GameLiftLocalTest()
{
#if WITH_GAMELIFT

    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

    gameLiftSdkModule->InitSDK();
#endif
}
