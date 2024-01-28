// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttribuateInfoDA.generated.h"


USTRUCT(BlueprintType)
struct FAttribuateInfo//����������Ϣ
{
	GENERATED_BODY()
	//��Ϸ��ǩ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag GameTag;
	
	//������
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttribuateName;

	//��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttribuateDescription;


	//���Ե���ֵ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttribuateValue;
		
};




/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAttribuateInfoDA : public UDataAsset
{
	GENERATED_BODY()
	

public:
	//��ѯ��Ӧ��ǩ��������Ϣ
	FAttribuateInfo FindFAttribuateInfoForTag(const FGameplayTag& Tag, bool bLogNotFound = true) const;

	//������Ϣ��
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray< FAttribuateInfo> AttribuateInfoes;
	//������Ϣ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray< FAttribuateInfo> TestInfoes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float d;

};
