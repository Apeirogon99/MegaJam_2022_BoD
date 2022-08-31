// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_TransitionLoding.generated.h"

/**
 * 
 */

class UTextBlock;
class UProgressBar;

UENUM(BlueprintType)
enum class EProgressType : uint8
{
	P_MAP			UMETA(DisplayName = "P_MAP"),
	P_OBJECT		UMETA(DisplayName = "P_OBJECT"),
	P_CHARACTER		UMETA(DisplayName = "P_CHARACTER"),
	P_WAITPLATER	UMETA(DisplayName = "P_WAITPLATER")
};

UCLASS()
class MEGAJAM_2022_BOD_API UW_TransitionLoding : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
		void UpdateLoding(const float lodingPercent, const EProgressType progressType);

protected:
	UFUNCTION()
		void UpdateLog(const EProgressType progressType);

	UFUNCTION()
		void UpdateBar(const float lodingPercent);

private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* m_ProgressLog;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* m_LodingBar;
};
