// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameAbility.generated.h"

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAuraGameAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	//���������ı�ǩ
	UPROPERTY(EditDefaultsOnly,Category= " AuraGameAbility")
	FGameplayTag StartupTag;

	//Override UGameplayAbility
	
	/**��������  ��Ҫֱ�ӵ���*/
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	//End

};
