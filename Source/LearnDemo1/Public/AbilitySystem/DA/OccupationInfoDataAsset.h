// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayEffect.h>
#include "OccupationInfoDataAsset.generated.h"


//角色职业类型
UENUM(BlueprintType)
enum class EOccupationType : uint8
{
	//游侠
	Ranger,
	//战士
	Warrior,
	//法师
	Mage
};


/**
 * 角色职业信息
 */
UCLASS(BlueprintType)
class LEARNDEMO1_API UOccupationInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	// 职业类型对应的主要属性游戏效果
	UPROPERTY(EditAnywhere)
	TMap<EOccupationType, TSubclassOf<UGameplayEffect>>	OccupationTypeAndPrimaryEffect;
	
	//共用的次要属性游戏效果
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> SecondaryEffect;

	//共用的重要属性游戏效果
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> VitalEffect;
	
	//需要根据游戏标签启动的游戏能力
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> ComAbility;


	UFUNCTION(BlueprintCallable,BlueprintPure)
	 TSubclassOf<UGameplayEffect>& GetDefaultOccupationToEffect(EOccupationType OccupationType);

};
