// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapons = CreateDefaultSubobject<USkeletalMeshComponent>("Weapons");//创建
	Weapons->SetCollisionEnabled(ECollisionEnabled::NoCollision);//关闭碰撞
	Weapons->SetupAttachment(GetMesh(), "WeaponHandSocket");//将组件绑定到骨骼网格体的 WeaponHandSocket 插槽上


}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{

}

void AAuraCharacterBase::InitAttributSet()
{
	//主要属性
	ApplyEffectToSelf(InitPrimaryEffect);
	//次要属性     依赖 主要属性
	ApplyEffectToSelf(lastingSecondaryEffect);
	//抵抗属性
	ApplyEffectToSelf(lastingResistanceEffect);
	//重要要属性   依赖 主要属性
	ApplyEffectToSelf(InitVitalEffect);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	check(GameplayEffectClass);
	check(AbilitySystemComponent);

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectSpecHandle.Data.Get()->Def, EffectSpecHandle.Data.Get()->GetLevel(), EffectContextHandle);
}





