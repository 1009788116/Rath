// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RathGameInstance.generated.h"

/**
 * 游戏实例
 */
UCLASS()
class RATH_API URathGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category = "DefaultAutoLoadPrimarty")
	TArray<FPrimaryAssetType> AutoLoadTypes;

	virtual void Init() override;
	
	void AutoLoadDataAssets();
};
