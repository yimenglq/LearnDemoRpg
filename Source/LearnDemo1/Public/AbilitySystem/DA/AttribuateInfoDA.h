// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttribuateInfoDA.generated.h"


USTRUCT(BlueprintType)
struct FAttribuateInfo//属性数据信息
{
	GENERATED_BODY()
	//游戏标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag GameTag;
	
	//属性名
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttribuateName;

	//属性描述
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttribuateDescription;


	//属性的数值
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
	//查询对应标签的属性消息
	FAttribuateInfo FindFAttribuateInfoForTag(const FGameplayTag& Tag, bool bLogNotFound = true) const;

	//属性信息集
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray< FAttribuateInfo> AttribuateInfoes;
	//属性信息集
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray< FAttribuateInfo> TestInfoes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float d;

};
