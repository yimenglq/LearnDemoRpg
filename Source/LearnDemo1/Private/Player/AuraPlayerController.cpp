// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Iterface/HighLightIterface.h>
#include"GameplayTagContainer.h"
#include <Character/AuraCharacterBase.h>
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include"Input\AuraInputConfigDA.h"
#include <FAuraGamePlayTags.h>
#include"GameFramework\GameStateBase.h"
#include <Character/AuraEnemy.h>
#include <Components/SplineComponent.h>
#include <NavigationSystem.h>
#include"NavigationSystem\Public\NavigationPath.h"
#include <Kismet/KismetSystemLibrary.h>

//#include <ApplicationCore/Private/Windows/WindowsApplication.cpp>

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;//网络复制 允许
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	

	check(AuraContext);
	//获得本地增强输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (!Subsystem) return;
	
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
	AutoMove();

}

void AAuraPlayerController::SetupInputComponent()
{
	
	Super::SetupInputComponent();
	//获得增强型输入控件
	UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent);
	//输入 绑定回调函数   ETriggerEvent::Triggered按下后 继续触发  
	EInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	check(AuraInputConfig);
	for (FInputToTag& AIC : AuraInputConfig->InputConfiges)
	{
		EInputComp->BindAction(AIC.InputAction, ETriggerEvent::Started, this, &AAuraPlayerController::AbilityInputTagPressed, AIC.InputTag);

	}
	
}

void AAuraPlayerController::FindEnemyActor()
{
	
	//获取鼠标下碰撞的物体
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, ThisHitResult);
	
	if (!ThisHitResult.bBlockingHit) return;
	ThisActor = Cast<IHighLightIterface>(	ThisHitResult.GetActor());
	
	
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



void AAuraPlayerController::AutoMove()
{


	if (bIsAutoRunMove)
	{
		if (APawn* aPawn = GetPawn())
		{
			FVector Location = aPawn->GetActorLocation();
			
			
				// 给定一个位置，在世界空间中，返回曲线上最接近该位置的点。
			FVector	SplineLocation = Spline->FindLocationClosestToWorldLocation(Location, ESplineCoordinateSpace::World);
				
				//给定位置，在世界空间中，返回最接近该位置的样条切线的单位方向向量。
			FVector  MoveDirection = Spline->FindDirectionClosestToWorldLocation(SplineLocation, ESplineCoordinateSpace::World);
				
			if (bIsStopAutoRido)
			{
				FHitResult Hit;
				const TArray<AActor*> ActorsToIgnore;
				if (UKismetSystemLibrary::LineTraceSingleByProfile(aPawn, Location, MoveLocation, Cast<AAuraCharacterBase>(aPawn)->GetCapsuleComponent()->GetCollisionProfileName(), false, ActorsToIgnore, EDrawDebugTrace::None, Hit, true))
				{
					bIsStopAutoRido = false;
				}
				else
				{
					MoveDirection = (MoveLocation - Location).GetSafeNormal();
				}
				
			}
				
				aPawn->AddMovementInput(MoveDirection, 1.f);
				DrawDebugAltCone(GetWorld(), Location, MoveDirection.Rotation(), 10.f, 3.f, 3.f, FColor::Green, false, 20.f);
				
				DrawDebugSphere(GetWorld(), SplineLocation, 20.f, 6, FColor::Blue, false, 1.f);

				if ( (MoveLocation - Location).Length()  <= StopAutoRido)
				{
					bIsStopAutoRido = true;
					if( (MoveLocation - Location).Length() <= 100.f && bIsStopAutoRido)
						bIsAutoRunMove = false;
				}
				
		}
	}


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

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGamePlayTags::Get().AbilityInput_LMB))
	{
		//获取游戏服务器时间
		ThisLMBClickedTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
		if ( (ThisLMBClickedTime - LastLMBClickedTime) < TimeInterval && !Cast<AAuraEnemy>(ThisActor) )
		{

			bIsAutoRunMove = true;
			MoveLocation =	ThisHitResult.ImpactPoint;
			if (APawn* pawn = GetPawn())
			{
				//在 FindPath 中同步查找路径。
				NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, pawn->GetActorLocation(), MoveLocation);

				if (NavPath)
				{
					//清除样条曲线中的所有点
					Spline->ClearSplinePoints();
					for (FVector& PathPoint : NavPath->PathPoints)
					{

					
						DrawDebugSphere(GetWorld(), PathPoint, 20.f, 6, FColor::Red, false, 10.f);
						//添加样条线的点
						Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::Type::World);
					
					}
					if( !NavPath->PathPoints.IsEmpty())
					MoveLocation = NavPath->PathPoints[NavPath->PathPoints.Num()-1];

				}

			}
		}

			
		LastLMBClickedTime = ThisLMBClickedTime;

	}





	/////
	AAuraCharacterBase* ACB = Cast<AAuraCharacterBase>(GetPawn());
	if (ACB)
	{

		if (UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(ACB->GetAbilitySystemComponent()))
		{
			//返回所有可激活能力的列表
			TArray<FGameplayAbilitySpec>& AbilitySpeces = ASC->GetActivatableAbilities();
			for (FGameplayAbilitySpec& AbilitySpec : AbilitySpeces)
			{
				//判断该能力中 是否不处于活动状态 且 是否与当前的启动标签相同 
				if (!AbilitySpec.IsActive() && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
				{
					AbilitySpec.InputPressed = true;
					//尝试激活给定的游戏能力
					ASC->TryActivateAbility(AbilitySpec.Handle);

				}

			}
		}
	}


}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	

}

