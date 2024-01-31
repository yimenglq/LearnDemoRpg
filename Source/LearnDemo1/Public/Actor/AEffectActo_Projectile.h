// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AEffectActo.h"
#include <GameplayEffect.h>
#include "AEffectActo_Projectile.generated.h"



class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class LEARNDEMO1_API AAEffectActo_Projectile : public AAEffectActo
{
	GENERATED_BODY()


public:

	AAEffectActo_Projectile();


	//游戏效果句柄
	FGameplayEffectSpecHandle EffectSpecHandle;



protected:
	//Override AAEffectActo

	virtual void BeginOvelap(AActor* OtherActor)override;

	//碰撞结束重叠事件

	virtual void EndOverlap(AActor* OtherActor)override;
	//End


	//override AActor
	virtual void PostInitializeComponents() override;
	virtual void Destroyed()override;
	//End

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	//爆炸时的效果
	UPROPERTY(EditAnywhere,Category= "00-Effect|NiagaraSystem")
	TObjectPtr<	UNiagaraSystem> ExplosionNiagaraSystem;

	//爆炸时的声音
	UPROPERTY(EditAnywhere, Category = "00-Effect|Sound")
	TObjectPtr<USoundBase> ExplosionSound;

private:
	bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UFUNCTION()
	void OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
