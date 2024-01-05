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

	UFUNCTION()//碰撞开始重叠事件
	virtual void BeginOvelap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()//碰撞结束重叠事件
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	


protected:
	UPROPERTY(VisibleAnywhere)//静态网格体
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere)//球形碰撞
	TObjectPtr<USphereComponent> ShapeComp;
};
