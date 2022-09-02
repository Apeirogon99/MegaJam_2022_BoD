// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_LoginMain.generated.h"

/**
 * 
 */

class UW_LoginSingIn;
class UW_LoginSingUp;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LoginMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


public:
	UPROPERTY(Meta = (BindWidget))
		UW_LoginSingIn* m_singIn;


};
