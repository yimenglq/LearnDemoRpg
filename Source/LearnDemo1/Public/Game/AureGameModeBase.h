// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"E:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Classes\Engine\TextureRenderTarget2D.h"
#include <ImageUtils.h>
#include "GameFramework/GameModeBase.h"
#include "AureGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class LEARNDEMO1_API AAureGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	


	//将渲染纹理2d对象存储到文件以二进制的形式
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SaveRenderTargetToFile", Keywords = "SaveRenderTargetToFile"), Category = "SaveToFile")
	static bool SaveRenderTargetToFile(UTextureRenderTarget2D* rt, const FString& fileDestination)
	{
		FTextureRenderTargetResource* rtResource = rt->GameThread_GetRenderTargetResource();
		FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);

		TArray<FColor> outBMP;
		outBMP.AddUninitialized(rt->GetSurfaceWidth() * rt->GetSurfaceHeight());
		rtResource->ReadPixels(outBMP, readPixelFlags);
		


		FIntPoint destSize(rt->GetSurfaceWidth(), rt->GetSurfaceHeight());
		TArray<uint8> CompressedBitmap;
		FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, CompressedBitmap);
		bool imageSavedOk = FFileHelper::SaveArrayToFile(CompressedBitmap, *fileDestination);

		return imageSavedOk;
	}


};
