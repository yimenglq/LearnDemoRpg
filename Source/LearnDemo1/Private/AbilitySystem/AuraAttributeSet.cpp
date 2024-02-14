// Fill out your copyright notice in the Description page of Project Settings.

#include <Net/UnrealNetwork.h>
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include"GameplayEffectExtension.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include <FAuraGamePlayTags.h>

UAuraAttributeSet::UAuraAttributeSet()
{
	InitTagsToAttributeSignature();
}

void UAuraAttributeSet::InitTagsToAttributeSignature()
{
	FAuraGamePlayTags& AGPT = FAuraGamePlayTags::Get();
	auto lbdFunPtr = [this](FGameplayTag& tag, auto* Funptr)
		{
			FAttributeSignature AS;
			AS.BindStatic(Funptr);
			TagsToAttributeSignature.Add(tag, AS);
		};

	/*
 * 主要属性
 * Primary Attributes
 */

	lbdFunPtr(AGPT.Attribute_Primary_Strength, GetStrengthAttribute);
	lbdFunPtr(AGPT.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	lbdFunPtr(AGPT.Attribute_Primary_Resilience, GetResilienceAttribute);
	lbdFunPtr(AGPT.Attribute_Primary_Vigor, GetVigorAttribute);
	
	
	/*
* 次要属性
 * Secondary Attributes
 */
	lbdFunPtr(AGPT.Attribute_Secondary_Armor, GetArmorAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	lbdFunPtr(AGPT.Attribute_Secondary_MaxMana, GetMaxManaAttribute);
	//End

	/* 抵抗属性
	 * Resistance Attributes
	 */
	lbdFunPtr(AGPT.Attribute_Resistance_FireResistance, GetFireResistanceAttribute);
	lbdFunPtr(AGPT.Attribute_Resistance_LightningResistance, GetLightningResistanceAttribute);
	lbdFunPtr(AGPT.Attribute_Resistance_ArcaneResistance, GetArcaneResistanceAttribute);
	lbdFunPtr(AGPT.Attribute_Resistance_PhysicalResistance, GetPhysicalResistanceAttribute);

	/*
	* 重要属性
	 * Vital Attributes
	 */
	lbdFunPtr(AGPT.Attribute_Vital_Health, GetHealthAttribute);
	//lbdFunPtr(AGPT.Attribute_Vital_Mana, GetManaAttribute);
	



	InitAttributeSetAndTag(Mana, Attribute_Vital_Mana);
	//end



	
	

}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//注册复制
	// Primary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Resistance Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);

	// Vital Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	//End
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

TArray<FGameplayTag> UAuraAttributeSet::GetAttributeTages() const
{

	TArray<FGameplayTag> Tags;

	for ( auto par : TagsToAttributeSignature)
	{
		Tags.Add(par.Key);
	}

	return Tags;
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//Debug绘制到屏幕上
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("Hello World")));


	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{

			float Damage = GetIncomingDamage();
			SetIncomingDamage(0.f);
			if (Damage > 0.f)
			{
				float NewHealth = GetHealth() - Damage;
				SetHealth( FMath::Clamp(NewHealth, 0, GetMaxHealth()));
				bool bFalt = NewHealth <= 0.f;
				if (!bFalt)
				{
					FGameplayTagContainer TagC(FAuraGamePlayTags::Get().HitReact);
					//根据标签激活游戏能力
					GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(TagC);

				}
				else
				{
					//血量归零时
					FGameplayTagContainer TagC(FAuraGamePlayTags::Get().Death);
					//根据标签激活游戏能力
					GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(TagC);
				}
			}
	}

}




void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}



void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireResistance, OldFireResistance);
}

void UAuraAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LightningResistance, OldLightningResistance);
}

void UAuraAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArcaneResistance, OldArcaneResistance);
}

void UAuraAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void UAuraAttributeSet::OnRep_IncomingDamage(const FGameplayAttributeData& OldIncomingDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, IncomingDamage, OldIncomingDamage);
}


