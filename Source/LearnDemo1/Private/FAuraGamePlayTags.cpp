// Fill out your copyright notice in the Description page of Project Settings.


#include "FAuraGamePlayTags.h"
#include "GameplayTagsManager.h"

#define AddGameplayTag(FGameplayTagVariableName, TagName,TagDevComment)\
 AuraGamePlayTags.SetGameplayTag(\
	(FGameplayTag&&)AuraGamePlayTags.FGameplayTagVariableName,\
	UGameplayTagsManager::Get().AddNativeGameplayTag(#TagName, TagDevComment )\
 );

FAuraGamePlayTags FAuraGamePlayTags::AuraGamePlayTags = FAuraGamePlayTags();





void FAuraGamePlayTags::InitalizNativeGameplayTags()
{
	//获得全局游戏标签管理器 并添加一个GamePlayTag标签

	/*
	 * 主要属性标签
	 * Primary Attributes
	 */

	/*AuraGamePlayTags.Attribute_Primary_Strength = 	UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Strength", TEXT("这是一个主要属性标签，名为力量"));
	AuraGamePlayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Intelligence", TEXT("这是一个主要属性标签，名为力量"));
	AuraGamePlayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Resilience", TEXT("这是一个主要属性标签，名为力量"));
	AuraGamePlayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Vigor", TEXT("这是一个主要属性标签，名为力量"));
	*/
	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Strength, 
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Strength", TEXT("这是一个主要属性标签，名为力量"))
	);

	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Intelligence,
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Intelligence", TEXT("这是一个主要属性标签，名为力量"))
	);
	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Vigor,
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Vigor", TEXT("这是一个主要属性标签，名为力量"))
	);

	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Resilience,
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Resilience", TEXT("这是一个主要属性标签，名为力量"))
	);

	/*
	* 次要属性标签
	 * Secondary Attributes
	 */

	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_Armor , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.Armor", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_ArmorPenetration , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.ArmorPenetration", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_BlockChance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.BlockChance", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_CriticalHitChance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.CriticalHitChance", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_CriticalHitDamage , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.CriticalHitDamage", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_CriticalHitResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.CriticalHitResistance", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_HealthRegeneration , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.HealthRegeneration", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_ManaRegeneration , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.ManaRegeneration", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_MaxHealth , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.MaxHealth", TEXT("这是一个次要属性标签，名为力量")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_MaxMana , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.MaxMana", TEXT("这是一个次要属性标签，名为力量")));



	/* 抵抗属性标签
 * Resistance Attributes
 */


		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_FireResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.FireResistance", TEXT("这是一个抵抗属性标签，名为力量")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_LightningResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.LightningResistance", TEXT("这是一个抵抗属性标签，名为力量")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_ArcaneResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.ArcaneResistance", TEXT("这是一个抵抗属性标签，名为力量")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_PhysicalResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.PhysicalResistance", TEXT("这是一个抵抗属性标签，名为力量")));
	
	/*
	 * 重要属性标签
	 * Vital Attributes
	 */


		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Vital_Health , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Vital.Health", TEXT("这是一个重要属性标签，名为血量")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Vital_Mana , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Vital.Mana", TEXT("这是一个重要属性标签，名为法力")));
	
	//End



	/*
	* 游戏能力标签
	*AbilityInput
	*/
		AddGameplayTag(AbilityInput_LMB, AbilityInput.LMB, L"This is AbilityInput");
		AddGameplayTag(AbilityInput_RMB, AbilityInput.RMB, L"This is AbilityInput");
		AddGameplayTag(AbilityInput_1, AbilityInput.1,L"This is AbilityInput");
		AddGameplayTag(AbilityInput_2, AbilityInput.2,L"This is AbilityInput");
		AddGameplayTag(AbilityInput_3, AbilityInput.3,L"This is AbilityInput");
		AddGameplayTag(AbilityInput_4, AbilityInput.4,L"This is AbilityInput");
		
		
		//End

}

void FAuraGamePlayTags::SetGameplayTag(FGameplayTag&& SroTag, const FGameplayTag& AddNewTag)
{

	SroTag = AddNewTag;
	Tages.Add(&SroTag);
}

#undef AddGameplayTag 
