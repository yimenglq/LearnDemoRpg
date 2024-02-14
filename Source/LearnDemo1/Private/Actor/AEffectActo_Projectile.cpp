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
	//��ֹ�������ݻ�ʱ �ͻ��˻�û��Ӧ
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
		
		//�����ײ��Ŀ�굽��ϷЧ������ʵ������
		FGameplayEffectSpecHandle TagrESH = ASC->MakeOutgoingSpec(GameplayEffectClass, 0.f, ASC->MakeEffectContext());
		/*UGameplayEffect ge; error
		FGameplayEffectSpecHandle c(new FGameplayEffectSpec(&ge, ASC->MakeEffectContext(), 1.0f));*/
		EffectSpecHandle.Data.Get()->TargetEffectSpecs.Add(TagrESH);
		//����Ϸ�������������ϷЧ��
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



