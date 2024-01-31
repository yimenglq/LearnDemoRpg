// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameAbility/AuraGameAbility.h"
#include <Actor/AEffectActo_Projectile.h>
#include "AuraGameAbility_Projectile.generated.h"


/**
 * 
 */
UCLASS()
class LEARNDEMO1_API UAuraGameAbility_Projectile : public UAuraGameAbility
{
	GENERATED_BODY()
	
	

public:

	//Override UAuraGameAbility

/**激活能力  不要直接调用*/
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	//End

	UFUNCTION(BlueprintCallable, Category = "AuraGameAbility_Projectile")
	void FinishSpawning(const FVector& TargetLocation);

	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "AuraCharacterBase|Attribute")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditAnywhere,Category = "Spawn")
	TSubclassOf<AAEffectActo_Projectile> SpawnProjectileClass;

	AAEffectActo_Projectile* SpawnProjectile;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FName SocketSpawn;

	FTransform SpawnTransform;
};
