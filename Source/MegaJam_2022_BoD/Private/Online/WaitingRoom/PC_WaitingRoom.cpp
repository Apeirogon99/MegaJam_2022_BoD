// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Online/WaitingRoom/GM_WaitingRoom.h"
#include "Widget/Waiting/W_WaitingMain.h"
#include "Widget/Waiting/W_WaitingChatting.h"
#include "Blueprint/UserWidget.h"
#include <UObject/ConstructorHelpers.h>
#include <Kismet/GameplayStatics.h>

APC_WaitingRoom::APC_WaitingRoom()
{

}

void APC_WaitingRoom::BeginPlay()
{
	Super::BeginPlay();

	ClientInitWidget();
}

bool APC_WaitingRoom::ClientInitWidget_Validate()
{
	return true;
}

void APC_WaitingRoom::ClientInitWidget_Implementation()
{
	m_WaitingMain = Cast<UW_WaitingMain>(CreateWidget(GetWorld(), m_WaitingMainClass));
	if (m_WaitingMain)
	{
		m_WaitingMain->AddToViewport();
	}
}

UUserWidget* APC_WaitingRoom::CreateWaitingWidgets(EWaitingWidgetType type)
{
	UUserWidget* NewWidgetClass = nullptr;

	switch (type)
	{
	case EWaitingWidgetType::MAIN:
		NewWidgetClass = CreateWidget(GetWorld(), m_WaitingMainClass);
		break;
	default:
		break;
	}

	if (NewWidgetClass != nullptr)
	{
		NewWidgetClass->AddToViewport();
	}

	return NewWidgetClass;
}

bool APC_WaitingRoom::CS_Chatting_Validate(const FString& sender, const FText& message)
{
	return true;
}

void APC_WaitingRoom::CS_Chatting_Implementation(const FString& sender, const FText& message)
{
	AGM_WaitingRoom* gameMode = Cast<AGM_WaitingRoom>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode)
	{
		gameMode->ProcessChatting(sender, message);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BroadCastChatting : Gamemode is null"));
	}
}

bool APC_WaitingRoom::SC_Chatting_Validate(const FString& sender, const FText& message)
{
	return true;
}

void APC_WaitingRoom::SC_Chatting_Implementation(const FString& sender, const FText& message)
{
	this->m_WaitingMain->m_chatting->UpdateChatting(sender, message);
}
