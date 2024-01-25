// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetController.h"
#include "OverlayMenuWidgetController.generated.h"


struct FAttribuateInfo;
class UAttribuateInfoDA;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttribuateInfo,const FAttribuateInfo&, Info);


/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class LEARNDEMO1_API UOverlayMenuWidgetController : public UWidgetController
{
	GENERATED_BODY()
	

public:
	//进行委托分发的函数
	UFUNCTION(BlueprintCallable)
	virtual void Broadcast()const override;

protected:

	//绑定多播代理
	virtual	void BindDelegateSignatureI_MULTICAST() override;

	//属性信息的委托
	UPROPERTY(BlueprintAssignable,Category = "OverlayMenuWidgetController|Info")
	FOnAttribuateInfo OnAttribuateInfoDelegate;

	
	//属性信息 数据资产
	UPROPERTY(EditDefaultsOnly,Category = "OverlayMenuWidgetController|Info")
	TObjectPtr<UAttribuateInfoDA> AttribuateInfoDataAsset;
};
