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
	//��ȡΨһʵ��
	static FAuraGamePlayTags& Get() { return AuraGamePlayTags; }

	//���ǩ��������ʼ����Ҫ��ӵı�ǩ
	static void	InitalizNativeGameplayTags();

	
	//����ע��ı�ǩ ��ӵ������� �� ָ���ı�ǩ�� FGameplayTag ������
	void SetGameplayTag(FGameplayTag&& SroTag,const FGameplayTag& AddNewTag);

	//���Ǹ����������б�ǩ�ļ���
	TArray<const FGameplayTag*> Tages;

	/*
	 * ��Ҫ���Ա�ǩ
	 * Primary Attributes
	 */

	FGameplayTag Attribute_Primary_Strength;

	FGameplayTag Attribute_Primary_Intelligence;

	FGameplayTag Attribute_Primary_Resilience;

	FGameplayTag Attribute_Primary_Vigor;

	/*
	* ��Ҫ���Ա�ǩ
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



	/* �ֿ����Ա�ǩ
	 * Resistance Attributes
	 */
	FGameplayTag Attribute_Resistance_FireResistance;

	FGameplayTag Attribute_Resistance_LightningResistance;

	FGameplayTag Attribute_Resistance_ArcaneResistance;

	FGameplayTag Attribute_Resistance_PhysicalResistance;


	/*
	* ��Ҫ���Ա�ǩ
	* Vital Attributes
	*/

	FGameplayTag Attribute_Vital_Health;

	FGameplayTag Attribute_Vital_Mana;


	/*
	* ��Ϸ������ǩ
	* AbilityInput
	*/
	FGameplayTag AbilityInput_LMB;
	FGameplayTag AbilityInput_RMB;
	FGameplayTag AbilityInput_1;
	FGameplayTag AbilityInput_2;
	FGameplayTag AbilityInput_3;
	FGameplayTag AbilityInput_4;


	FGameplayTag Damage;

	FGameplayTag HitReact;

	FGameplayTag Death;

protected:
	



private:

	//Ψһʵ��
	static FAuraGamePlayTags AuraGamePlayTags;


};
