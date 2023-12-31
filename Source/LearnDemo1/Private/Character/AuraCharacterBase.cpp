// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Weapons = CreateDefaultSubobject<USkeletalMeshComponent>("Weapons");//����
	Weapons->SetCollisionEnabled(ECollisionEnabled::NoCollision);//�ر���ײ
	Weapons->SetupAttachment(GetMesh(), "WeaponHandSocket");//������󶨵������������ WeaponHandSocket �����


}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}



