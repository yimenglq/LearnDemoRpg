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

static TAutoConsoleVariable<bool> ConsoleVariable(TEXT("PC.Debug"), true, TEXT("Draw"), ECVF_Cheat);//����̨��������


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;//���縴�� ����
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	

	check(AuraContext);
	//��ñ�����ǿ������ϵͳ
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (!Subsystem) return;
	
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
	AutoMove();

}

void AAuraPlayerController::SetupInputComponent()
{
	
	Super::SetupInputComponent();
	//�����ǿ������ؼ�
	UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent);
	//���� �󶨻ص�����   ETriggerEvent::Triggered���º� ��������  
	EInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	check(AuraInputConfig);
	for (FInputToTag& AIC : AuraInputConfig->InputConfiges)
	{
		EInputComp->BindAction(AIC.InputAction, ETriggerEvent::Started, this, &AAuraPlayerController::AbilityInputTagPressed, AIC.InputTag);
		EInputComp->BindAction(AIC.InputAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::AbilityInputTagHold, AIC.InputTag);
		EInputComp->BindAction(AIC.InputAction, ETriggerEvent::Canceled, this, &AAuraPlayerController::AbilityInputTagReleased, AIC.InputTag);
		EInputComp->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
		EInputComp->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
	}
	
}

void AAuraPlayerController::FindEnemyActor()
{
	
	//��ȡ�������ײ������
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
			
			
				// ����һ��λ�ã�������ռ��У�������������ӽ���λ�õĵ㡣
			FVector	SplineLocation = Spline->FindLocationClosestToWorldLocation(Location, ESplineCoordinateSpace::World);
				
				//����λ�ã�������ռ��У�������ӽ���λ�õ��������ߵĵ�λ����������
			FVector  MoveDirection = Spline->FindDirectionClosestToWorldLocation(SplineLocation, ESplineCoordinateSpace::World);
				
			if (bIsStopAutoRido)
			{
				FHitResult Hit;
				const TArray<AActor*> ActorsToIgnore;
				if (UKismetSystemLibrary::LineTraceSingleByProfile(aPawn, Location, MoveLocation, Cast<AAuraCharacterBase>(aPawn)->GetCapsuleComponent()->GetCollisionProfileName(), false, ActorsToIgnore, EDrawDebugTrace::Persistent, Hit, true))
				{
					bIsStopAutoRido = false;
				}
				else
				{
					MoveDirection = (MoveLocation - Location).GetSafeNormal();
				}
				
			}
				
				aPawn->AddMovementInput(MoveDirection, 1.f);
				if(ConsoleVariable.GetValueOnAnyThread())
				 DrawDebugAltCone(GetWorld(), Location, MoveDirection.Rotation(), 10.f, 3.f, 3.f, FColor::Green, false, 20.f);
				
				DrawDebugSphere(GetWorld(), SplineLocation, 20.f, 6, FColor::Blue, false, 1.f);

				if ( (MoveLocation - Location).Length()  <= StopAutoRido)
				{
					bIsStopAutoRido = true;
					if ((MoveLocation - Location).Length() <= 100.f && bIsStopAutoRido)
					{
						bIsAutoRunMove = false;
						bIsStopAutoRido = false;
					}
						
				}
				
		}
	}


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

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGamePlayTags::Get().AbilityInput_LMB) && !ThisActor)
	{
		//��ȡ��Ϸ������ʱ��
		ThisLMBClickedTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
		bTwoClick = (ThisLMBClickedTime - LastLMBClickedTime) < TimeInterval;
		if ( bTwoClick && !Cast<AAuraEnemy>(ThisActor) )
		{

			bIsAutoRunMove = true;
			MoveLocation =	ThisHitResult.ImpactPoint;
			if (APawn* pawn = GetPawn())
			{
				//�� FindPath ��ͬ������·����
				NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, pawn->GetActorLocation(), MoveLocation);

				if (NavPath)
				{
					//������������е����е�
					Spline->ClearSplinePoints();
					for (FVector& PathPoint : NavPath->PathPoints)
					{

					
						DrawDebugSphere(GetWorld(), PathPoint, 20.f, 6, FColor::Red, false, 10.f);
						//��������ߵĵ�
						Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::Type::World);
					
					}
					if( !NavPath->PathPoints.IsEmpty())
					MoveLocation = NavPath->PathPoints[NavPath->PathPoints.Num()-1];

				}

			}
		}

			
		LastLMBClickedTime = ThisLMBClickedTime;

		return;
	}

	AAuraCharacterBase* ACB = Cast<AAuraCharacterBase>(GetPawn());
	if (ACB)
	{

		if (UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(ACB->GetAbilitySystemComponent()))
		{
			ASC->AbilityInputTagPressed(InputTag);


			////�������пɼ����������б�
			//TArray<FGameplayAbilitySpec>& AbilitySpeces = ASC->GetActivatableAbilities();
			//for (FGameplayAbilitySpec& AbilitySpec : AbilitySpeces)
			//{
			//	//�жϸ������� �Ƿ񲻴��ڻ״̬ �� �Ƿ��뵱ǰ��������ǩ��ͬ 
			//	if (!AbilitySpec.IsActive() && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			//	{
			//		AbilitySpec.InputPressed = true;
			//		//���Լ����������Ϸ����
			//		ASC->TryActivateAbility(AbilitySpec.Handle);
			//	}

			//}
		}
	}


}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
	AAuraCharacterBase* ACB = Cast<AAuraCharacterBase>(GetPawn());
	if (ACB)
	{

		if (UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(ACB->GetAbilitySystemComponent()))
		{
			ASC->AbilityInputTagReleased(InputTag);
		}
	}
}

void AAuraPlayerController::AbilityInputTagHold(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGamePlayTags::Get().AbilityInput_LMB))
	{
		APawn* aPawn = GetPawn();
		if (aPawn)
		{
			FVector Normal = (ThisHitResult.ImpactPoint - aPawn->GetActorLocation()).GetSafeNormal();
			aPawn->AddMovementInput(Normal);
			if(!bTwoClick)
			 bIsAutoRunMove = false;
		}

	}

	if (InputTag.MatchesTagExact(FAuraGamePlayTags::Get().AbilityInput_RMB) && bShiftKeyDown)
	if (AAuraCharacterBase* ACB = Cast<AAuraCharacterBase>(GetPawn()))
	{

		if (UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(ACB->GetAbilitySystemComponent()))
		{
			ASC->AbilityInputTagHold(InputTag);
		}
	}
}

