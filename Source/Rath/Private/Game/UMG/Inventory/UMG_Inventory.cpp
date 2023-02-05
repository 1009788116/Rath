// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/UMG/Inventory/UMG_Inventory.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Rath/Public/Game/UMG/Inventory/UMG_Inventory_Slot.h"

void UUMG_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
	//去角色里面绑定信息
	GetRathCharacterFromUMG()->GetInventoryComponent()->OnInventoryChanged.AddUObject(this,&UUMG_Inventory::OnInventoryItemChanged);
}

void UUMG_Inventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

//绑定的是客户端仓库组件上的代理，但参数是从服务器上传递过来的
void UUMG_Inventory::OnInventoryItemChanged(TArray<FInventoryItem> InInventoryItems)
{
	//第一次用插槽填满格子
	if(GridPanel_SlotGrid->GetChildrenCount()==0)
	{
		for (size_t i = 0;i<ItemRowCount;i++)
		{
			for(size_t j = 0;j<ItemColumnCount;j++)
			{
				if(UUMG_Inventory_Slot* Inventory_Slot = CreateWidget<UUMG_Inventory_Slot>(GetWorld(),UMG_Inventory_Slot))
				{
					Inventory_Slot->InventoryId = i*ItemColumnCount + j;
					if(GridPanel_SlotGrid->AddChildToGrid(Inventory_Slot,i,j))
					{
						
					}
				}
			}
		}
	}
	//之后就是刷新数据到显示上
	if(InInventoryItems.Num()>0)
	{
		for (size_t i = 0;i<ItemRowCount;i++)
		{
			for(size_t j = 0;j<ItemColumnCount;j++)
			{
				if(UUMG_Inventory_Slot* InSlot = Cast<UUMG_Inventory_Slot>(GridPanel_SlotGrid->GetChildAt(i * ItemColumnCount + j)))
				{
					//有数据就更新并显示
					if(InInventoryItems[i*ItemColumnCount+j].IsValid())
					{
						InSlot->ButtonClick->SetVisibility(ESlateVisibility::Visible);
						InSlot->Num->SetText(FText::FromString(FString::FromInt(InInventoryItems[i*ItemColumnCount+j].ItemCount)));
						InSlot->Num->SetVisibility(ESlateVisibility::Visible);
						InSlot->SlotIcon->SetBrushFromTexture(InInventoryItems[i*ItemColumnCount+j].ItemBase->ItemIcon);
						InSlot->SlotIcon->SetVisibility(ESlateVisibility::Visible);
						InSlot->SlotDescriptionText = InInventoryItems[i*ItemColumnCount+j].ItemBase->ItemDescription;

						InSlot->bValid = true;
					}
					//无数据就隐藏
					else
					{
						InSlot->ButtonClick->SetVisibility(ESlateVisibility::Hidden);
						InSlot->Num->SetVisibility(ESlateVisibility::Hidden);
						InSlot->SlotIcon->SetVisibility(ESlateVisibility::Hidden);

						InSlot->bValid = false;
					}
				}
			}
		}
	}
}