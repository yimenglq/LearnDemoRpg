// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UDamageWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamage(float Damage);

};
