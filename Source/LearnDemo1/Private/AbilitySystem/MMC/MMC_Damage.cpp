// Fill out your copyright notice in the Description page of Project Settings.

#include"AbilitySystemComponent.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include "AbilitySystem/MMC/MMC_Damage.h"


UMMC_Damage::UMMC_Damage()
{
    //捕获
    IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
    IntelligenceDef.bSnapshot = false;


    RelevantAttributesToCapture.Add(IntelligenceDef);

}

float UMMC_Damage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

    //目标当前血量的 25% 的伤害 
    FGameplayEffectSpecHandle TagrESH = Spec.TargetEffectSpecs[0];
    const UAuraAttributeSet* set = CastChecked<UAuraAttributeSet>(TagrESH.Data.Get()->GetContext().Get()->GetInstigatorAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

   // const UAuraAttributeSet* set =  CastChecked<UAuraAttributeSet>(Spec.GetEffectContext().Get()->GetInstigatorAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;
    float Int = 0.f;
    
    //Spec.GetSetByCallerMagnitude
    GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Int);
    return set->GetHealth() * 0.25;
}
