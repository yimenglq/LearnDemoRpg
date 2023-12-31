// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	//设定指定碰撞通道的 响应方式
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	
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
