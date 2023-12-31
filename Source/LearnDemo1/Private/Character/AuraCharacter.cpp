// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"

AAuraCharacter::AAuraCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	//附加到组件 
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);


	//设置旋转朝向移动
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.f, 0.0f);

	//取消控制器控制Pawn的旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//取消弹簧臂继承父组件旋转
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();

	

}

