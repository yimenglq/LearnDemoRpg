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
	//��ȡ�ʲ�������Ψһʵ��
	static UAuraAssetManager& Get();

	//��ʼ������
	virtual void StartInitialLoading() override;
};
