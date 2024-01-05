// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");

	AbilitySystemComponent->SetIsReplicated(true);//�������縴��
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);//���ø���ģʽ   ������С����ϷЧ����Ϣ���Ƶ�ģ���������������Ϣ���Ƶ������ߺ����δ���

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");


	NetUpdateFrequency = 100.f;//  ���Ǹ��ƴ�ִ�������Ƶ�ʣ�ÿ�룩
}


UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraPlayerState::GetAttributeSet()
{
	return AttributeSet;
}
