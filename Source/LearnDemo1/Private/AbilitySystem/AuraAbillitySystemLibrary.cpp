// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbillitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/HUD/AuraHUD.h>
#include <Player/AuraPlayerController.h>

UWidgetController* UAuraAbillitySystemLibrary::GetHUDWidgetController(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		//获取本地玩家  0号  始终是本地玩家控制器
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
		//获取本地玩家  0号  始终是本地玩家控制器
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
		//获取本地玩家  0号  始终是本地玩家控制器
		AAuraPlayerController* PC =	Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
		return PC->GetThisHit();

	}

	return FHitResult();
}
