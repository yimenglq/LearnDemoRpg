// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayEffect.h>
#include "OccupationInfoDataAsset.generated.h"


//��ɫְҵ����
UENUM(BlueprintType)
enum class EOccupationType : uint8
{
	//����
	Ranger,
	//սʿ
	Warrior,
	//��ʦ
	Mage
};


/**
 * ��ɫְҵ��Ϣ
 */
UCLASS(BlueprintType)
class LEARNDEMO1_API UOccupationInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	// ְҵ���Ͷ�Ӧ����Ҫ������ϷЧ��
	UPROPERTY(EditAnywhere)
	TMap<EOccupationType, TSubclassOf<UGameplayEffect>>	OccupationTypeAndPrimaryEffect;
	
	//���õĴ�Ҫ������ϷЧ��
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> SecondaryEffect;

	//���õ���Ҫ������ϷЧ��
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> VitalEffect;
	
	//��Ҫ������Ϸ��ǩ��������Ϸ����
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> ComAbility;


	UFUNCTION(BlueprintCallable,BlueprintPure)
	 TSubclassOf<UGameplayEffect>& GetDefaultOccupationToEffect(EOccupationType OccupationType);

};
