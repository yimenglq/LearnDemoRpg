// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetController.h"
#include "OverlayWidgetController.generated.h"

//���Լ��ϱ��ʱ��ί��
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
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")//����ֵ��ί��
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//�������ֵ��ί��
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//����ֵ��ί��
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//�����ֵ��ί��
	FOnAttributeChangedSignature OnMaxManaChanged;

	

};
