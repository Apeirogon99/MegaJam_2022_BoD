// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Login.generated.h"

/**
 * 
 */

class UW_LoginMain;
class UW_LoginSingIn;
class UW_LoginSingUp;
class UW_LoginVerification;

UENUM(BlueprintType)
enum class WidgetType : uint8
{
	LOGIN_MAIN,
	LOGIN_SINGIN,
	LOGIN_SINGUP,
	LOGIN_VERIFICATION
};

UCLASS()
class MEGAJAM_2022_BOD_API APC_Login : public APlayerController
{
	GENERATED_BODY()
	
public:
	APC_Login();

	virtual void BeginPlay() override;

protected:
	void LoadLoginWidgets();

public:
	UFUNCTION()
		UUserWidget* CreateLoginWidgets(WidgetType type);

public:
	TSubclassOf<UW_LoginMain> m_loginMain;
	TSubclassOf<UW_LoginSingIn> m_loginSingIn;
	TSubclassOf<UW_LoginSingUp> m_loginSingUp;
	TSubclassOf<UW_LoginVerification> m_loginVerification;
};
