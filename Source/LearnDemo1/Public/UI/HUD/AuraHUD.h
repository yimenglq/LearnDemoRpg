// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UOverlayWidgetController;
class UAuraWidget;
struct FWidgetControllerParms;

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

	UFUNCTION(BlueprintCallable)//��ȡ�м�� WidgetController
	UWidgetController* GetWidgetController();

		

	//UWidgetController* GetWidgetController();
protected:

	TObjectPtr<UWidgetController> WidgetController; //�м�� WidgetController
	
	
	TObjectPtr<UAuraWidget> Widget;//������UI

private:

	UPROPERTY(EditAnywhere,Category = "AuraHUD")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere, Category = "AuraHUD")
	TSubclassOf<UAuraWidget> WidgetClass;
};
