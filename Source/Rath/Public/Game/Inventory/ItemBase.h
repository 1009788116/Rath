// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "ItemBase.generated.h"

class UGameplayAbility;
/**
 * 抽象类 PrimaryDataAsset Item
 */
UCLASS(Abstract,BlueprintType)
class RATH_API UItemBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//构造函数默认值设置
	UItemBase():Index(0),Price(0),Count(0),MaxCount(99),AbilityLevel(1){}

	//物品类型
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	FPrimaryAssetType ItemType;

	//物品名称
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	FName ItemName;

	//物品描述
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	FText ItemDescription;

	//物品序号
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	int Index;

	//物品图标
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	UTexture2D* ItemIcon;

	//价格
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	float Price;

	//当前数量
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Property")
	int Count;

	//最大可堆叠数量
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Max")
	int MaxCount;

	//最大等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Max")
	int MaxLevel;

	//是否可堆叠
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Type")
	bool bStackable;

	//是否可消耗
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "Type")
	bool IsConsumable() const;
	
	//可用的技能
	//UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Ability")
	//TSubclassOf<UGameplayAbility> GrantedAbility;

	//技能等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Ability")
	int AbilityLevel;

	UFUNCTION(BlueprintCallable,Category = "Item")
	FString GetIdentifierString() const;

	//获取资产ID
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
