// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include"Iterface\CombatInterface.h"
#include"Player\AuraPlayerState.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 *  �������
 */
UCLASS()
class LEARNDEMO1_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

		
public:
	AAuraCharacter();
	
	//Override  AAuraCharacterBase
	virtual void InitAbilityActorInfo() override;

	//End
	
	//Override ICombatInterface
	virtual int32	GetLevel()const override {	if (AAuraPlayerState* PS = Cast<AAuraPlayerState>(GetPlayerState()) )  return PS->Level;  else   return 0; };
	
	virtual int32 BP_GetLevel_Implementation() override { return GetLevel(); };
	//End


protected:
	virtual void BeginPlay() override;

	/** PlayerState �ı�ʱ ���ƻص�����*/
	virtual void OnRep_PlayerState() override;

	//����Pawn������ʱ  ������������
	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaSeconds)override;


protected:
	//���ɱ����
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<	USpringArmComponent>  SpringArmComp;

	//��������
	UPROPERTY(VisibleAnywhere)
	TObjectPtr < UCameraComponent> CameraComp;

private:

	//�Ƿ��Ѿ���ʼ����
	bool bInited = false;

};
