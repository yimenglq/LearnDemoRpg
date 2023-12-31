// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Iterface/HighLightIterface.h>

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;//网络复制 允许

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	

	check(AuraContext);
	//获得本地增强输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);//添加进映射上下文 UEnhancedPlayerInput：：AppliedInputContexts中
	bShowMouseCursor = true;//显示鼠标
	DefaultMouseCursor = EMouseCursor::Hand;//设置鼠标光标样式
	/*
	 * 用于设置输入模式的数据结构，该模式允许 UI 响应用户输入，如果 UI 不处理它，则玩家输入/玩家控制器将有机会。
	 */
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置光标在视口锁定模式
	InputModeData.SetHideCursorDuringCapture(false);// 鼠标按下导致的临时鼠标捕获期间是否隐藏光标
	SetInputMode(InputModeData);//设置输入模式
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FindEnemyActor();

}

void AAuraPlayerController::SetupInputComponent()
{
	
	Super::SetupInputComponent();
	//获得增强型输入控件
	UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent);
	//输入 绑定回调函数   ETriggerEvent::Triggered按下后 继续触发  
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
	//让控制器旋转Yaw与摄像机旋转的Yaw一致
	ControlRotation.Yaw = PlayerCameraManager->GetCameraRotation().Yaw;

	//获得操作输出的2D值
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	//获得控制器旋转
	const FRotator Rotator = GetControlRotation();
	//取得控制器只在Yaw的旋转
	const FRotator YawRotator(0.f, Rotator.Yaw, 0.f);
	//返回Yaw旋转方向上的 X 的单位向量
	const FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	//返回Yaw旋转方向上的 Y 的单位向量
	const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	//获得玩家控制器控制的Pawn
	APawn* ControPawn = GetPawn();
	if (ControPawn)
	{
		//添加运动输入
		ControPawn->AddMovementInput(ForwardDirection, InputAxisValue.X);
		ControPawn->AddMovementInput(RightDirection, InputAxisValue.Y);
	}

}


