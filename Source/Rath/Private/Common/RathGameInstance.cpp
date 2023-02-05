// Copyright © 2022 Rath. All rights reserved.
#include "Rath/Public/Common/RathGameInstance.h"
#include "Rath/Public/Common/RathAssetManager.h"

void URathGameInstance::Init()
{
	Super::Init();
	AutoLoadDataAssets();
}

void URathGameInstance::AutoLoadDataAssets()
{
	URathAssetManager& Manager = URathAssetManager::Get();
	for(auto& Type : AutoLoadTypes)
	{
		FPrimaryAssetType CurrentType = Type;
		TArray<FPrimaryAssetId> AssetIds;
		if(Manager.GetPrimaryAssetIdList(CurrentType,AssetIds))
		{
			Manager.LoadPrimaryAssets(AssetIds,TArray<FName>(),FStreamableDelegate(),0);
		}
	}
}
