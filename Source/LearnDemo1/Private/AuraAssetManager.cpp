// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include <FAuraGamePlayTags.h>

UAuraAssetManager& UAuraAssetManager::Get()
{
	UAuraAssetManager* AuraAM = 	Cast<UAuraAssetManager>(GEngine->AssetManager);

	return *AuraAM;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//调用初始化需要加载的标签
	FAuraGamePlayTags::InitalizNativeGameplayTags();

}
