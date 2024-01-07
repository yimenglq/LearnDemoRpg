// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Player/AuraPlayerState.h>
#include "WidgetController.generated.h"


class UAuraAbilitySystemComponent;
class UAuraAttributeSet;


USTRUCT()
struct FWidgetControllerParms
{
	GENERATED_BODY()

	FWidgetControllerParms() {}
	FWidgetControllerParms(APlayerController* PCL, AAuraPlayerState* PS, UAuraAbilitySystemComponent* ASC, UAuraAttributeSet* AS)
		: PlayerController(PCL), PlayerState(PS), AuraAbilitySystemComp(ASC), AuraAttributeSet(AS)
	{}

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY()
	TObjectPtr<AAuraPlayerState> PlayerState;
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComp;
	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AuraAttributeSet;
};

/**
 * 
 */
UCLASS(BlueprintType)
class LEARNDEMO1_API UWidgetController : public UObject
{
	GENERATED_BODY()
	

public:

	void SetWidgetControllerParams(const FWidgetControllerParms& Parms);

	//进行委托分发的函数
	virtual void Broadcast()const {};

protected:
	UPROPERTY(BlueprintReadOnly,Category= "WidgetController")
	TObjectPtr<APlayerController> OwnerPlayerController;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AAuraPlayerState> OwnerPlayerState;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAuraAbilitySystemComponent> OwnerAuraAbilitySystemComp;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAuraAttributeSet> OwnerAuraAttributeSet;
};
