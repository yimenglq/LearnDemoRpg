// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapons = CreateDefaultSubobject<USkeletalMeshComponent>("Weapons");//创建
	Weapons->SetCollisionEnabled(ECollisionEnabled::NoCollision);//关闭碰撞
	Weapons->SetupAttachment(GetMesh(), "WeaponHandSocket");//将组件绑定到骨骼网格体的 WeaponHandSocket 插槽上


	//更改此 PrimitiveComponent 的 ResponseToChannels 容器的成员  更改碰撞通道 响应方式
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::Die()
{
	//分开武器   拆开场景组件
	Weapons->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SeverDie();
}

void AAuraCharacterBase::SeverDie_Implementation()
{
	//Weapons->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Weapons->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Weapons->SetSimulatePhysics(true);
	Weapons->SetEnableGravity(true);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);//启用物理模拟
	GetMesh()->SetEnableGravity(true);//启用重力

	//设置碰撞检测  无碰撞
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
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

	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectSpecHandle.Data.Get()->Def, EffectSpecHandle.Data.Get()->GetLevel(), EffectContextHandle);
}



void AAuraCharacterBase::AddCharacterAbility(TSubclassOf<UGameplayAbility>& AbilityClass)
{

}

void AAuraCharacterBase::AddCharacterAbilityes(TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses)
{
	check(AbilitySystemComponent);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AddCharacterAbilityes(AbilityClasses);
}

void AAuraCharacterBase::AddCharacterAbilityes()
{
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	//将开始时的游戏能力加入该角色的GAS能力组件
	AuraAbilitySystemComponent->AddCharacterAbilityes(StartupAbilityes);
}

void AAuraCharacterBase::Dissolve()
{
	if (IsValid(MeshDissolve))
	{
		//创建材质动态实例
		UMaterialInstanceDynamic* MID =	UMaterialInstanceDynamic::Create(MeshDissolve, this);
		//设置材质
		GetMesh()->SetMaterial(0, MID);
		
		SetMeshDissolveTimeLine(MID);

	}
	
	if (IsValid(WeaponsDissolve))
	{
		//创建材质动态实例
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(WeaponsDissolve, this);
		//设置材质
		Weapons->SetMaterial(0, MID);
		SetWeaponsDissolveTimeLine(MID);
	}
}





