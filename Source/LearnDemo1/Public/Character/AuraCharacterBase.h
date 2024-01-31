// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include"GameplayAbilities\Public\AttributeSet.h"
#include"GameplayAbilities\Public\AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include"Components\CapsuleComponent.h"
#include <AbilitySystem/DA/OccupationInfoDataAsset.h>
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

	//初始化属性
	virtual void InitAttributSet();

	// 添加游戏效果到自己上
	UFUNCTION(BlueprintCallable, Category = "AEffectActo")
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass);

	void AddCharacterAbility(TSubclassOf<UGameplayAbility>& AbilityClass);
	void AddCharacterAbilityes(	TArray<	TSubclassOf<UGameplayAbility> > & AbilityClasses);
	
	void AddCharacterAbilityes();

	TObjectPtr<USkeletalMeshComponent> GetWeapons()const { return Weapons; }


protected:
	
	virtual void BeginPlay() override;

protected:

	//角色职业
	UPROPERTY(EditAnywhere,Category = "00-CharacterBase")
	EOccupationType OccupationType = EOccupationType::Warrior;


	//游戏开始时启动的游戏能力
	UPROPERTY(EditAnywhere,Category = "AuraCharacterBase|Ability")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilityes;


	//即时
	UPROPERTY(EditDefaultsOnly,Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> InitPrimaryEffect;//初始化主要属性
	
	//持久
	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> lastingSecondaryEffect;//次要属性
	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> lastingResistanceEffect;//抵抗属性
	//即时
	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> InitVitalEffect;//初始化重要属性


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AuraCharacterBase")//武器骨骼网格体
	TObjectPtr<USkeletalMeshComponent> Weapons;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//GAS组件
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//属性集合
	TObjectPtr<UAttributeSet> AttributeSet;


	
};
