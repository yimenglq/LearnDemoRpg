// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DA/OccupationInfoDataAsset.h"

TSubclassOf<UGameplayEffect>& UOccupationInfoDataAsset::GetDefaultOccupationToEffect(EOccupationType OccupationType)
{
    // TODO: �ڴ˴����� return ���
    

    return *OccupationTypeAndPrimaryEffect.Find(OccupationType);
}
