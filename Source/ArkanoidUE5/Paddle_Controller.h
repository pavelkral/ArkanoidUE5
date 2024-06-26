// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Paddle_Controller.generated.h"

class ABall;

UCLASS()
class ARKANOIDUE5_API APaddle_Controller : public APlayerController
{
	GENERATED_BODY()
	APaddle_Controller();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LunchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuitAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SaveAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ChangeAction;

protected:
	virtual void BeginPlay() override;
	//void MoveHorizontal(float AxisValue);
	virtual void MoveHorizontal(const FInputActionValue& Value);
	
	void Launch();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABall> BallObj;

	ABall* MyBall;

	FVector SpawnLocation = FVector(10.0f, 0.0f, 40.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	bool bIsEpic = true;

public:
	UFUNCTION()
	virtual void SetupInputComponent() override;
	void QuitApp();
	void SaveApp();
	void ChangeApp();
	void SpawnNewBall();
};
