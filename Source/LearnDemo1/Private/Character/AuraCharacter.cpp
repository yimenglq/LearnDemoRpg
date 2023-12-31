// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"

AAuraCharacter::AAuraCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	//���ӵ���� 
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);


	//������ת�����ƶ�
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//��ת����
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.f, 0.0f);

	//ȡ������������Pawn����ת
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//ȡ�����ɱۼ̳и������ת
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();

	

}

