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
	//���ȫ����Ϸ��ǩ������ �����һ��GamePlayTag��ǩ

	/*
	 * ��Ҫ���Ա�ǩ
	 * Primary Attributes
	 */

	/*AuraGamePlayTags.Attribute_Primary_Strength = 	UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Strength", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"));
	AuraGamePlayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Intelligence", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"));
	AuraGamePlayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Resilience", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"));
	AuraGamePlayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Vigor", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"));
	*/
	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Strength, 
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Strength", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"))
	);

	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Intelligence,
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Intelligence", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"))
	);
	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Vigor,
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Vigor", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"))
	);

	AuraGamePlayTags.SetGameplayTag(
		(FGameplayTag&&)AuraGamePlayTags.Attribute_Primary_Resilience,
		UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Primary.Resilience", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����"))
	);

	/*
	* ��Ҫ���Ա�ǩ
	 * Secondary Attributes
	 */

	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_Armor , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.Armor", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_ArmorPenetration , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.ArmorPenetration", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_BlockChance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.BlockChance", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_CriticalHitChance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.CriticalHitChance", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_CriticalHitDamage , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.CriticalHitDamage", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_CriticalHitResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.CriticalHitResistance", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_HealthRegeneration , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.HealthRegeneration", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_ManaRegeneration , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.ManaRegeneration", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_MaxHealth , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.MaxHealth", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Secondary_MaxMana , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Secondary.MaxMana", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));



	/* �ֿ����Ա�ǩ
 * Resistance Attributes
 */


		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_FireResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.FireResistance", TEXT("����һ���ֿ����Ա�ǩ����Ϊ����")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_LightningResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.LightningResistance", TEXT("����һ���ֿ����Ա�ǩ����Ϊ����")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_ArcaneResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.ArcaneResistance", TEXT("����һ���ֿ����Ա�ǩ����Ϊ����")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Resistance_PhysicalResistance , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Resistance.PhysicalResistance", TEXT("����һ���ֿ����Ա�ǩ����Ϊ����")));
	
	/*
	 * ��Ҫ���Ա�ǩ
	 * Vital Attributes
	 */


		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Vital_Health , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Vital.Health", TEXT("����һ����Ҫ���Ա�ǩ����ΪѪ��")));
		AuraGamePlayTags.SetGameplayTag((FGameplayTag&&)AuraGamePlayTags.Attribute_Vital_Mana , UGameplayTagsManager::Get().AddNativeGameplayTag("Attributes.Vital.Mana", TEXT("����һ����Ҫ���Ա�ǩ����Ϊ����")));
	
	//End



	/*
	* ��Ϸ������ǩ
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
