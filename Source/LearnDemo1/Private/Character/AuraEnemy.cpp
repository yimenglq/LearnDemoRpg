// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include<AbilitySystem\DA\OccupationInfoDataAsset.h>
#include "Character/AuraEnemy.h"
#include <UI/Widget/AuraWidget.h>
#include <AbilitySystem/AuraAbillitySystemLibrary.h>


AAuraEnemy::AAuraEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(RootComponent);

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

void AAuraEnemy::InitAttributSet()
{
	//����ְҵ��ʼ������
	UAuraAbillitySystemLibrary::InitOccupationAttibuate(this, OccupationType);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();

	//����һ��Σ�յĲ��� ������ص� UWidgetController �� AAuraEnemy ���͵�ָ��ָ��ת��
	Cast< UAuraWidget>(HealthWidgetComponent->GetWidget())->SetWidgetController((UWidgetController*)this);
	UAuraAttributeSet* AS =  Cast<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthAttributeDelegate.Broadcast(Data.NewValue);
		}

	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthAttributeDelegate.Broadcast(Data.NewValue);
		}

	);
	OnMaxHealthAttributeDelegate.Broadcast(AS->GetHealth());
	OnHealthAttributeDelegate.Broadcast(AS->GetMaxHealth());

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




