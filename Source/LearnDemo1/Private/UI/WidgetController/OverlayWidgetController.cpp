// Fill out your copyright notice in the Description page of Project Settings.

#include"AbilitySystem/AuraAttributeSet.h"
#include"AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"



void UOverlayWidgetController::Broadcast() const
{
	OnHealthChanged.Broadcast(OwnerAuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(OwnerAuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(OwnerAuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(OwnerAuraAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindDelegateSignatureI_MULTICAST()
{
	//绑定 UAuraAttributeSet 属性集中 成员变量 FGameplayAttributeData Health; 更改时 触发的回调函数
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnHealthAttribute);
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxHealthAttribute);
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnManaAttribute);
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxManaAttribute);
}

void UOverlayWidgetController::OnHealthAttribute(const FOnAttributeChangeData& Data)
{
	//委托分发
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxHealthAttribute(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnManaAttribute(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxManaAttribute(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
