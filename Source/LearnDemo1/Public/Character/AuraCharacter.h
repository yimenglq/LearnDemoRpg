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
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<	USpringArmComponent>  SpringArmComp;//���ɱ����

	UPROPERTY(VisibleAnywhere)
	TObjectPtr < UCameraComponent> CameraComp;//��������


};
