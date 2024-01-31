// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbillitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/HUD/AuraHUD.h>
#include <Player/AuraPlayerController.h>
#include <AbilitySystemBlueprintLibrary.h>
#include"AbilitySystem\DA\OccupationInfoDataAsset.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"
#include <Game/AureGameModeBase.h>
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <Iterface/CombatInterface.h>

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

void UAuraAbillitySystemLibrary::InitOccupationAttibuate(AActor* TargetObject, EOccupationType OccupationType, TSubclassOf<UGameplayEffect>& SecondaryEffect, TSubclassOf<UGameplayEffect>& VitalEffect)
{
	if (TargetObject == nullptr) return;

	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetObject) )
	{
		if (AAureGameModeBase* GM = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(TargetObject)) )
		{

			
			 TSubclassOf<UGameplayEffect>& Effect = GM->OccupationInfo->GetDefaultOccupationToEffect(OccupationType);
			 

			ApplyEffectToSelf(TargetObject, ASC,Effect);
			
			ApplyEffectToSelf(TargetObject, ASC, SecondaryEffect);
			
			ApplyEffectToSelf(TargetObject, ASC, VitalEffect);

			
		}

	}
}

void UAuraAbillitySystemLibrary::InitOccupationAttibuate(AActor* TargetObject, EOccupationType OccupationType)
{
	if (TargetObject == nullptr) return;

	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetObject))
	{
		if (AAureGameModeBase* GM = Cast<AAureGameModeBase>(UGameplayStatics::GetGameMode(TargetObject)))
		{


			TSubclassOf<UGameplayEffect>& Effect = GM->OccupationInfo->GetDefaultOccupationToEffect(OccupationType);

			ApplyEffectToSelf(TargetObject, ASC, Effect);

			ApplyEffectToSelf(TargetObject, ASC, GM->OccupationInfo->SecondaryEffect);

			ApplyEffectToSelf(TargetObject, ASC, GM->OccupationInfo->VitalEffect);


		}

	}
}

void UAuraAbillitySystemLibrary::ApplyEffectToSelf(AActor* Target, UAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect>& Effect)
{
	check(Effect);

	ICombatInterface* CIF = Cast<ICombatInterface>(Target);
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(Target);
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(Effect, CIF ? CIF->GetLevel() : 1.f, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
