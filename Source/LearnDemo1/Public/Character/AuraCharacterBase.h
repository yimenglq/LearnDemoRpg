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
#include"Iterface\CombatInterface.h"
#include "AuraCharacterBase.generated.h"




/*
*  人形基类 
* 
*/

UCLASS()
class LEARNDEMO1_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface, public ICombatInterface
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
	
	//Override ICombatInterface 
	
	//死亡
	virtual void Die() override;

	UFUNCTION( NetMulticast, Reliable)
	virtual void SeverDie();

	
	//End
	
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

	void Dissolve();

	//在蓝图使用时间线设置动态实例参数
	UFUNCTION(BlueprintImplementableEvent)
	void SetMeshDissolveTimeLine(UMaterialInstanceDynamic* MIDynamic);

	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponsDissolveTimeLine(UMaterialInstanceDynamic* MIDynamic);


protected:
	
	virtual void BeginPlay() override;

protected:

	//网格体溶解
	UPROPERTY(EditAnywhere,Category="AuraCharacterBase|MaterialInstance")
	TObjectPtr<UMaterialInstance> MeshDissolve;

	//武器溶解
	UPROPERTY(EditAnywhere, Category = "AuraCharacterBase|MaterialInstance")
	TObjectPtr<UMaterialInstance>  WeaponsDissolve;


	//死亡时销毁的时间
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AuraCharacterBase|LifeSpan(销魂时间)")
	float LifeSpan = 5.f;

	//受击动画蒙太奇
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AuraCharacterBase|HitReact")
	TObjectPtr<UAnimMontage> HitReactAnimMontage;

	//死亡动画蒙太奇
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AuraCharacterBase|HitReact")
	TObjectPtr<UAnimMontage> DeathAnimMontage;

	//角色职业
	UPROPERTY(EditAnywhere,Category = "AuraCharacterBase")
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
