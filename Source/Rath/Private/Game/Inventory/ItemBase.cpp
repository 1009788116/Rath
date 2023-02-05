// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/Inventory/ItemBase.h"

bool UItemBase::IsConsumable() const
{
	return MaxCount>=0?true:false;
}

FString UItemBase::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UItemBase::GetPrimaryAssetId() const
{
	//这是一个数据资产而不是一个蓝图，所以我们可以使用原始名称
	//如果是蓝图你还需要拆开 _C 后缀
	return FPrimaryAssetId(ItemType,GetFName());
}
