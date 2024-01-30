// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbillitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/HUD/AuraHUD.h>
#include <Player/AuraPlayerController.h>

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

FHitResult UAuraAbillitySystemLibrary::GetThisHitPlayController(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		//��ȡ�������  0��  ʼ���Ǳ�����ҿ�����
		AAuraPlayerController* PC =	Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
		return PC->GetThisHit();

	}

	return FHitResult();
}
