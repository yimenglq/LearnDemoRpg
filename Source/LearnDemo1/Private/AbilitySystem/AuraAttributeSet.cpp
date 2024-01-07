// Fill out your copyright notice in the Description page of Project Settings.

#include <Net/UnrealNetwork.h>
#include"GameplayAbilities\Public\AbilitySystemComponent.h"

#include "AbilitySystem/AuraAttributeSet.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50);
	InitMaxHealth(100);
	InitMana(90);
	InitMaxMana(100);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//×¢²á¸´ÖÆ
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	//End
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
