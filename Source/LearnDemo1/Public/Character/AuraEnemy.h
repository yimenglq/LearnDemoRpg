// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include"Iterface\HighLightIterface.h"
#include"Iterface\CombatInterface.h"
#include <Components/WidgetComponent.h>
#include "AuraEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuraAttributeDelegate, float, NewValue);

/**
 * 敌方NPC人形
 */
UCLASS(Blueprintable)
class LEARNDEMO1_API AAuraEnemy : public AAuraCharacterBase, public IHighLightIterface, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();


	//overide IHighLightIterface

	//开启后处理描边
	virtual void OpenHighLight() override;
	//关闭后处理描边
	virtual void CloceHighLight() override;
	//End 

	//Override ICombatInterface
	
	virtual int32 GetLevel() const  override { return Level; };

	virtual int32 BP_GetLevel_Implementation() override { return GetLevel(); };
	//End

	//Override  AAuraCharacterBase
	virtual void InitAbilityActorInfo() override;
	//初始化属性
	virtual void InitAttributSet() override;
	//End


	UPROPERTY(BlueprintAssignable)
	FAuraAttributeDelegate OnHealthAttributeDelegate;
	UPROPERTY(BlueprintAssignable)
	FAuraAttributeDelegate OnMaxHealthAttributeDelegate;
protected:
	virtual void BeginPlay() override;


	//角色等级
	UPROPERTY(EditAnywhere, Category = "00-CharacterBase")
	int32 Level = 1;


	//构件组件在 3D 环境中提供了一个表面，用于在该图面上渲染通常渲染到屏幕上的构件。
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;



};
