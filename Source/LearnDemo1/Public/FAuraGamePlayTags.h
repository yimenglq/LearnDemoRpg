// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
class LEARNDEMO1_API FAuraGamePlayTags
{
public:
	//获取唯一实例
	static FAuraGamePlayTags& Get() { return AuraGamePlayTags; }

	//向标签管理器初始化需要添加的标签
	static void	InitalizNativeGameplayTags();

	

	void SetGameplayTag(FGameplayTag&& SroTag,const FGameplayTag& AddNewTag);

	TArray<const FGameplayTag*> Tages;

	/*
	 * 主要属性标签
	 * Primary Attributes
	 */

	FGameplayTag Attribute_Primary_Strength;

	FGameplayTag Attribute_Primary_Intelligence;

	FGameplayTag Attribute_Primary_Resilience;

	FGameplayTag Attribute_Primary_Vigor;

	/*
	* 次要属性标签
	 * Secondary Attributes
	 */

	FGameplayTag Attribute_Secondary_Armor;

	FGameplayTag Attribute_Secondary_ArmorPenetration;

	FGameplayTag Attribute_Secondary_BlockChance;

	FGameplayTag Attribute_Secondary_CriticalHitChance;

	FGameplayTag Attribute_Secondary_CriticalHitDamage;

	FGameplayTag Attribute_Secondary_CriticalHitResistance;

	FGameplayTag Attribute_Secondary_HealthRegeneration;


	FGameplayTag Attribute_Secondary_ManaRegeneration;

	FGameplayTag Attribute_Secondary_MaxHealth;

	FGameplayTag Attribute_Secondary_MaxMana;



	/* 抵抗属性标签
	 * Resistance Attributes
	 */
	FGameplayTag Attribute_Resistance_FireResistance;

	FGameplayTag Attribute_Resistance_LightningResistance;

	FGameplayTag Attribute_Resistance_ArcaneResistance;

	FGameplayTag Attribute_Resistance_PhysicalResistance;


	/*
	* 重要属性标签
	* Vital Attributes
	*/

	FGameplayTag Attribute_Vital_Health;

	FGameplayTag Attribute_Vital_Mana;



protected:
	



private:

	//唯一实例
	static FAuraGamePlayTags AuraGamePlayTags;


};
