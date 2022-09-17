// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include "Widget/Waiting/W_WaitingMain.h"

APC_WaitingRoom::APC_WaitingRoom()
{
	LoadWidget();
}

void APC_WaitingRoom::BeginPlay()
{
	Super::BeginPlay();

	m_WaitingMain = Cast<UW_WaitingMain>(CreateWaitingWidgets(WaitingWidgetType::MAIN));
}

void APC_WaitingRoom::LoadWidget()
{
	static ConstructorHelpers::FClassFinder<UW_WaitingMain> WaitingMainWidget(TEXT("Blueprint'/Game/MegaJam_2022_BoD/Widget/Watiting/BW_WaitingMain.BW_WaitingMain_C'"));
	if (WaitingMainWidget.Succeeded())
	{
		m_WaitingMainClass = WaitingMainWidget.Class;
	}
}

UUserWidget* APC_WaitingRoom::CreateWaitingWidgets(WaitingWidgetType type)
{
	UUserWidget* NewWidgetClass = nullptr;

	switch (type)
	{
	case WaitingWidgetType::MAIN:
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
