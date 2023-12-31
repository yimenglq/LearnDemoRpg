// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighLightIterface;

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupInputComponent()override;


private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;//输入映射上下文
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;//移动输入操作
	
	IHighLightIterface* LastActor;//上一帧
	IHighLightIterface* ThisActor;//当前帧

	void Move(const FInputActionValue& InputActionValue);//移动输入操作回调函数

	void FindEnemyActor();
};
