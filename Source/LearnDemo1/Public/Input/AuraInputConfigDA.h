// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfigDA.generated.h"



class UInputAction;

USTRUCT(BlueprintType)
struct FInputToTag
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag;


};

/**
 * 
 */
UCLASS(BlueprintType)
class LEARNDEMO1_API UAuraInputConfigDA : public UDataAsset
{
	GENERATED_BODY()
	


public:

	// ‰»Î≈‰÷√
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FInputToTag> InputConfiges;

};
