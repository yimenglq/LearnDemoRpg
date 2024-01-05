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

public:
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;//����������ֵ��


	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;//��󽡿�������ֵ��
};
