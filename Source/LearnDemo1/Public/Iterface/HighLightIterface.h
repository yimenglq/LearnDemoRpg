// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighLightIterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHighLightIterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEARNDEMO1_API IHighLightIterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//�����������
	virtual void OpenHighLight() = 0;
	//�رպ������
	virtual void CloceHighLight() = 0;
};
