// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include"Iterface\HighLightIterface.h"
#include "AuraEnemy.generated.h"

/**
 * �з�NPC����
 */
UCLASS()
class LEARNDEMO1_API AAuraEnemy : public AAuraCharacterBase, public IHighLightIterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	//�����������
	virtual void OpenHighLight() override;
	//�رպ������
	virtual void CloceHighLight() override;

};