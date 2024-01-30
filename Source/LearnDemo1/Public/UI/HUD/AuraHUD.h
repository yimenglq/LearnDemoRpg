// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UOverlayWidgetController;
class UAuraWidget;
struct FWidgetControllerParms;
class UOverlayMenuWidgetController;

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	//override AActor
	

	//End

public:
	
	void InitAuraHUD(const FWidgetControllerParms& InParms);

	UFUNCTION(BlueprintCallable)//获取中间件 WidgetController
	UWidgetController* GetWidgetController();
	
	UFUNCTION(BlueprintCallable)//获取中间件 OverlayMenuWidgetController 获得属性菜单的控制器
	UWidgetController* GetOverlayMenuWidgetController();
	


	template<typename WclType>
	WclType* GetTypeWidgetController(TSubclassOf<WclType> WidgetControllerClass);
		

	//UWidgetController* GetWidgetController();
protected:

	TObjectPtr<UWidgetController> WidgetController; //中间件 WidgetController 主界面
	
	TObjectPtr<UAuraWidget> Widget;//主界面UI


	TObjectPtr<UWidgetController> OverlayMenuWidgetController;//属性菜单WidgetController

private:

	UPROPERTY(EditAnywhere,Category = "AuraHUD")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere, Category = "AuraHUD")
	TSubclassOf<UOverlayMenuWidgetController> OverlayMenuWidgetControllerClass;//属性菜单类

	UPROPERTY(EditAnywhere, Category = "AuraHUD")
	TSubclassOf<UAuraWidget> WidgetClass;
};


template<typename WclType>
inline	WclType* AAuraHUD::GetTypeWidgetController(TSubclassOf<WclType> WidgetControllerClass)
{
	check(WidgetControllerClass);
	WclType* WC = NewObject<WclType>(this, WidgetControllerClass);

	APlayerController* PC = GetOwningPlayerController();
	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	PS = PS ? PS : PC->GetPawn()->GetPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PS->GetAttributeSet());

	FWidgetControllerParms Parms(PC, PS, ASC, AS);

	WC->SetWidgetControllerParams(Parms);

	return WC;
}

