// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLift/GameLiftCallbackStructs.h"

FTestStructs::FTestStructs()
{
	Status = false;
}

FGameSessionsInfo::FGameSessionsInfo()
{
		m_CurrentPlayerSessionCount = -1;
		m_MaximumPlayerSessionCount = -1;
		m_IpAddress = TEXT("");
		m_Port = -1;
		m_Location = TEXT("");
		m_Status = false;
}
