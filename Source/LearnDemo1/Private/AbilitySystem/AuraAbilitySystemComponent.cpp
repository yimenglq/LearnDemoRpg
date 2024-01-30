// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <FAuraGamePlayTags.h>
#include <AbilitySystem/GameAbility/AuraGameAbility.h>

void UAuraAbilitySystemComponent::AbiltyActorInfoSet()
{
	if (bInited) return;


	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	bInited = true;

	//测试代码
	FAuraGamePlayTags::Get().Attribute_Primary_Strength.GetTagName();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FAuraGamePlayTags::Get().Attribute_Primary_Strength.GetTagName().ToString());
}




void UAuraAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHold(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	//用于阻止我们在迭代技能时从技能系统组件中删除技能 
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//判断启动能力标签是否相符
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				//尝试启动能力
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}


void UAuraAbilitySystemComponent::AddCharacterAbilityes(TArray<TSubclassOf<UGameplayAbility>>& Abilityes)
{
	
	for (TSubclassOf<UGameplayAbility> Gabilityclass : Abilityes)
	{
		FGameplayAbilitySpec AbilitySpec(Gabilityclass,1.f);

		AbilitySpec.DynamicAbilityTags.AddTag( Cast<UAuraGameAbility>(AbilitySpec.Ability)->StartupTag );

		////给能力组件添加能力不启动	
		FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = GiveAbility(AbilitySpec);
		//添加能力且启动
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}

}

void UAuraAbilitySystemComponent::AddCharacterAbility(TSubclassOf<UGameplayAbility>& Abilityes)
{
	if (!Abilityes) return;
	
	FGameplayAbilitySpec AbilitySpec(Abilityes);
	AbilitySpec.DynamicAbilityTags.AddTag(
		Cast<UAuraGameAbility>(Abilityes)->StartupTag
	);

	GiveAbility(AbilitySpec);

}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("UAuraAbilitySystemComponent::EffectApplied "));
	
	//获得所有AssetTags(资产标签)
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);
	
	OnEffectTagsSignature.Broadcast(TagContainer);
}
