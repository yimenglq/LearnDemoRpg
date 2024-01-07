// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraWidget.h"

void UAuraWidget::SetWidgetController(UWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;

	WidgetControllerSet();
}
