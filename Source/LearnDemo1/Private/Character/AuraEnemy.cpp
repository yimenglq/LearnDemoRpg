// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Character/AuraEnemy.h"


AAuraEnemy::AAuraEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");

	//设定指定碰撞通道的 响应方式
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	

}

void AAuraEnemy::InitAbilityActorInfo()
{
	//初始化GAS组件 Owner 是创造者 Avatar 是在世界中具体的化身
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbiltyActorInfoSet();
	//初始化属性
	InitAttributSet();

}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();

}

void AAuraEnemy::OpenHighLight()
{
	//启用自定义深度值
	GetMesh()->SetRenderCustomDepth(true);
	// 设置自定义深度值
	GetMesh()->SetCustomDepthStencilValue(250);
	//启用自定义深度值
	Weapons->SetRenderCustomDepth(true);
	// 设置自定义深度值
	Weapons->SetCustomDepthStencilValue(250);
}

void AAuraEnemy::CloceHighLight()
{
	//关闭自定义深度值
	GetMesh()->SetRenderCustomDepth(false);
	Weapons->SetRenderCustomDepth(false);
}




