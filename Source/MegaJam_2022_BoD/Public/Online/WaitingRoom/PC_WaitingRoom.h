// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_WaitingRoom.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWaitingWidgetType : uint8
{
	MAIN,
	CHATTING,
};

class UW_WaitingMain;
class UW_WaitingChatting;

UCLASS()
class MEGAJAM_2022_BOD_API APC_WaitingRoom : public APlayerController
{
	GENERATED_BODY()

public:
	APC_WaitingRoom();

protected:
	virtual void BeginPlay() override;
	
public:
	//WIDGET

	UFUNCTION(Client, Reliable, WithValidation)
	void ClientInitWidget();
	virtual bool ClientInitWidget_Validate();
	virtual void ClientInitWidget_Implementation();

	UFUNCTION(BlueprintCallable)
		UUserWidget* CreateWaitingWidgets(EWaitingWidgetType type);

	UFUNCTION(Server, Reliable, WithValidation)
	void CS_Chatting(const FString& sender, const FText& message);
	virtual bool CS_Chatting_Validate(const FString& sender, const FText& message);
	virtual void CS_Chatting_Implementation(const FString& sender, const FText& message);

	UFUNCTION(Client, Reliable, WithValidation)
	void SC_Chatting(const FString& sender, const FText& message);
	virtual bool SC_Chatting_Validate(const FString& sender, const FText& message);
	virtual void SC_Chatting_Implementation(const FString& sender, const FText& message);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UW_WaitingMain* m_WaitingMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UW_WaitingMain> m_WaitingMainClass;

};
