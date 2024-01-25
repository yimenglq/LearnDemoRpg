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

	//��Ʒ��Ϸ��ǩ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	//��Ϣ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	//��ʾ����Ļ�ϵ� UMG �ؼ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraWidget> MessageWidget;

	//��ƷͼƬ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;

};



//���Լ��ϱ��ʱ��ί��
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
	
	//�ص����� ���Ը��� 
	void OnHealthAttribute(const FOnAttributeChangeData& Data);
	void OnMaxHealthAttribute(const FOnAttributeChangeData& Data);
	void OnManaAttribute(const FOnAttributeChangeData& Data);
	void OnMaxManaAttribute(const FOnAttributeChangeData& Data);
	//End
public:

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Message")//��Ϣ���ݱ�
	TObjectPtr<UDataTable> MessageDataTable;


	UPROPERTY(BlueprintAssignable, Category = "GAS|Message")//��ϷЧ������ʱ ��������Ϣί��
	FMessageWidgetRowSignature OnMessageWidgetRowSignature;

	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")//����ֵ��ί��
		FOnOverlayAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//�������ֵ��ί��
		FOnOverlayAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//����ֵ��ί��
		FOnOverlayAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")//�����ֵ��ί��
		FOnOverlayAttributeChangedSignature OnMaxManaChanged;

	

	//������Ϣ���ݱ��е�һ�� ��������
	template<typename T>
	T* GetMessgaeRow(const FName& Row);
	//������Ϣ���ݱ��е�һ�� �����к�
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
