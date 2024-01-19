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
	
	//设置中间件
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UWidgetController* InWidgetController);
	
	//蓝图可实现的函数
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void WidgetControllerSet();

protected:
	UPROPERTY(BlueprintReadOnly)//中间件UI拿取数据的地方  
	TObjectPtr<UWidgetController> WidgetController;

	

};
