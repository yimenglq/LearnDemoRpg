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
	TObjectPtr<UInputMappingContext> AuraContext;//����ӳ��������
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;//�ƶ��������
	
	IHighLightIterface* LastActor;//��һ֡
	IHighLightIterface* ThisActor;//��ǰ֡

	void Move(const FInputActionValue& InputActionValue);//�ƶ���������ص�����

	void FindEnemyActor();
};
