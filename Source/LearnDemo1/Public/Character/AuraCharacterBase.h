// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include"Components\CapsuleComponent.h"
#include "AuraCharacterBase.generated.h"

/*
*  人形基类 
* 
*/

UCLASS()
class LEARNDEMO1_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,Category="AuraCharacterBase")
	TObjectPtr<USkeletalMeshComponent> Weapons;//武器骨骼网格体



};
