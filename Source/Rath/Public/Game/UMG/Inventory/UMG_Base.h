// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_Base.generated.h"

class ARathCharacter;
/**
 * 基础UMG
 */
UCLASS(Abstract)
class RATH_API UUMG_Base : public UUserWidget
{
	GENERATED_BODY()
public:
	UUMG_Base(const FObjectInitializer& ObjectInitializer);
protected:
	void PlayWidgetAnim(const FString& InAnimName);
	UWidgetAnimation* GetNameWidgetAnimation(const FString& InWidgetName);
	
	ARathCharacter* GetRathCharacterFromUMG();
};
