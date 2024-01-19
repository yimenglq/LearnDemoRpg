// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

//宏内含有  get set init 等方法
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 属性集
 */
UCLASS()
class LEARNDEMO1_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:
	UAuraAttributeSet();

	// override UObject   
	// 注册复制
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
	
	//GameplayAttributeData修改前
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	//GameplayAttributeData修改后
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	//End

public:
	UPROPERTY(ReplicatedUsing = OnRep_Health, EditDefaultsOnly, Category = "Attribute")//健康（生命值）
	FGameplayAttributeData Health;


	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth,EditDefaultsOnly,Category = "Attribute")//最大健康（生命值）
	FGameplayAttributeData MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Mana, EditDefaultsOnly, Category = "Attribute")//法力
	FGameplayAttributeData Mana;


	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, EditDefaultsOnly, Category = "Attribute")//最大法力
	FGameplayAttributeData MaxMana;
};
