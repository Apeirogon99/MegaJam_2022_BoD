// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/WaitingRoom/C_WaitingRoom.h"

// Sets default values
AC_WaitingRoom::AC_WaitingRoom()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_WaitingRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_WaitingRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_WaitingRoom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

