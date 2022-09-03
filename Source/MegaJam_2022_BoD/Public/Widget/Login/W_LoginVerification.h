// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Http.h"
#include "W_LoginVerification.generated.h"

/**
 * 
 */
class UEditableTextBox;
class UButton;
class UTextBlock;

UCLASS()
class MEGAJAM_2022_BOD_API UW_LoginVerification : public UUserWidget
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
		UTextBlock* m_verificationLog;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* m_verification;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_resend;

	UPROPERTY(Meta = (BindWidget))
		UButton* m_confirmAccount;

public:
	UFUNCTION()
		void Committed_Verification(const FText& message, ETextCommit::Type commitType);

	UFUNCTION()
		void Click_ReSend();

	UFUNCTION()
		void Click_Confirm();

	UFUNCTION()
		void SetUsername(FString username);

private:
	UPROPERTY(EditAnywhere)
		FString m_verificationCode;

	UPROPERTY(EditAnywhere)
		FString m_ApiGatewayEndpoint;

	UPROPERTY(EditAnywhere)
		FString m_verificationURI;

	UPROPERTY(EditAnywhere)
		FString m_username;

	FHttpModule* Http;
	void AwsVerificationInit();
	void VerificationRequest(FString username, FString verification, FString resend);
	void OnVerificationResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
