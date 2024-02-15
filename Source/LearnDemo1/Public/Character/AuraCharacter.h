// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include"Iterface\CombatInterface.h"
#include"Player\AuraPlayerState.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 *  玩家人形
 */
UCLASS()
class LEARNDEMO1_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

		
public:
	AAuraCharacter();
	
	//Override  AAuraCharacterBase
	virtual void InitAbilityActorInfo() override;

	//End
	
	//Override ICombatInterface
	virtual int32	GetLevel()const override {	if (AAuraPlayerState* PS = Cast<AAuraPlayerState>(GetPlayerState()) )  return PS->Level;  else   return 0; };
	
	virtual int32 BP_GetLevel_Implementation() override { return GetLevel(); };
	//End


protected:
	virtual void BeginPlay() override;

	/** PlayerState 改变时 复制回调函数*/
	virtual void OnRep_PlayerState() override;

	//当该Pawn被控制时  仅服务器调用
	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaSeconds)override;


protected:
	//弹簧臂组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<	USpringArmComponent>  SpringArmComp;

	//摄像机组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr < UCameraComponent> CameraComp;

private:

	//是否已经初始化绑定
	bool bInited = false;

};
