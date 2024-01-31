// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include"Iterface\HighLightIterface.h"
#include"Iterface\CombatInterface.h"
#include <Components/WidgetComponent.h>
#include "AuraEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuraAttributeDelegate, float, NewValue);

/**
 * �з�NPC����
 */
UCLASS(Blueprintable)
class LEARNDEMO1_API AAuraEnemy : public AAuraCharacterBase, public IHighLightIterface, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();


	//overide IHighLightIterface

	//�����������
	virtual void OpenHighLight() override;
	//�رպ������
	virtual void CloceHighLight() override;
	//End 

	//Override ICombatInterface
	
	virtual int32 GetLevel() const  override { return Level; };

	virtual int32 BP_GetLevel_Implementation() override { return GetLevel(); };
	//End

	//Override  AAuraCharacterBase
	virtual void InitAbilityActorInfo() override;
	//��ʼ������
	virtual void InitAttributSet() override;
	//End


	UPROPERTY(BlueprintAssignable)
	FAuraAttributeDelegate OnHealthAttributeDelegate;
	UPROPERTY(BlueprintAssignable)
	FAuraAttributeDelegate OnMaxHealthAttributeDelegate;
protected:
	virtual void BeginPlay() override;


	//��ɫ�ȼ�
	UPROPERTY(EditAnywhere, Category = "00-CharacterBase")
	int32 Level = 1;


	//��������� 3D �������ṩ��һ�����棬�����ڸ�ͼ������Ⱦͨ����Ⱦ����Ļ�ϵĹ�����
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;



};
