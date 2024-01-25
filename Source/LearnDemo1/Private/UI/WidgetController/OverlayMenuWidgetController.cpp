// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayMenuWidgetController.h"
#include "FAuraGamePlayTags.h"
#include "AbilitySystem\DA\AttribuateInfoDA.h"

void UOverlayMenuWidgetController::Broadcast() const
{
	

	for (TPair<FGameplayTag, FAttributeSignature>  TS : OwnerAuraAttributeSet->TagsToAttributeSignature)
	{
		FAttribuateInfo Info;
		Info = AttribuateInfoDataAsset->FindFAttribuateInfoForTag(TS.Key);
		Info.AttribuateValue = TS.Value.Execute().GetNumericValue(OwnerAuraAttributeSet);
		OnAttribuateInfoDelegate.Broadcast(Info);
	}


	
}

void UOverlayMenuWidgetController::BindDelegateSignatureI_MULTICAST()
{
	//属性更改时调用
	for (TPair<FGameplayTag, FAttributeSignature> TS : OwnerAuraAttributeSet->TagsToAttributeSignature)
		OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(TS.Value.Execute()).AddLambda(
			[this,TS] (const FOnAttributeChangeData& Data)
			{
			
				FAttribuateInfo Info;
			
				Info =	AttribuateInfoDataAsset->FindFAttribuateInfoForTag(TS.Key);
				Info.AttribuateValue = Data.NewValue;

				OnAttribuateInfoDelegate.Broadcast(Info);
			}
		);
}
