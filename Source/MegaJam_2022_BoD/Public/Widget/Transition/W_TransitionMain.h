// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_TransitionMain.generated.h"

/**
 * 
 */

class UW_TransitionLoding;

UCLASS()
class MEGAJAM_2022_BOD_API UW_TransitionMain : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

private:
	UW_TransitionLoding* m_LodingWidget;
};
