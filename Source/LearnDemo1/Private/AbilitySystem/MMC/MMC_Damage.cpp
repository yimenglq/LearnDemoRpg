// Fill out your copyright notice in the Description page of Project Settings.

#include"AbilitySystemComponent.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include "AbilitySystem/MMC/MMC_Damage.h"


float UMMC_Damage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

    //目标当前血量的 25% 的伤害 
    FGameplayEffectSpecHandle TagrESH = Spec.TargetEffectSpecs[0];
    const UAuraAttributeSet* set = CastChecked<UAuraAttributeSet>(TagrESH.Data.Get()->GetContext().Get()->GetInstigatorAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

   // const UAuraAttributeSet* set =  CastChecked<UAuraAttributeSet>(Spec.GetEffectContext().Get()->GetInstigatorAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

    
    return set->GetHealth() * 0.25;
}
