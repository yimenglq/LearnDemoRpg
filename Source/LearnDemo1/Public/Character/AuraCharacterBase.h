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

	//��ʼ������
	virtual void InitAttributSet();

	// �����ϷЧ�����Լ���
	UFUNCTION(BlueprintCallable, Category = "AEffectActo")
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass);

	void AddCharacterAbility(TSubclassOf<UGameplayAbility>& AbilityClass);
	void AddCharacterAbilityes(	TArray<	TSubclassOf<UGameplayAbility> > & AbilityClasses);
	
	void AddCharacterAbilityes();

	TObjectPtr<USkeletalMeshComponent> GetWeapons()const { return Weapons; }


protected:
	
	virtual void BeginPlay() override;

protected:

	//��ɫְҵ
	UPROPERTY(EditAnywhere,Category = "00-CharacterBase")
	EOccupationType OccupationType = EOccupationType::Warrior;


	//��Ϸ��ʼʱ��������Ϸ����
	UPROPERTY(EditAnywhere,Category = "AuraCharacterBase|Ability")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilityes;


	//��ʱ
	UPROPERTY(EditDefaultsOnly,Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> InitPrimaryEffect;//��ʼ����Ҫ����
	
	//�־�
	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> lastingSecondaryEffect;//��Ҫ����
	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> lastingResistanceEffect;//�ֿ�����
	//��ʱ
	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> InitVitalEffect;//��ʼ����Ҫ����


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AuraCharacterBase")//��������������
	TObjectPtr<USkeletalMeshComponent> Weapons;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//GAS���
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "AuraCharacterBase")//���Լ���
	TObjectPtr<UAttributeSet> AttributeSet;


	
};
