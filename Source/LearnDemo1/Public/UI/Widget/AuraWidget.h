// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraWidget.generated.h"

class UWidgetController;

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAuraWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:
	
	//�����м��
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UWidgetController* InWidgetController);
	
	//��ͼ��ʵ�ֵĺ���
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void WidgetControllerSet();

protected:
	UPROPERTY(BlueprintReadOnly)//�м��UI��ȡ���ݵĵط�  
	TObjectPtr<UWidgetController> WidgetController;

	

};
