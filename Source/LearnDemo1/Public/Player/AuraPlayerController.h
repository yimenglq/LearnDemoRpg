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

	//上次点击鼠标左键时间
	double LastLMBClickedTime;
	//当前点击鼠标左键时间
	double ThisLMBClickedTime;
	//判断为双击的时间允许间隔
	UPROPERTY(EditAnywhere, Category = "00-Input|Cilick")
	float   TimeInterval = 0.2f;
	//自动寻路最终点停止半径
	UPROPERTY(EditAnywhere,Category = "00-Input|autoPath" )
	float  StopAutoRido = 1000.f;
	bool bIsStopAutoRido = false;
	//启动自动寻路
	bool bIsAutoRunMove = false;
	

	//移动的位置
	UPROPERTY(BlueprintReadOnly)
	FVector MoveLocation;

	//当前鼠标下命中结果
	FHitResult ThisHitResult;

	//寻路路径
	UNavigationPath* NavPath;


	void AutoMove();


private:
	UPROPERTY(EditAnywhere,Category = "00-Input")
	TObjectPtr<UInputMappingContext> AuraContext;//输入映射上下文
	
	UPROPERTY(EditAnywhere, Category = "00-Input")
	TObjectPtr<UInputAction> MoveAction;//移动输入操作
	
	IHighLightIterface* LastActor;//上一帧命中的
	IHighLightIterface* ThisActor;//当前帧命中的



	void Move(const FInputActionValue& InputActionValue);//移动输入操作回调函数

	void FindEnemyActor();
	



	//AbilityInput

	UPROPERTY(EditAnywhere, Category = "00Input|InputConfig")
	TObjectPtr<	UAuraInputConfigDA> AuraInputConfig;


	//游戏能力按下输入根据标签激活
	void AbilityInputTagPressed(FGameplayTag InputTag);
	
	//游戏能力抬起输入根据标签激活
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	
	//end
};
