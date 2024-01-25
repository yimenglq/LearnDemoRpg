// Fill out your copyright notice in the Description page of Project Settings.

#include"UI/Widget/AuraWidget.h"
#include <Player/AuraPlayerState.h>
#include"AbilitySystem/AuraAttributeSet.h"
#include"AbilitySystem/AuraAbilitySystemComponent.h"
#include <UI/WidgetController/OverlayWidgetController.h>
#include"UI/WidgetController/OverlayMenuWidgetController.h"
#include "UI/HUD/AuraHUD.h"



void AAuraHUD::InitAuraHUD(const FWidgetControllerParms& InParms)
{
	checkf(OverlayWidgetControllerClass, TEXT("��֤WidgetControllerClass����ͼ��ֵ��"));
	checkf(WidgetClass, TEXT("��֤WidgetClass����ͼ��ֵ��"));
	
	Widget = Cast<UAuraWidget>( CreateWidget(GetWorld(), WidgetClass));
	check(Widget);
	UWidgetController* WCl = GetWidgetController();
	
		
	Widget->SetWidgetController(WCl);

	WCl->Broadcast();

	Widget->AddToViewport();
}

UWidgetController* AAuraHUD::GetWidgetController()
{
	checkf(OverlayWidgetControllerClass, TEXT("��֤WidgetControllerClass����ͼ��ֵ��"));
	
	if (WidgetController == NULL)
	{
		WidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		
		APlayerController* PC = GetOwningPlayerController();
		AAuraPlayerState* PS =	PC->GetPlayerState<AAuraPlayerState>();
		UAuraAbilitySystemComponent* ASC =	Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		UAuraAttributeSet* AS =	Cast<UAuraAttributeSet>(PS->GetAttributeSet());

		FWidgetControllerParms Parms(PC,PS,ASC,AS);

		WidgetController->SetWidgetControllerParams(Parms);

	}

	return WidgetController;
}

UWidgetController* AAuraHUD::GetOverlayMenuWidgetController()
{
	if (OverlayMenuWidgetController == NULL)
	{
		OverlayMenuWidgetController = GetTypeWidgetController(OverlayMenuWidgetControllerClass);
		OverlayMenuWidgetController->Broadcast();
	}
	

	return OverlayMenuWidgetController;
}
