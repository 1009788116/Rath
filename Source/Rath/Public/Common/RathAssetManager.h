// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Game/Inventory/ItemBase.h"
#include "Engine/AssetManager.h"
#include "Engine/Engine.h"
#include "RathAssetManager.generated.h"

/**
 * 资源管理器
 */
UCLASS()
class RATH_API URathAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	URathAssetManager();

	virtual void StartInitialLoading() override;

	static const FPrimaryAssetType PotionItemType;
	static const FPrimaryAssetType FoodItemType;
	static const FPrimaryAssetType SkillItemType;
	static const FPrimaryAssetType MaterialItemType;
	static const FPrimaryAssetType EquipmentItemType;

	static URathAssetManager& Get();

	UItemBase* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true) const;
};