// Fill out your copyright notice in the Description page of Project Settings.


#include "Logs.h"


void Logs::printOnScreen(const FString& DebugMessage)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, DebugMessage, false);
}

void Logs::Log(const FString& DebugMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMessage);
}
