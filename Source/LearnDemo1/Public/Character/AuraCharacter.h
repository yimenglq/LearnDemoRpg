// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
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
	
protected:
	virtual void BeginPlay() override;

	/** PlayerState 改变时 复制回调函数*/
	virtual void OnRep_PlayerState() override;

	//当该Pawn被控制时  仅服务器调用
	virtual void PossessedBy(AController* NewController) override;

	


protected:
	//弹簧臂组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<	USpringArmComponent>  SpringArmComp;

	//摄像机组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr < UCameraComponent> CameraComp;

private:

	//初始化GAS组件
	void	InitAbilityActorInfo();
};
