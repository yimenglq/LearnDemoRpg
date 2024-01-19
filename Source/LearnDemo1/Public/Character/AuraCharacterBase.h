// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include"GameplayAbilities\Public\AttributeSet.h"
#include"GameplayAbilities\Public\AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include"Components\CapsuleComponent.h"

#include "AuraCharacterBase.generated.h"



/*
*  ���λ��� 
* 
*/

UCLASS()
class LEARNDEMO1_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();

	//Override  IAbilitySystemInterface ���
	//���GAS���
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return  AbilitySystemComponent; };
	//������Լ���
	UAttributeSet* GetAttributeSet() { return AttributeSet; };
	// End  
	// 
	//��ʼ��GAS���
	virtual void InitAbilityActorInfo();

protected:
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,Category="AuraCharacterBase")//��������������
	TObjectPtr<USkeletalMeshComponent> Weapons;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//GAS���
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//���Լ���
	TObjectPtr<UAttributeSet> AttributeSet;

};
