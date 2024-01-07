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
