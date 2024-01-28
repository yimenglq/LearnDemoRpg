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

	
	//Override  IAbilitySystemInterface ���
	//���GAS���
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//������Լ���
	UAttributeSet* GetAttributeSet();
	// End  



protected:

	UPROPERTY()//GAS���
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()//���Լ���
	TObjectPtr<UAttributeSet> AttributeSet;
};
