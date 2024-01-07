// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetController.h"
#include "OverlayWidgetController.generated.h"

//属性集合变更时的委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);


/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UOverlayWidgetController : public UWidgetController
{
	GENERATED_BODY()
	

public:
	//Override UWidgetController
	virtual void Broadcast()const override;

	//End


public:
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")//体力值的委托
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//最大体力值的委托
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//法力值的委托
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//最大法力值的委托
	FOnAttributeChangedSignature OnMaxManaChanged;

	

};
