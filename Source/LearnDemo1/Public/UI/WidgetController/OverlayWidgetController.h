// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetController.h"
#include"GameplayAbilities\Public\GameplayEffectTypes.h"

#include "OverlayWidgetController.generated.h"



struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	//物品游戏标签
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	//消息文字
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	//显示在屏幕上的 UMG 控件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraWidget> MessageWidget;

	//物品图片
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;

};



//属性集合变更时的委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlayAttributeChangedSignature, float, NewValue);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
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

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Message")//消息数据表
	TObjectPtr<UDataTable> MessageDataTable;


	UPROPERTY(BlueprintAssignable, Category = "GAS|Message")//游戏效果附加时 触发的消息委托
	FMessageWidgetRowSignature OnMessageWidgetRowSignature;

	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")//体力值的委托
		FOnOverlayAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//最大体力值的委托
		FOnOverlayAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//法力值的委托
		FOnOverlayAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//最大法力值的委托
		FOnOverlayAttributeChangedSignature OnMaxManaChanged;

	

	//返回消息数据表中的一段 根据名称
	template<typename T>
	T* GetMessgaeRow(const FName& Row);
	//返回消息数据表中的一段 根据行号
	template<typename T>
	T* GetMessgaeRow(const uint32& iRow);
};

template<typename T>
inline T* UOverlayWidgetController::GetMessgaeRow(const FName& Row)
{
	ensureMsgf(MessageDataTable, TEXT("MessageDataTable Is Not Null"));
	T* InsRow = MessageDataTable->FindRow<T>(Row, TEXT(""));

	return InsRow;
}

template<typename T>
inline T* UOverlayWidgetController::GetMessgaeRow(const uint32& iRow)
{   
	ensureMsgf(MessageDataTable, TEXT("MessageDataTable Is Not Null"));
	T* InsRow = nullptr;
	TArray<T*> InsRows;
	MessageDataTable->GetAllRows(L"", InsRows);	
	if(	InsRows.Num() > iRow ) 
		InsRow = InsRows[iRow];
	return InsRow;
}
