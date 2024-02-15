// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/ExecutionCalcu_Damage.h"
#include"AbilitySystem\AuraAttributeSet.h"

struct AuraDamageStatic
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);

	AuraDamageStatic()
	{
		//��׽����
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MaxHealth, Target, false);

	}

};
static AuraDamageStatic& DamageStatic()
{
	static AuraDamageStatic ADS;

	return ADS;
}

UExecutionCalcu_Damage::UExecutionCalcu_Damage()
{
	//�������д  �ſɲ���
	RelevantAttributesToCapture.Add(DamageStatic().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatic().MaxHealthDef);

}


void UExecutionCalcu_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* GtcTarget = Spec.CapturedTargetTags.GetAggregatedTags();
	const FGameplayTagContainer* GtcSour = Spec.CapturedSourceTags.GetAggregatedTags();
	FAggregatorEvaluateParameters FEP;
	FEP.SourceTags = GtcSour;
	FEP.TargetTags = GtcTarget;
	float MaxHealth = 0.f;
	//���ݲ�������� ��ȡֵ
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().MaxHealthDef, FEP, MaxHealth);
	float Damage = 100.f;
	Damage = Damage + (MaxHealth * 0.25f) - (MaxHealth * 0.1f);
	Damage = Damage > 0.f ? Damage : 0;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage));
	

}
