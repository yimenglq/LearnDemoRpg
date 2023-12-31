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



