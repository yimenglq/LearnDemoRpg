// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbillitySystemLibrary.generated.h"

class UWidgetController;

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAuraAbillitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable,Category = "AuraAbillitySystemLibrary")
	static UWidgetController* GetHUDWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AuraAbillitySystemLibrary")
	static UWidgetController* GetOverlayMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AuraAbillitySystemLibrary")
	static FHitResult GetThisHitPlayController(const UObject* WorldContextObject);
};
