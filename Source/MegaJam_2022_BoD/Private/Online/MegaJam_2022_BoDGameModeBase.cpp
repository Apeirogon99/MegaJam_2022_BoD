// Copyright Epic Games, Inc. All Rights Reserved.


#include "MegaJam_2022_BoDGameModeBase.h"
#include "GameLiftServerSDK.h"

AMegaJam_2022_BoDGameModeBase::AMegaJam_2022_BoDGameModeBase()
{
    GameLiftLocalTest();
}

void AMegaJam_2022_BoDGameModeBase::GameLiftLocalTest()
{
#if WITH_GAMELIFT

    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

    gameLiftSdkModule->InitSDK();

    auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
    {
        gameLiftSdkModule->ActivateGameSession();
    };

    FProcessParameters* params = new FProcessParameters();
    params->OnStartGameSession.BindLambda(onGameSession);
    params->OnTerminate.BindLambda([=]() {gameLiftSdkModule->ProcessEnding(); });
    params->OnHealthCheck.BindLambda([]() {return true; });
    params->port = 7777;

    TArray<FString> logfiles;
    logfiles.Add(TEXT("aLogFile.txt"));
    params->logParameters = logfiles;

    gameLiftSdkModule->ProcessReady(*params);
#endif
}
