// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");

	AbilitySystemComponent->SetIsReplicated(true);//开启网络复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);//设置复制模式   仅将最小的游戏效果信息复制到模拟代理，但将完整信息复制到所有者和自治代理

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");


	NetUpdateFrequency = 100.f;//  考虑复制此执行组件的频率（每秒）
}


UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraPlayerState::GetAttributeSet()
{
	return AttributeSet;
}
