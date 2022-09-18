// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/GM_WaitingRoom.h"
#include "Online/WaitingRoom/C_WaitingRoom.h"
#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Online/WaitingRoom/GS_WaitingRoom.h"
#include "Online/WaitingRoom/PS_WaitingRoom.h"
#include "GameLiftServerSDK.h"

AGM_WaitingRoom::AGM_WaitingRoom()
{
	//Default Setting
	bUseSeamlessTravel = true;

	//Online Class Setting
	DefaultPawnClass		= AC_WaitingRoom::StaticClass();
	PlayerControllerClass	= APC_WaitingRoom::StaticClass();
	GameStateClass			= AGS_WaitingRoom::StaticClass();
	PlayerStateClass		= APS_WaitingRoom::StaticClass();

	//AWS Service Start
	TestAWSStartServer();
}

void AGM_WaitingRoom::BeginPlay()
{
	/*FString description;
	m_travelLevelName = FString::Printf(TEXT("L_Battle"));
	TravelLevel(m_travelLevelName, description);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *description);*/
}

void AGM_WaitingRoom::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer != nullptr)
	{
		if (IsValid(NewPlayer->GetPawn()))
		{
			////Delete old pawn
			//APawn* oldPawn = NewPlayer->GetPawn();
			//NewPlayer->UnPossess();
			//oldPawn->Destroy();

			////Create new pawn
			//FActorSpawnParameters parm;
			//APawn* newPawn = Cast<APawn>(GetWorld()->SpawnActor<APC_WaitingRoom>(parm));
			//NewPlayer->Possess(newPawn);
		}

		m_players.Add(Cast<APC_WaitingRoom>(NewPlayer));
		UE_LOG(LogTemp, Log, TEXT("Current Login %d"), m_players.Num());
	}
}

bool AGM_WaitingRoom::GameStart()
{
	FString description;
	AGS_WaitingRoom* gameState = Cast<AGS_WaitingRoom>(GetWorld()->GetGameState());
	if (nullptr == gameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState is nullptr"));
		return false;
	}

	//if player length
	if (false == gameState->EnoughPlayers(1, 10, description))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *description);
		return false;
	}

	//if ready is false
	if(false == gameState->GetAllReady(description))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *description);
		return false;
	}

	//Travel Level
	if (false == TravelLevel(m_travelLevelName, description))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *description);
		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *description);
	return true;
}

void AGM_WaitingRoom::TestAWSStartServer()
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

	//FTimerHandle WaitHandle;
	//float WaitTime = 60.0f * 5.0f;
	//GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	//	{
	//		gameLiftSdkModule->ProcessEnding();

	//	}), WaitTime, false);
#endif
}

void AGM_WaitingRoom::ProcessChatting(const FString& sender, const FText& message)
{
	for (APC_WaitingRoom* playerController : m_players)
	{
		playerController->SC_Chatting(sender, message);
	}
}

bool AGM_WaitingRoom::TravelLevel(const FString levelName, FString& Description)
{
	if (GetWorld())
	{
		if (GetWorld()->ServerTravel(levelName))
		{
			Description = TEXT("Success ServerTravel");
			return true;
		}
		else
		{
			Description = TEXT("Fail ServerTravel");
			return false;
		}
	}

	Description = TEXT("UWorld is nullptr");
	return false;
}
