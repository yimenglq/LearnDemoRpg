// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

struct	FGameplayTagContainer;


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectTagsSignature, FGameplayTagContainer&/* AssetTags */);

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	//��GAS�ؼ��¼�
	void AbiltyActorInfoSet();

	//��ϷЧ������ʱ�������ʲ���ǩ�����ಥ����
	FEffectTagsSignature OnEffectTagsSignature;


protected:

	//Ч��Ӧ��ʱ����
	virtual void EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

private:

	//�Ƿ��Ѿ���ʼ����
	bool bInited = false;

};
