// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidUE5GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOIDUE5_API AArkanoidUE5GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 TotalPoints = 0;

	UPROPERTY(VisibleAnywhere)
	int32 NumberOfLives = 0;

	UPROPERTY(EditAnywhere)
	int32 MaxLives = 3;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameHudClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameHud* GameHud;

	UFUNCTION()
	void UpdateScore();

protected:
	virtual void BeginPlay() override;
};