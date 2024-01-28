// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <FAuraGamePlayTags.h>
#include <AbilitySystem/GameAbility/AuraGameAbility.h>

void UAuraAbilitySystemComponent::AbiltyActorInfoSet()
{
	if (bInited) return;


	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	bInited = true;

	//���Դ���
	FAuraGamePlayTags::Get().Attribute_Primary_Strength.GetTagName();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FAuraGamePlayTags::Get().Attribute_Primary_Strength.GetTagName().ToString());
}

void UAuraAbilitySystemComponent::AddCharacterAbilityes(TArray<TSubclassOf<UGameplayAbility>>& Abilityes)
{
	for (TSubclassOf<UGameplayAbility> Gabilityclass : Abilityes)
	{
		FGameplayAbilitySpec AbilitySpec(Gabilityclass,1.f);

		AbilitySpec.DynamicAbilityTags.AddTag( Cast<UAuraGameAbility>(AbilitySpec.Ability)->StartupTag );

		////����������������������	
		FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = GiveAbility(AbilitySpec);
		//�������������
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
	
	//�������AssetTags(�ʲ���ǩ)
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);
	
	OnEffectTagsSignature.Broadcast(TagContainer);
}
