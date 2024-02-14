// Fill out your copyright notice in the Description page of Project Settings.
#include"AbilitySystem\AuraAbilitySystemComponent.h"

#include "Character/AuraCharacter.h"

#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include <Player/AuraPlayerState.h>
#include <UI/WidgetController/WidgetController.h>
#include <UI/HUD/AuraHUD.h>


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



void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (bInited) return;

	InitAbilityActorInfo();
	AddCharacterAbilityes();
}

void AAuraCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void AAuraCharacter::OnRep_PlayerState()
{
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{

	//������״̬
	AAuraPlayerState* PlayS = GetPlayerState<AAuraPlayerState>();
	check(PlayS);
	//��ʼ��GAS���
	PlayS->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayS, this);
	
	Cast<UAuraAbilitySystemComponent>(PlayS->GetAbilitySystemComponent())->AbiltyActorInfoSet();

	//�洢GAS���
	AbilitySystemComponent = PlayS->GetAbilitySystemComponent();
	//�洢���Լ���
	AttributeSet = PlayS->GetAttributeSet();
	
	//��ʼ������
	InitAttributSet();


	APlayerController* PCL = GetController<APlayerController>();
	
	if ( !PCL || !PCL->IsLocalController()) return;

	//�ڱ��ص���ҿ�����������
	//AAuraPlayerState* PS = PCL->GetPlayerState< AAuraPlayerState>();
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PlayS->GetAbilitySystemComponent());
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PlayS->GetAttributeSet());
	AAuraHUD* Hud =	Cast<AAuraHUD>( PCL->GetHUD());
	if(Hud)
	Hud->InitAuraHUD(FWidgetControllerParms(PCL, PlayS, ASC, AS));



}
