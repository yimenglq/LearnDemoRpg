// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilities\Public\ActiveGameplayEffectHandle.h"
#include "AEffectActo.generated.h"


/*
*	触发游戏效果的枚举策略
*/


UENUM()
enum class EEffectTriggerPolicy: uint8  //触发效果策略 //一字节
{
	//开始重叠时触发
	BeginOvelap,
	//结束重叠时触发
	EndOvelap,
	//不触发
	NoTrigger
};


UENUM()
enum class EEffectRemovePolicy : uint8 //删除效果策略 //一字节
{
	//开始重叠时删除
	BeginOvelapRemove,
	//结束重叠时删除
	EndOvelapRemove,
	//不删除
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
	
	//碰撞开始重叠事件
	UFUNCTION(BlueprintCallable)
	virtual void BeginOvelap(AActor* OtherActor);

	//碰撞结束重叠事件
	UFUNCTION(BlueprintCallable)
	virtual void EndOverlap(AActor* OtherActor);

    // 添加游戏效果到目标上
	UFUNCTION(BlueprintCallable, Category = "AEffectActo")
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	// 删除游戏效果在目标上
	UFUNCTION(BlueprintCallable, Category = "AEffectActo")
	void RemoveActiveGameplayEffectToTarget(AActor* Target);

protected:

	//保存活动游戏效果 与 对应的GAS组件
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent* > ActiveGameplayEffectHandles;


	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "AEffectActo|Instant")// 即时（立即）的游戏效果
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Instant")
	EEffectTriggerPolicy InstantEffectTriggerPolicy = EEffectTriggerPolicy::NoTrigger;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Duration")// 有持续时间的游戏效果
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Duration")
	EEffectTriggerPolicy DurationEffectTriggerPolicy = EEffectTriggerPolicy::NoTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Lasting")// 持久性的游戏效果
	TSubclassOf<UGameplayEffect> LastingGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Lasting")
	EEffectTriggerPolicy LastingEffectTriggerPolicy = EEffectTriggerPolicy::NoTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AEffectActo|Lasting")
	EEffectRemovePolicy  LastingEffectRemovePolicy = EEffectRemovePolicy::EndOvelapRemove;

};
