// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataMouseAbilityTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataMouseSignature,const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UTargetDataMouseAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category ="Ability|Task", meta = (DisplayName = "TargetDataUnderMouse",HidePin = "OwningAblilty", DefaultToSelf = "OwningAblilty")) // meta  ǰ׺ UM::
	static UTargetDataMouseAbilityTask* CreateTargetDataMouse(UGameplayAbility* OwningAblilty);
	
	UPROPERTY(BlueprintAssignable, Category = "Ability|Task")
	FTargetDataMouseSignature ValidData;

private:

	virtual void Activate() override;

	void SendMouseCursorData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);

};
