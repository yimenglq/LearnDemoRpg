// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Actor/AEffectActo.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>

// Sets default values
AAEffectActo::AAEffectActo()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	ShapeComp = CreateDefaultSubobject<USphereComponent>("USphereComponent");

	RootComponent = MeshComp;
	//SetRootComponent(MeshComp);
	ShapeComp->SetupAttachment(MeshComp);

	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAEffectActo::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAEffectActo::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//���ص��¼�
	ShapeComp->OnComponentBeginOverlap.AddDynamic(this, &AAEffectActo::BeginOvelap);
	ShapeComp->OnComponentEndOverlap.AddDynamic(this, &AAEffectActo::EndOverlap);
}

void AAEffectActo::BeginOvelap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	IAbilitySystemInterface* IASIF_AbilitySys = Cast<IAbilitySystemInterface>(OtherActor);
	if (IASIF_AbilitySys)
	{
		//��ȡGAS�ؼ��б����ָ���������Լ���   ����λ����  UAbilitySystemComponent::InitializeComponent() 
		const UAuraAttributeSet* CAAS_Attribute = Cast<UAuraAttributeSet>(IASIF_AbilitySys->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		auto * AAS_Attribute = const_cast<UAuraAttributeSet*>(CAAS_Attribute);
		AAS_Attribute->SetHealth(AAS_Attribute->GetHealth() + 225.f);
		Destroy();
	}

}

void AAEffectActo::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}



