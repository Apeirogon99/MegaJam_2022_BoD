// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Waiting/W_WaitingChatting.h"
#include <Components/TextBlock.h>
#include <Components/ListView.h>
#include <Components/EditableTextBox.h>
#include <Components/Border.h>
#include "Widget/Waiting/W_WaitingChatInfo.h"
#include "Online/WaitingRoom/GM_WaitingRoom.h"
#include "Online/WaitingRoom/GS_WaitingRoom.h"
#include "Online/WaitingRoom/PC_WaitingRoom.h"
#include <Kismet/GameplayStatics.h>

void UW_WaitingChatting::NativeConstruct()
{
	Super::NativeConstruct();

	m_border = Cast<UBorder>(GetWidgetFromName(TEXT("m_border")));
	m_ChattingBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("m_ChattingBox")));
	m_ChatListView = Cast<UListView>(GetWidgetFromName(TEXT("m_ChatListView")));

	m_ChatListView->ClearListItems();

	if (m_ChattingBox != nullptr)
	{
		m_ChattingBox->OnTextCommitted.AddDynamic(this, &UW_WaitingChatting::Committed_Chatting);
	}
}

void UW_WaitingChatting::UpdateChatting(const FString& name, const FText& chatLog)
{
	if (IsValid(m_ChatInfoClass))
	{
		UW_WaitingChatInfo* ChatInfoWidget = CreateWidget<UW_WaitingChatInfo>(GetWorld(), m_ChatInfoClass);
		if (ChatInfoWidget)
		{
			ChatInfoWidget->SetChatInfo(name, chatLog);
			m_ChatListView->AddItem(ChatInfoWidget);
		}
	}

	m_ChatListView->RegenerateAllEntries();
}

void UW_WaitingChatting::FocusChatting()
{
	if (false == HasKeyboardFocus())
	{
		APC_WaitingRoom* playerContoller = Cast<APC_WaitingRoom>(GetOwningPlayerPawn()->GetController());
		FInputModeGameAndUI Mode;
		Mode.SetWidgetToFocus(m_ChattingBox->GetCachedWidget());
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetHideCursorDuringCapture(true);
		playerContoller->SetInputMode(Mode);
	}
}

void UW_WaitingChatting::Committed_Chatting(const FText& message, ETextCommit::Type commitType)
{
	if (ETextCommit::Type::OnEnter == commitType)
	{
		APC_WaitingRoom* playerContoller = Cast<APC_WaitingRoom>(GetOwningPlayer());

		if (playerContoller)
		{
			playerContoller->CS_Chatting(TEXT("TEST"), message);

			m_ChattingBox->SetText(FText::FromString(TEXT("")));
			FInputModeGameOnly Mode;
			playerContoller->SetInputMode(Mode);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Committed_Chatting : playerContoller is null"));
		}
		
	}
}