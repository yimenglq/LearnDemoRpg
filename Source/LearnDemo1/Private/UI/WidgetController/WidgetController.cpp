// Fill out your copyright notice in the Description page of Project Settings.


#include"UI/WidgetController/WidgetController.h"

void UWidgetController::SetWidgetControllerParams(const FWidgetControllerParms& Parms)
{
	OwnerPlayerController = Parms.PlayerController;
	OwnerPlayerState = Parms.PlayerState;
	OwnerAuraAbilitySystemComp = Parms.AuraAbilitySystemComp;
	OwnerAuraAttributeSet = Parms.AuraAttributeSet;

}
