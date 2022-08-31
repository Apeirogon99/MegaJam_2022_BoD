// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Transition/W_TransitionLoding.h"
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UW_TransitionLoding::NativeConstruct()
{
	Super::NativeConstruct();

	m_ProgressLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProgressLog")));
	m_LodingBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("LodingBar")));

}

void UW_TransitionLoding::UpdateLoding(const float lodingPercent, const EProgressType progressType)
{
	UpdateLog(progressType);
	UpdateBar(lodingPercent);
}

void UW_TransitionLoding::UpdateBar(const float lodingPercent)
{
	if (m_LodingBar == nullptr)
	{
		m_ProgressLog->SetText(FText::FromString("ProgressBar is nullptr"));
		return;
	}

	m_LodingBar->SetPercent(lodingPercent);
}

void UW_TransitionLoding::UpdateLog(const EProgressType progressType)
{
	FText message;
	if (m_ProgressLog == nullptr)
	{
		m_ProgressLog->SetText(FText::FromString("ProgressLog is nullptr"));
		return;
	}

	switch (progressType)
	{
	case EProgressType::P_MAP:
		message = FText::FromString("맵 생성중");
		break;
	case EProgressType::P_OBJECT:
		message = FText::FromString("오브젝트 배치중");
		break;
	case EProgressType::P_CHARACTER:
		message = FText::FromString("캐릭터 스폰중");
		break;
	case EProgressType::P_WAITPLATER:
		message = FText::FromString("참가자 기다리는 중");
		break;
	default:
		message = FText::FromString("Default ProgressType");
		break;
	};

	m_ProgressLog->SetText(message);
}