// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/GM_Battle.h"
#include "Online/Battle/PC_Battle.h"
#include "Online/Battle/PS_Battle.h"
#include "GameLiftServerSDK.h"

void AGM_Battle::InitSeamlessTravelPlayer(AController* newPlayer)
{
    Super::InitSeamlessTravelPlayer(newPlayer);

    m_players.AddUnique(Cast<APC_Battle>(newPlayer));

    OnConnected(Cast<APC_Battle>(newPlayer));
}

AGM_Battle::AGM_Battle()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MegaJam_2022_BOD/Online/Battle/FirstPersonCharacter"));

    DefaultPawnClass = PlayerPawnBPClass.Class;

    GameLiftLocalTest();
}

void AGM_Battle::OnConnected_Implementation(APC_Battle* controller)
{
}

void AGM_Battle::TravelActorList()
{
    
}

void AGM_Battle::GameLiftLocalTest()
{
#if WITH_GAMELIFT

    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

    gameLiftSdkModule->InitSDK();
#endif
}

void AGM_Battle::GameLiftEnd()
{

}
