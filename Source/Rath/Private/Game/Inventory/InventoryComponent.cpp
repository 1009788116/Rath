// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/Inventory/InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

FInventoryItem::FInventoryItem():ItemBase(nullptr),ItemCount(0)
{
	
}

bool FInventoryItem::IsValid()
{
	return ItemBase&&ItemCount>0?true:false;
}

void FInventoryItem::ResetSelf()
{
	ItemBase = nullptr;
	ItemCount =0;
}

UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	RathCharacter = Cast<ARathCharacter>(GetOwner());

	if(InventoryItems.Num()==0)
	{
		for (size_t i = 0;i<InventoryCapacity;i++)
		{
			InventoryItems.Add(FInventoryItem());
		}
	}
	InventoryItemChanged(InventoryItems);
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryComponent::AddInventoryItem(FInventoryItem InInventoryItem)
{
	//只在服务器上操作数据
	//if(GetOwner()->GetLocalRole() == ENetRole::ROLE_Authority)
	//{
		if(InInventoryItem.IsValid())
		{
			//寻找是否已经存在
			for (size_t i = 0;i<InventoryItems.Num();i++)
			{
				if(InventoryItems[i].ItemBase == InInventoryItem.ItemBase)
				{
					InventoryItems[i].ItemCount+=InInventoryItem.ItemCount;
					//通知UI
					UKismetSystemLibrary::PrintString( GetWorld(),TEXT("图标++"));
					InventoryItemChanged(InventoryItems);
					return true;
				}
			}

			//如果找不到，那么就寻找有没有空位
			for (size_t i = 0;i<InventoryItems.Num();i++)
			{
				if(!InventoryItems[i].ItemBase)
				{
					InventoryItems[i] = InInventoryItem;
					//通知UI
					UKismetSystemLibrary::PrintString( GetWorld(),TEXT("新加图标"));
					InventoryItemChanged(InventoryItems);
					return true;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("无法添加空的仓库物品!"));
			return false;
		}
		//无法添加物品，仓库已满!
		UE_LOG(LogTemp,Warning,TEXT("无法添加物品，仓库已满!"));
		return false;
	//}
	//无法在非服务器上操作数据
	//UE_LOG(LogTemp,Warning,TEXT("无法在非服务器上操作数据!"));
	//return false;
}

void UInventoryComponent::RemoveInventoryItem(int Index_Remove)
{
	InventoryItems[Index_Remove].ResetSelf();
	InventoryItemChanged(InventoryItems);
}

void UInventoryComponent::RemoveInventoryItemByItem(FInventoryItem InInventoryItem)
{
	for (size_t i = 0;i<InventoryItems.Num();i++)
	{
		if(InventoryItems[i].ItemBase == InInventoryItem.ItemBase)
		{
			InventoryItems[i].ItemCount-=InInventoryItem.ItemCount;
			if(InventoryItems[i].ItemCount<=0)
			{
				InventoryItems[i].ResetSelf();
			}
			//通知UI
			InventoryItemChanged(InventoryItems);
			break;
		}
	}
}

void UInventoryComponent::SwepInventoryItem(int Index_i, int Index_j)
{
	InventoryItems.Swap(Index_i,Index_j);
	InventoryItemChanged(InventoryItems);
}

void UInventoryComponent::UpdateUMG()
{
	InventoryItemChanged(InventoryItems);
}

void UInventoryComponent::InventoryItemChanged_Implementation(const TArray<FInventoryItem>& InInventoryItems)
{
	OnInventoryChanged.Broadcast(InventoryItems);
}
