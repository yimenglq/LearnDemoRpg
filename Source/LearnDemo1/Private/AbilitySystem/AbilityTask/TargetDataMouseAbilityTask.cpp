// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetDataMouseAbilityTask.h"
#include"GameplayAbilities\Public\AbilitySystemComponent.h"

UTargetDataMouseAbilityTask* UTargetDataMouseAbilityTask::CreateTargetDataMouse(UGameplayAbility* OwningAblilty)
{
	UTargetDataMouseAbilityTask* TaskObj = NewAbilityTask<UTargetDataMouseAbilityTask>(OwningAblilty);

	
	return TaskObj;
}

void UTargetDataMouseAbilityTask::Activate()
{
	const bool IsLocal =  Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (IsLocal)
	{
		SendMouseCursorData();

	}
	else
	{
		FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		FPredictionKey	PredictionKey	= GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, PredictionKey).AddUObject(this, &UTargetDataMouseAbilityTask::OnTargetDataReplicatedCallback);

		const bool bCallDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, PredictionKey);
		if (!bCallDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}




}

void UTargetDataMouseAbilityTask::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = HitResult;
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
		GetActivationPredictionKey(), DataHandle,FGameplayTag(), 
		AbilitySystemComponent->ScopedPredictionKey
	);

	//判断游戏能力是否还处于活跃状态
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
		
}

void UTargetDataMouseAbilityTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	//判断游戏能力是否还处于活跃状态
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
