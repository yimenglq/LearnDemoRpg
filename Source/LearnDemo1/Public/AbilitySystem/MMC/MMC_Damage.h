// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Damage.generated.h"

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UMMC_Damage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;
};
