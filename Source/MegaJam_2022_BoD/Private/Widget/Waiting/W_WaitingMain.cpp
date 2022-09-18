// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Waiting/W_WaitingMain.h"
#include "Widget/Waiting/W_WaitingChatting.h"

void UW_WaitingMain::NativeConstruct()
{
	m_chatting = Cast<UW_WaitingChatting>(GetWidgetFromName(TEXT("m_chatting")));
	
}

void UW_WaitingMain::OpenChattingBox()
{
	m_chatting->FocusChatting();
}