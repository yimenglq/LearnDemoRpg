// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	//获取资产管理器唯一实例
	static UAuraAssetManager& Get();

	//初始化加载
	virtual void StartInitialLoading() override;
};
