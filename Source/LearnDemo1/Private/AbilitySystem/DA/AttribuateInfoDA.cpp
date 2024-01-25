// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DA/AttribuateInfoDA.h"

FAttribuateInfo UAttribuateInfoDA::FindFAttribuateInfoForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FAttribuateInfo& Info : AttribuateInfoes)
	{
		if (Info.GameTag.MatchesTagExact(Tag))
		{

			return Info;
		}


	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("No Find AttribuateInfo , Tag Is [%s] , AttribuateInfo [%s] "),*Tag.ToString(),*GetNameSafe(this));

	}

	return FAttribuateInfo();
}
