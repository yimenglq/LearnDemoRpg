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
*  人形基类 
* 
*/

UCLASS()
class LEARNDEMO1_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();

	//Override  IAbilitySystemInterface 相关
	//获得GAS组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return  AbilitySystemComponent; };
	//获得属性集合
	UAttributeSet* GetAttributeSet() { return AttributeSet; };
	// End  
	// 
	//初始化GAS组件
	virtual void InitAbilityActorInfo();

protected:
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,Category="AuraCharacterBase")//武器骨骼网格体
	TObjectPtr<USkeletalMeshComponent> Weapons;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//GAS组件
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//属性集合
	TObjectPtr<UAttributeSet> AttributeSet;

};
