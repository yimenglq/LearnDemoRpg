// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilities\Public\ActiveGameplayEffectHandle.h"
#include "AEffectActo.generated.h"


/*
*	������ϷЧ����ö�ٲ���
*/


UENUM()
enum class EEffectTriggerPolicy: uint8  //����Ч������ //һ�ֽ�
{
	//��ʼ�ص�ʱ����
	BeginOvelap,
	//�����ص�ʱ����
	EndOvelap,
	//������
	NoTrigger
};


UENUM()
enum class EEffectRemovePolicy : uint8 //ɾ��Ч������ //һ�ֽ�
{
	//��ʼ�ص�ʱɾ��
	BeginOvelapRemove,
	//�����ص�ʱɾ��
	EndOvelapRemove,
	//��ɾ��
	NoRemove
};





class UAbilitySystemComponent;

UCLASS()
class LEARNDEMO1_API AAEffectActo : public AActor
{
	GENERATED_BODY()
	
public:	

	AAEffectActo();

protected:

	virtual void BeginPlay() override;

	//virtual void PostInitializeComponents() override;
	
	//��ײ��ʼ�ص��¼�
	UFUNCTION(BlueprintCallable)
	virtual void BeginOvelap(AActor* OtherActor);

	//��ײ�����ص��¼�
	UFUNCTION(BlueprintCallable)
	virtual void EndOverlap(AActor* OtherActor);

    // �����ϷЧ����Ŀ����
	UFUNCTION(BlueprintCallable, Category = "AEffectActo")
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	// ɾ����ϷЧ����Ŀ����
	UFUNCTION(BlueprintCallable, Category = "AEffectActo")
	void RemoveActiveGameplayEffectToTarget(AActor* Target);

protected:

	//������ϷЧ�� �� ��Ӧ��GAS���
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent* > ActiveGameplayEffectHandles;


	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "AEffectActo|Instant")// ��ʱ������������ϷЧ��
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Instant")
	EEffectTriggerPolicy InstantEffectTriggerPolicy = EEffectTriggerPolicy::NoTrigger;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Duration")// �г���ʱ�����ϷЧ��
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Duration")
	EEffectTriggerPolicy DurationEffectTriggerPolicy = EEffectTriggerPolicy::NoTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Lasting")// �־��Ե���ϷЧ��
	TSubclassOf<UGameplayEffect> LastingGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Lasting")
	EEffectTriggerPolicy LastingEffectTriggerPolicy = EEffectTriggerPolicy::NoTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Lasting")
	EEffectRemovePolicy  LastingEffectRemovePolicy = EEffectRemovePolicy::EndOvelapRemove;

};
