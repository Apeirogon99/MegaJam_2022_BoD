// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/GM_WaitingRoom.h"
#include "Online/WaitingRoom/C_WaitingRoom.h"
#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Online/WaitingRoom/GS_WaitingRoom.h"
#include "Online/WaitingRoom/PS_WaitingRoom.h"

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
	
}

void AGM_WaitingRoom::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//if (NewPlayer != nullptr)
	//{
	//	APC_WaitingRoom* newController = Cast<APC_WaitingRoom>(NewPlayer);
	//	if (m_players.Num() == 0)
	//	{
	//		m_hostPlayers = newController;
	//		m_hostIndex = 0;
	//	}

	//	m_players.Add(newController);
	//	//UE_LOG(LogTemp, Log, TEXT("Current Login %d"), m_players.Num());
	//}
}

void AGM_WaitingRoom::Logout(AController* Exiting)
{
	int32 removeIndex = m_players.Find(Cast<APC_WaitingRoom>(Exiting));
	
	//gameLiftSdkModule->RemovePlayerSession();

	m_players.RemoveAt(removeIndex);

	if (m_players.Num() == 0)
	{
		ProcessGameEnd();
	}
}

void AGM_WaitingRoom::ProcessGameReady()
{
	AGS_WaitingRoom* gameState = Cast<AGS_WaitingRoom>(GetWorld()->GetGameState());
	if (gameState)
	{
		FTimerHandle WaitHandle;
		float WaitTime = 5.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
				if (gameState->m_isAllReady)
				{
					ProcessStartGame();
				}
		}), WaitTime, false);
	}
}

void AGM_WaitingRoom::ProcessStartGame()
{
	FString levelName = TEXT("L_Battle");

	if (GetWorld())
	{
		GetWorld()->ServerTravel(levelName);
	}
}

void AGM_WaitingRoom::ProcessCancleGame()
{
}

void AGM_WaitingRoom::ProcessGameEnd()
{
#if WITH_GAMELIFT
	gameLiftSdkModule->ProcessEnding();

	EvnetGameEnd();
#endif
}

void AGM_WaitingRoom::EvnetGameEnd_Implementation()
{
}

void AGM_WaitingRoom::UpdateHostPlayer()
{
	int32 temp = ++m_hostIndex % m_players.Num();
	if (m_players[temp])
	{
		m_hostPlayers = m_players[temp];
	}
}

void AGM_WaitingRoom::TestAWSStartServer()
{
#if WITH_GAMELIFT

	gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
	gameLiftSdkModule->InitSDK();

	auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
	{
		gameLiftSdkModule->ActivateGameSession();
	};

	FProcessParameters* params = new FProcessParameters();
	params->OnStartGameSession.BindLambda(onGameSession);
	params->OnTerminate.BindLambda([=]() {gameLiftSdkModule->ProcessEnding(); });
	params->OnHealthCheck.BindLambda([]() {return true; });
	params->port;

	TArray<FString> logfiles;
	logfiles.Add(TEXT("aLogFile.txt"));
	params->logParameters = logfiles;

	gameLiftSdkModule->ProcessReady(*params);

	auto outCome = Aws::GameLift::Server::GetGameSessionId();
	if (outCome.IsSuccess())
	{
		sessionId = outCome.GetResult();
	}
	else
	{

	}

#endif
}

void AGM_WaitingRoom::ProcessChatting(const FString& sender, const FText& message)
{
	for (APC_WaitingRoom* playerController : m_players)
	{
		playerController->SC_Chatting(sender, message);
	}
}