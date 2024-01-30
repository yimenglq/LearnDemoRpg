// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameAbility/AuraGameAbility_Projectile.h"
#include <Character/AuraCharacterBase.h>
#include <AbilitySystem/AuraAbillitySystemLibrary.h>

void UAuraGameAbility_Projectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);



	if (AAuraCharacterBase * OwnerCharacter = Cast<AAuraCharacterBase>(ActorInfo->AvatarActor) )
	{	
		SpawnActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnActorClass, SpawnTransform, ActorInfo->AvatarActor.Get(), Cast<APawn>(ActorInfo->AvatarActor.Get()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	}

}

void UAuraGameAbility_Projectile::FinishSpawning(const FVector& TargetLocation)
{
	if (SpawnActor)
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

		SpawnActor->FinishSpawning(SpawnTransform);
	}
	
}
