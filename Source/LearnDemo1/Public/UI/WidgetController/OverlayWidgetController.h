// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetController.h"
#include"GameplayAbilities\Public\GameplayEffectTypes.h"

#include "OverlayWidgetController.generated.h"

//属性集合变更时的委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlayAttributeChangedSignature, float, NewValue);



struct FOnAttributeChangeData;
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

protected:
	//Override UWidgetController
	virtual	void BindDelegateSignatureI_MULTICAST() override;
	//End
	
	//回调函数 属性更改 
	void OnHealthAttribute(const FOnAttributeChangeData& Data);
	void OnMaxHealthAttribute(const FOnAttributeChangeData& Data);
	void OnManaAttribute(const FOnAttributeChangeData& Data);
	void OnMaxManaAttribute(const FOnAttributeChangeData& Data);
	//End
public:
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")//体力值的委托
		FOnOverlayAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//最大体力值的委托
		FOnOverlayAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//法力值的委托
		FOnOverlayAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//最大法力值的委托
		FOnOverlayAttributeChangedSignature OnMaxManaChanged;

	

};
