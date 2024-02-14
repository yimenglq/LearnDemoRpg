// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameAbility/AuraGameAbility_Projectile.h"
#include <Character/AuraCharacterBase.h>
#include <AbilitySystem/AuraAbillitySystemLibrary.h>
#include <FAuraGamePlayTags.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <Iterface/CombatInterface.h>


void UAuraGameAbility_Projectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);



	if (AAuraCharacterBase * OwnerCharacter = Cast<AAuraCharacterBase>(ActorInfo->AvatarActor) )
	{	
		SpawnProjectile = GetWorld()->SpawnActorDeferred<AAEffectActo_Projectile>(SpawnProjectileClass, SpawnTransform, ActorInfo->AvatarActor.Get(), Cast<APawn>(ActorInfo->AvatarActor.Get()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()))
		{

			ICombatInterface*	IIF = Cast<ICombatInterface>(OwnerCharacter);

			FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, IIF ? IIF->GetLevel() : GetAbilityLevel() , ASC->MakeEffectContext());
			
			const float fValue = Damage.GetValueAtLevel(IIF ? IIF->GetLevel() : GetAbilityLevel());

			//按调用方大小设置的映射 SetByCallerTagMagnitudes
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, FAuraGamePlayTags::Get().Damage, fValue);
			SpawnProjectile->EffectSpecHandle = EffectSpecHandle;


		}

	}

}

void UAuraGameAbility_Projectile::FinishSpawning(const FVector& TargetLocation)
{
	if (SpawnProjectile)
	{
		AAuraCharacterBase* OwnerCharacter = Cast<AAuraCharacterBase>(GetCurrentActorInfo()->AvatarActor) ;

		SpawnTransform.SetLocation(
			
			OwnerCharacter->GetWeapons()->GetSocketLocation(SocketSpawn)
		);

		/*SpawnTransform.SetRotation(
			FQuat(
				(UAuraAbillitySystemLibrary::GetThisHitPlayController(OwnerCharacter).ImpactPoint - SpawnTransform.GetLocation()).Rotation()
			)
		);*/
		SpawnTransform.SetRotation(
			FQuat(
				(TargetLocation - SpawnTransform.GetLocation()).Rotation().Quaternion()
			)
		);

		SpawnProjectile->FinishSpawning(SpawnTransform);
	}
	
}
