// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Transition/W_TransitionMain.h"
#include "Widget/Transition/W_TransitionLoding.h"

void UW_TransitionMain::NativeConstruct()
{
	Super::NativeConstruct();

	m_LodingWidget = Cast<UW_TransitionLoding>(GetWidgetFromName(TEXT("LodingWidget")));
	

}