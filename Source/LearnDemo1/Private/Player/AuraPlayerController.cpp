// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Iterface/HighLightIterface.h>

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;//���縴�� ����

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	

	check(AuraContext);
	//��ñ�����ǿ������ϵͳ
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);//��ӽ�ӳ�������� UEnhancedPlayerInput����AppliedInputContexts��
	bShowMouseCursor = true;//��ʾ���
	DefaultMouseCursor = EMouseCursor::Hand;//�����������ʽ
	/*
	 * ������������ģʽ�����ݽṹ����ģʽ���� UI ��Ӧ�û����룬��� UI �������������������/��ҿ��������л��ᡣ
	 */
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//���ù�����ӿ�����ģʽ
	InputModeData.SetHideCursorDuringCapture(false);// ��갴�µ��µ���ʱ��겶���ڼ��Ƿ����ع��
	SetInputMode(InputModeData);//��������ģʽ
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FindEnemyActor();

}

void AAuraPlayerController::SetupInputComponent()
{
	
	Super::SetupInputComponent();
	//�����ǿ������ؼ�
	UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent);
	//���� �󶨻ص�����   ETriggerEvent::Triggered���º� ��������  
	EInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

	
}

void AAuraPlayerController::FindEnemyActor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	
	if (!HitResult.bBlockingHit) return;
	ThisActor = Cast<IHighLightIterface>(	HitResult.GetActor());
	
	
	/*
	* A ThisActor == NULL    LastActor == NULL;
	* 
	* B ThisActor != NULL    LastActor == NULL;
	* 
	* C ThisActor == NULL    LastActor != NULL;
	* 
	* D ThisActor != NULL    LastActor != NULL; And  ThisActor == LastActor
	* 
	* E ThisActor != NULL    LastActor != NULL; And  ThisActor != LastActor
	* 
	*/

	if (ThisActor)
	{
		if (LastActor)
		{
			if (ThisActor == LastActor)
			{
				//D
				ThisActor->OpenHighLight();

			}
			else
			{
				//E
				LastActor->CloceHighLight();
				ThisActor->OpenHighLight();

			}

		}
		else
		{
			//B
			ThisActor->OpenHighLight();

		}


	}
	else
	{

		if (LastActor)
		{
			//C
			LastActor->CloceHighLight();

		}
		else
		{
			//A
		}

	}

	LastActor = ThisActor;

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//�ÿ�������תYaw���������ת��Yawһ��
	ControlRotation.Yaw = PlayerCameraManager->GetCameraRotation().Yaw;

	//��ò��������2Dֵ
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	//��ÿ�������ת
	const FRotator Rotator = GetControlRotation();
	//ȡ�ÿ�����ֻ��Yaw����ת
	const FRotator YawRotator(0.f, Rotator.Yaw, 0.f);
	//����Yaw��ת�����ϵ� X �ĵ�λ����
	const FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	//����Yaw��ת�����ϵ� Y �ĵ�λ����
	const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	//�����ҿ��������Ƶ�Pawn
	APawn* ControPawn = GetPawn();
	if (ControPawn)
	{
		//����˶�����
		ControPawn->AddMovementInput(ForwardDirection, InputAxisValue.X);
		ControPawn->AddMovementInput(RightDirection, InputAxisValue.Y);
	}

}


