// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include"Iterface\HighLightIterface.h"
#include"Iterface\CombatInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 敌方NPC人形
 */
UCLASS()
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


	//Override  AAuraCharacterBase
	virtual void InitAbilityActorInfo() override;

	//End

protected:
	virtual void BeginPlay() override;

};
