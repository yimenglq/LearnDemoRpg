// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighLightIterface;
struct FGameplayTag;
class UAuraInputConfigDA;
class USplineComponent;
class UNavigationPath;

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



protected:

	TObjectPtr<	USplineComponent> Spline;

	//�ϴε��������ʱ��
	double LastLMBClickedTime;
	//��ǰ���������ʱ��
	double ThisLMBClickedTime;
	//�ж�Ϊ˫����ʱ��������
	UPROPERTY(EditAnywhere, Category = "00-Input|Cilick")
	float   TimeInterval = 0.2f;
	//�Զ�Ѱ·���յ�ֹͣ�뾶
	UPROPERTY(EditAnywhere,Category = "00-Input|autoPath" )
	float  StopAutoRido = 1000.f;
	bool bIsStopAutoRido = false;
	//�����Զ�Ѱ·
	bool bIsAutoRunMove = false;
	

	//�ƶ���λ��
	UPROPERTY(BlueprintReadOnly)
	FVector MoveLocation;

	//��ǰ��������н��
	FHitResult ThisHitResult;

	//Ѱ··��
	UNavigationPath* NavPath;


	void AutoMove();


private:
	UPROPERTY(EditAnywhere,Category = "00-Input")
	TObjectPtr<UInputMappingContext> AuraContext;//����ӳ��������
	
	UPROPERTY(EditAnywhere, Category = "00-Input")
	TObjectPtr<UInputAction> MoveAction;//�ƶ��������
	
	IHighLightIterface* LastActor;//��һ֡���е�
	IHighLightIterface* ThisActor;//��ǰ֡���е�



	void Move(const FInputActionValue& InputActionValue);//�ƶ���������ص�����

	void FindEnemyActor();
	



	//AbilityInput

	UPROPERTY(EditAnywhere, Category = "00Input|InputConfig")
	TObjectPtr<	UAuraInputConfigDA> AuraInputConfig;


	//��Ϸ��������������ݱ�ǩ����
	void AbilityInputTagPressed(FGameplayTag InputTag);
	
	//��Ϸ����̧��������ݱ�ǩ����
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	
	//end
};
