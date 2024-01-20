// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

//���ں���  get set init �ȷ���
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * ���Լ�
 */
UCLASS()
class LEARNDEMO1_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:
	UAuraAttributeSet();

	// override UObject   
	// ע�Ḵ��
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	//End


	//Override UAttributeSet
	
	//GameplayAttributeData�޸�ǰ
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	//GameplayAttributeData�޸ĺ�
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	//End




public:

	/*
	 * ��Ҫ����
	 * Primary Attributes
	 */


	//����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category = "Attributes")
	FGameplayAttributeData Strength;
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);
	
	//End

	//���� 
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Intelligence, Category = "Attributes")
	FGameplayAttributeData Intelligence;
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	//End
	
	//����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resilience, Category = "Attributes")
	FGameplayAttributeData Resilience;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	//End

	//����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Vigor, Category = "Attributes")
	FGameplayAttributeData Vigor;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	
	//End


	/*
	* ��Ҫ����
	 * Secondary Attributes
	 */

	//װ��
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor, Category = "Attributes")
	FGameplayAttributeData Armor;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	//End

	//װ�״�͸
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ArmorPenetration, Category = "Attributes")
	FGameplayAttributeData ArmorPenetration;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	//End

	//�赲����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_BlockChance, Category = "Attributes")
	FGameplayAttributeData BlockChance;
	
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	//End

	//��������
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitChance, Category = "Attributes")
	FGameplayAttributeData CriticalHitChance;
	
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	//End

	//�����˺�
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Attributes")
	FGameplayAttributeData CriticalHitDamage;
	
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	//End

	//��������
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Attributes")
	FGameplayAttributeData CriticalHitResistance;
	
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	//End

	//�������� (Ѫ����������)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegeneration, Category = "Attributes")
	FGameplayAttributeData HealthRegeneration;
	
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	//End

	//������������
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ManaRegeneration, Category = "Attributes")
	FGameplayAttributeData ManaRegeneration;
	
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	//End
	
	//��󽡿�
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	//End

	//�����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	//End
	
	/* �ֿ�����
	 * Resistance Attributes
	 */

	//�ͻ���  ���濹��
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_FireResistance, Category = "Attributes")
	FGameplayAttributeData FireResistance;
	
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireResistance);

	//End

	//������ �׵翹��
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_LightningResistance, Category = "Attributes")
	FGameplayAttributeData LightningResistance;
	
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightningResistance);

	//End

	//��������
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ArcaneResistance, Category = "Attributes")
	FGameplayAttributeData ArcaneResistance;
	
	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArcaneResistance);

	//End

	//������
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_PhysicalResistance, Category = "Attributes")
	FGameplayAttributeData PhysicalResistance;

	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalResistance);
	
	//End



	/*
	* ��Ҫ����
	 * Vital Attributes
	 */

	//����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	//End

	//����
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana, Category = "Attributes")
	FGameplayAttributeData Mana;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	
	//End


	/*
	 * Meta Attributes
	 */

	/*UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_IncomingDamage, Category = "Attributes")
	FGameplayAttributeData IncomingDamage;
	UFUNCTION()
	void OnRep_IncomingDamage(const FGameplayAttributeData& OldIncomingDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);


	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_IncomingXP, Category = "Attributes")
	FGameplayAttributeData IncomingXP;
	UFUNCTION()
	void OnRep_IncomingXP(const FGameplayAttributeData& OldIncomingXP);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingXP);*/

	

};
