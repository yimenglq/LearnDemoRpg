// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Character/AuraEnemy.h"


AAuraEnemy::AAuraEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");

	//�趨ָ����ײͨ���� ��Ӧ��ʽ
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	

}

void AAuraEnemy::InitAbilityActorInfo()
{
	//��ʼ��GAS��� Owner �Ǵ����� Avatar ���������о���Ļ���
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbiltyActorInfoSet();
	//��ʼ������
	InitAttributSet();

}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();

}

void AAuraEnemy::OpenHighLight()
{
	//�����Զ������ֵ
	GetMesh()->SetRenderCustomDepth(true);
	// �����Զ������ֵ
	GetMesh()->SetCustomDepthStencilValue(250);
	//�����Զ������ֵ
	Weapons->SetRenderCustomDepth(true);
	// �����Զ������ֵ
	Weapons->SetCustomDepthStencilValue(250);
}

void AAuraEnemy::CloceHighLight()
{
	//�ر��Զ������ֵ
	GetMesh()->SetRenderCustomDepth(false);
	Weapons->SetRenderCustomDepth(false);
}




