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

	//获取游戏效果上下文句柄
	FGameplayEffectContextHandle	EffectContextHandle = TargetASC->MakeEffectContext();
	//设置从中创建此效果的对象。
	EffectContextHandle.AddSourceObject(this);
	
	//获得游戏效果句柄
	FGameplayEffectSpecHandle EffectSpecHandle  = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle);
	//将游戏效果规范添加到自身
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	//判读持久性游戏效果是否可删除
	if (LastingEffectRemovePolicy != EEffectRemovePolicy::NoRemove && ActiveGameplayEffectHandle.IsValid())
	{
		ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, TargetASC);
	}
	
}

void AAEffectActo::RemoveActiveGameplayEffectToTarget(AActor* Target)
{

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!TargetASC) return;

	//保存ActiveGameplayEffectHandles 需要删除的活动游戏效果句柄
	TArray<FActiveGameplayEffectHandle> RemoveEffectHandles;
	//在GAS组件删除掉活动游戏效果句柄
	for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*>  EffectHandle : ActiveGameplayEffectHandles)
	{
		if (EffectHandle.Value == TargetASC)
		{
			//删除活动的游戏效果句柄
			TargetASC->RemoveActiveGameplayEffect(EffectHandle.Key,1);
			
			RemoveEffectHandles.Add(EffectHandle.Key);
			
		}
	}

	//删除掉保存在ActiveGameplayEffectHandles 中的活动游戏效果句柄
	for (FActiveGameplayEffectHandle EffectHandle : RemoveEffectHandles)
	{
		ActiveGameplayEffectHandles.Remove(EffectHandle);
	}
	

}



