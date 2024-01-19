// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
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
protected:
	virtual void BeginPlay() override;

	/** PlayerState �ı�ʱ ���ƻص�����*/
	virtual void OnRep_PlayerState() override;

	//����Pawn������ʱ  ������������
	virtual void PossessedBy(AController* NewController) override;




protected:
	//���ɱ����
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<	USpringArmComponent>  SpringArmComp;

	//��������
	UPROPERTY(VisibleAnywhere)
	TObjectPtr < UCameraComponent> CameraComp;

private:

	

};
