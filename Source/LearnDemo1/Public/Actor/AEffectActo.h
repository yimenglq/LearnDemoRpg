// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEffectActo.generated.h"

class USphereComponent;

UCLASS()
class LEARNDEMO1_API AAEffectActo : public AActor
{
	GENERATED_BODY()
	
public:	

	AAEffectActo();

protected:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()//��ײ��ʼ�ص��¼�
	virtual void BeginOvelap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()//��ײ�����ص��¼�
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	


protected:
	UPROPERTY(VisibleAnywhere)//��̬������
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere)//������ײ
	TObjectPtr<USphereComponent> ShapeComp;
};
