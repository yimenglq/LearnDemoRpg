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

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	//Override UAttributeSet
	
	//GameplayAttributeData�޸�ǰ
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	//GameplayAttributeData�޸ĺ�
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	//End

public:
	UPROPERTY(ReplicatedUsing = OnRep_Health, EditDefaultsOnly, Category = "Attribute")//����������ֵ��
	FGameplayAttributeData Health;


	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth,EditDefaultsOnly,Category = "Attribute")//��󽡿�������ֵ��
	FGameplayAttributeData MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Mana, EditDefaultsOnly, Category = "Attribute")//����
	FGameplayAttributeData Mana;


	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, EditDefaultsOnly, Category = "Attribute")//�����
	FGameplayAttributeData MaxMana;
};
