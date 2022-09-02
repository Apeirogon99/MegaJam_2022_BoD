// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/Login/PC_Login.h"
#include "Widget/Login/W_LoginMain.h"
#include "Widget/Login/W_LoginSingIn.h"
#include "Widget/Login/W_LoginSingUp.h"
#include "Blueprint/UserWidget.h"

APC_Login::APC_Login()
{
	SetShowMouseCursor(true);

	LoadLoginWidgets();

}

void APC_Login::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	Mode.SetHideCursorDuringCapture(true);
	SetInputMode(Mode);

	ShowWidget(WidgetType::LOGIN_MAIN);
}

void APC_Login::LoadLoginWidgets()
{
	static ConstructorHelpers::FClassFinder<UW_LoginMain> loginMainWidget(TEXT("Blueprint'/Game/MegaJam_2022_BoD/Widget/Login/WB_LoginMain.WB_LoginMain_C'"));
	if (loginMainWidget.Succeeded())
	{
		m_loginMain = loginMainWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UW_LoginSingIn> loginSingInWidget(TEXT("Blueprint'/Game/MegaJam_2022_BoD/Widget/Login/WB_LoginSingIn.WB_LoginSingIn_C'"));
	if (loginSingInWidget.Succeeded())
	{
		m_loginSingIn = loginSingInWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UW_LoginSingUp> loginSingUpWidget(TEXT("Blueprint'/Game/MegaJam_2022_BoD/Widget/Login/WB_LoginSingUp.WB_LoginSingUp_C'"));
	if (loginSingUpWidget.Succeeded())
	{
		m_loginSingUp = loginSingUpWidget.Class;
	}
}

void APC_Login::ShowWidget(WidgetType type)
{
	UUserWidget* NewWidgetClass = nullptr;

	switch (type)
	{
	case WidgetType::LOGIN_MAIN:
		NewWidgetClass = CreateWidget(GetWorld(), m_loginMain);
		break;
	case WidgetType::LOGIN_SINGIN:
		NewWidgetClass = CreateWidget(GetWorld(), m_loginSingIn);
		break;
	case WidgetType::LOGIN_SINGUP:
		NewWidgetClass = CreateWidget(GetWorld(), m_loginSingUp);
		break;
	default:
		break;
	}

	if (NewWidgetClass != nullptr)
	{
		NewWidgetClass->AddToViewport();
	}

}
