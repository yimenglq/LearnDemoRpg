// Fill out your copyright notice in the Description page of Project Settings.
#include<Kismet/GameplayStatics.h>
#include "Components/SphereComponent.h"
#include <NiagaraFunctionLibrary.h>
#include"GameFramework\ProjectileMovementComponent.h"
#include "Actor/AEffectActo_Projectile.h"
#include <AbilitySystemBlueprintLibrary.h>
#include"AbilitySystemComponent.h"





AAEffectActo_Projectile::AAEffectActo_Projectile()
{

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	ProjectileMovementComponent->InitialSpeed = 500.f;
}

void AAEffectActo_Projectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAEffectActo_Projectile::OnCompBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AAEffectActo_Projectile::OnCompEndOverlap);

}

void AAEffectActo_Projectile::Destroyed()
{
	//防止服务器摧毁时 客户端还没反应
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionNiagaraSystem, GetActorLocation());

	}

	Super::Destroyed();
}


void AAEffectActo_Projectile::BeginOvelap(AActor* OtherActor)
{

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionNiagaraSystem, GetActorLocation());
	
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		EffectSpecHandle.Data.Get()->SetLevel(EffectLevel);
		
		//添加碰撞的目标到游戏效果范例实例里面
		FGameplayEffectSpecHandle TagrESH = ASC->MakeOutgoingSpec(GameplayEffectClass, 0.f, ASC->MakeEffectContext());
		/*UGameplayEffect ge; error
		FGameplayEffectSpecHandle c(new FGameplayEffectSpec(&ge, ASC->MakeEffectContext(), 1.0f));*/
		EffectSpecHandle.Data.Get()->TargetEffectSpecs.Add(TagrESH);
		//给游戏能力组件附加游戏效果
		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	}

	if (HasAuthority())
	{
		Destroy();
	}
	else
	{
		bHit = true;
	}

	
}

void AAEffectActo_Projectile::EndOverlap(AActor* OtherActor)
{

}


void AAEffectActo_Projectile::OnCompBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	BeginOvelap(OtherActor);
}

void AAEffectActo_Projectile::OnCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EndOverlap(OtherActor);
}



