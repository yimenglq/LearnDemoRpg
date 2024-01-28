// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystem/GameAbility/AuraGameAbility.h"



void UAuraGameAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	//��ͼ�еĴ�ӡ�ַ����ڵ�
	UKismetSystemLibrary::PrintString(GetWorld(), FString(TEXT("C++ ActivateAbility")), true, true, FLinearColor::Blue, 10.f);

}
