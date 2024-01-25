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
	//����ί�зַ��ĺ���
	UFUNCTION(BlueprintCallable)
	virtual void Broadcast()const override;

protected:

	//�󶨶ಥ����
	virtual	void BindDelegateSignatureI_MULTICAST() override;

	//������Ϣ��ί��
	UPROPERTY(BlueprintAssignable,Category = "OverlayMenuWidgetController|Info")
	FOnAttribuateInfo OnAttribuateInfoDelegate;

	
	//������Ϣ �����ʲ�
	UPROPERTY(EditDefaultsOnly,Category = "OverlayMenuWidgetController|Info")
	TObjectPtr<UAttribuateInfoDA> AttribuateInfoDataAsset;
};
