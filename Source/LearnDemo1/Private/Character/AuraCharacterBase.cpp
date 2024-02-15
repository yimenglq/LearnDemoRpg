// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapons = CreateDefaultSubobject<USkeletalMeshComponent>("Weapons");//����
	Weapons->SetCollisionEnabled(ECollisionEnabled::NoCollision);//�ر���ײ
	Weapons->SetupAttachment(GetMesh(), "WeaponHandSocket");//������󶨵������������ WeaponHandSocket �����


	//���Ĵ� PrimitiveComponent �� ResponseToChannels �����ĳ�Ա  ������ײͨ�� ��Ӧ��ʽ
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::Die()
{
	//�ֿ�����   �𿪳������
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
	GetMesh()->SetSimulatePhysics(true);//��������ģ��
	GetMesh()->SetEnableGravity(true);//��������

	//������ײ���  ����ײ
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}


void AAuraCharacterBase::InitAbilityActorInfo()
{

}

void AAuraCharacterBase::InitAttributSet()
{
	//��Ҫ����
	ApplyEffectToSelf(InitPrimaryEffect);
	//��Ҫ����     ���� ��Ҫ����
	ApplyEffectToSelf(lastingSecondaryEffect);
	//�ֿ�����
	ApplyEffectToSelf(lastingResistanceEffect);
	//��ҪҪ����   ���� ��Ҫ����
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

	//����ʼʱ����Ϸ��������ý�ɫ��GAS�������
	AuraAbilitySystemComponent->AddCharacterAbilityes(StartupAbilityes);
}

void AAuraCharacterBase::Dissolve()
{
	if (IsValid(MeshDissolve))
	{
		//�������ʶ�̬ʵ��
		UMaterialInstanceDynamic* MID =	UMaterialInstanceDynamic::Create(MeshDissolve, this);
		//���ò���
		GetMesh()->SetMaterial(0, MID);
		
		SetMeshDissolveTimeLine(MID);

	}
	
	if (IsValid(WeaponsDissolve))
	{
		//�������ʶ�̬ʵ��
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(WeaponsDissolve, this);
		//���ò���
		Weapons->SetMaterial(0, MID);
		SetWeaponsDissolveTimeLine(MID);
	}
}





