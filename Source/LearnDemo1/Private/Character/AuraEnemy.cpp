// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	//�趨ָ����ײͨ���� ��Ӧ��ʽ
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	
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
