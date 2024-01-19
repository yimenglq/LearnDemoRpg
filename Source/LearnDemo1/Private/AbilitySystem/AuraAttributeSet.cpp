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

	//注册复制
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

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	FGameplayAttributeData* AttributeData = Attribute.GetGameplayAttributeData(this);
	//限制血量
	if (AttributeData == &Health)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	//限制法力
	if (AttributeData == &Mana)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}

}

void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	const FGameplayAttributeData* AttributeData = Attribute.GetGameplayAttributeData(this);
	//限制血量
	if (AttributeData == &Health)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	//限制法力
	if (AttributeData == &Mana)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//Debug绘制到屏幕上
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("Hello World")));
}




