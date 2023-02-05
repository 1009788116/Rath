// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Common/RathAssetManager.h"

const FPrimaryAssetType URathAssetManager::PotionItemType = TEXT("PotionItemType");

const FPrimaryAssetType URathAssetManager::FoodItemType = TEXT("FoodItemType");

const FPrimaryAssetType URathAssetManager::SkillItemType = TEXT("SkillItemType");

const FPrimaryAssetType URathAssetManager::MaterialItemType = TEXT("MaterialItemType");

const FPrimaryAssetType URathAssetManager::EquipmentItemType = TEXT("EquipmentItemType");

URathAssetManager::URathAssetManager()
{
	
}

void URathAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//UAbilitySystemGlobals::Get().InitGlobalData();
}

URathAssetManager& URathAssetManager::Get()
{
	URathAssetManager* Singleton = Cast<URathAssetManager>(GEngine->AssetManager);
	if(Singleton)
	{
		return *Singleton;
	}
	else
	{
		//UE_LOG(LogAssetManager,Fatal,TEXT("如果资源管理器的类名未定义则无法使用资源管理器！"));
		return *NewObject<URathAssetManager>();//永远不要调用这个
	}
}

UItemBase* URathAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning /*Default: true*/)const
{
	const FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);
	//这是同步加载可能会出现小问题
	UItemBase* LoadedItem = Cast<UItemBase>(ItemPath.TryLoad());

	if(bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("通过FPrimaryAssetId：%s加载物品资产失败!"),*PrimaryAssetId.ToString());
	}

	return LoadedItem;
}
