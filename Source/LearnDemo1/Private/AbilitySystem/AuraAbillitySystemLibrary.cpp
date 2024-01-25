// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbillitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/HUD/AuraHUD.h>

UWidgetController* UAuraAbillitySystemLibrary::GetHUDWidgetController(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		//��ȡ�������  0��  ʼ���Ǳ�����ҿ�����
		APlayerController* PC =	UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		AAuraHUD* AuraHUD	= Cast<AAuraHUD>(	PC->GetHUD() );
		if (AuraHUD)
		{
		    return	AuraHUD->GetWidgetController();
		}


	}
	return nullptr;
}

UWidgetController* UAuraAbillitySystemLibrary::GetOverlayMenuWidgetController(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		//��ȡ�������  0��  ʼ���Ǳ�����ҿ�����
		APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
		if (AuraHUD)
		{

			return	AuraHUD->GetOverlayMenuWidgetController();


		}


	}
	return nullptr;
}
