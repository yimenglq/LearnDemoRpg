// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Actor/AEffectActo.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystemBlueprintLibrary.h>

// Sets default values
AAEffectActo::AAEffectActo()
{
	PrimaryActorTick.bCanEverTick = false;
	
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));

}


void AAEffectActo::BeginPlay()
{
	Super::BeginPlay();
	
}



void AAEffectActo::BeginOvelap(AActor* OtherActor)
{
	if (InstantEffectTriggerPolicy == EEffectTriggerPolicy::BeginOvelap)
	{
		ApplyEffectToTarget(OtherActor, InstantGameplayEffectClass);
	}
	
	if (DurationEffectTriggerPolicy == EEffectTriggerPolicy::BeginOvelap)
	{
		ApplyEffectToTarget(OtherActor, DurationGameplayEffectClass);
	}

	if (LastingEffectTriggerPolicy == EEffectTriggerPolicy::BeginOvelap)
	{
		ApplyEffectToTarget(OtherActor, LastingGameplayEffectClass);
	}


}

void AAEffectActo::EndOverlap(AActor* OtherActor)
{
	if (InstantEffectTriggerPolicy == EEffectTriggerPolicy::EndOvelap)
	{
		ApplyEffectToTarget(OtherActor, InstantGameplayEffectClass);
	}

	if (DurationEffectTriggerPolicy == EEffectTriggerPolicy::EndOvelap)
	{
		ApplyEffectToTarget(OtherActor, DurationGameplayEffectClass);
	}

	if (LastingEffectTriggerPolicy == EEffectTriggerPolicy::EndOvelap)
	{
		ApplyEffectToTarget(OtherActor, LastingGameplayEffectClass);
	}
	if (LastingEffectRemovePolicy == EEffectRemovePolicy::EndOvelapRemove)
	{

		RemoveActiveGameplayEffectToTarget(OtherActor);

	}


}

void AAEffectActo::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC =	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target );
	if (!TargetASC) return;

	check(GameplayEffectClass);

	//��ȡ��ϷЧ�������ľ��
	FGameplayEffectContextHandle	EffectContextHandle = TargetASC->MakeEffectContext();
	//���ô��д�����Ч���Ķ���
	EffectContextHandle.AddSourceObject(this);
	
	//�����ϷЧ�����
	FGameplayEffectSpecHandle EffectSpecHandle  = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle);
	//����ϷЧ���淶��ӵ�����
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	//�ж��־�����ϷЧ���Ƿ��ɾ��
	if (LastingEffectRemovePolicy != EEffectRemovePolicy::NoRemove && ActiveGameplayEffectHandle.IsValid())
	{
		ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, TargetASC);
	}
	
}

void AAEffectActo::RemoveActiveGameplayEffectToTarget(AActor* Target)
{

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!TargetASC) return;

	//����ActiveGameplayEffectHandles ��Ҫɾ���Ļ��ϷЧ�����
	TArray<FActiveGameplayEffectHandle> RemoveEffectHandles;
	//��GAS���ɾ�������ϷЧ�����
	for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*>  EffectHandle : ActiveGameplayEffectHandles)
	{
		if (EffectHandle.Value == TargetASC)
		{
			//ɾ�������ϷЧ�����
			TargetASC->RemoveActiveGameplayEffect(EffectHandle.Key,1);
			
			RemoveEffectHandles.Add(EffectHandle.Key);
			
		}
	}

	//ɾ����������ActiveGameplayEffectHandles �еĻ��ϷЧ�����
	for (FActiveGameplayEffectHandle EffectHandle : RemoveEffectHandles)
	{
		ActiveGameplayEffectHandles.Remove(EffectHandle);
	}
	

}



