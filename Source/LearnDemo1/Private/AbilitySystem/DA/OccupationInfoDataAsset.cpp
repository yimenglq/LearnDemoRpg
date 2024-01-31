// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DA/OccupationInfoDataAsset.h"

TSubclassOf<UGameplayEffect>& UOccupationInfoDataAsset::GetDefaultOccupationToEffect(EOccupationType OccupationType)
{
    // TODO: 在此处插入 return 语句
    

    return *OccupationTypeAndPrimaryEffect.Find(OccupationType);
}
