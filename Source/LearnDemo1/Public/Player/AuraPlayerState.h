// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include"GameplayAbilities\Public\AttributeSet.h"
#include"GameplayAbilities\Public\AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraPlayerState();

	
	//Override  IAbilitySystemInterface 相关
	//获得GAS组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获得属性集合
	UAttributeSet* GetAttributeSet();
	// End  



protected:

	UPROPERTY()//GAS组件
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()//属性集合
	TObjectPtr<UAttributeSet> AttributeSet;
};
