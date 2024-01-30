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

	//绑定GAS控件事件
	void AbiltyActorInfoSet();

	//游戏效果附加时触发的资产标签容器多播代理
	FEffectTagsSignature OnEffectTagsSignature;
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void AbilityInputTagHold(const FGameplayTag& InputTag);

	//给角色添加多个游戏能力
	void AddCharacterAbilityes(TArray<TSubclassOf<UGameplayAbility>> & Abilityes);
	//给角色添加单个游戏能力
	void AddCharacterAbility(TSubclassOf<UGameplayAbility>& Abilityes);
protected:

	//效果应用时调用
	virtual void EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

private:

	//是否已经初始化绑定
	bool bInited = false;

};
