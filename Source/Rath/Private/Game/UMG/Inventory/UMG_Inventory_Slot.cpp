// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/UMG/Inventory/UMG_Inventory_Slot.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Rath/Public/Game/UMG/Inventory/UMG_IconDragDrop.h"
#include "Rath/Public/Game/UMG/Inventory/UMG_Inventory.h"

void UUMG_Inventory_Slot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUMG_Inventory_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUMG_Inventory_Slot::HiddenSlotNum()
{
	Num->SetVisibility(ESlateVisibility::Hidden);
}

void UUMG_Inventory_Slot::ShowSlotNum()
{
	Num->SetVisibility(ESlateVisibility::Visible);
}

void UUMG_Inventory_Slot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UUMG_Inventory_Slot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UUMG_Inventory_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	 if(InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton && bValid || InMouseEvent.IsTouchEvent())
	 {
	 	FReply Reply = FReply::Handled();
	 	const TSharedPtr<SWidget> SlateWidgetDrag = GetCachedWidget();
	 	if(SlateWidgetDrag.IsValid())
	 	{
	 		Reply.DetectDrag(SlateWidgetDrag.ToSharedRef(),EKeys::RightMouseButton);
	 		return Reply;
	 	}
	 }
	return FReply::Handled();
}

void UUMG_Inventory_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	if(UMG_IconDragDrop && SlotIcon && SlotIcon->Brush.GetResourceObject()) 
	{
		if(UUMG_IconDragDrop* IconDragDrop = CreateWidget<UUMG_IconDragDrop>(GetWorld(), UMG_IconDragDrop))
		{
			if(UDragDropOperation* InDragDropOperation = NewObject<UDragDropOperation>(GetTransientPackage(),UDragDropOperation::StaticClass()))
			{
				//强引用，避免GC ???
				InDragDropOperation->SetFlags(RF_StrongRefOnFrame);
				//图片赋值
				IconDragDrop->DrawIcon(Cast<UTexture2D>(SlotIcon->Brush.GetResourceObject()));
				//UE写好了的定位鼠标的位置进行渲染
				InDragDropOperation->DefaultDragVisual = IconDragDrop;
				//传入负载信息，告知我们这是从哪里拖过来的
				InDragDropOperation->Payload = this;
				HiddenSlotIcon();
				HiddenSlotNum();

				OutOperation = InDragDropOperation;
			}
		}
	}
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UUMG_Inventory_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if(InOperation)
	{
		if(UUMG_Inventory_Slot* OtherInventory_Slot = Cast<UUMG_Inventory_Slot>(InOperation->Payload))
		{
			GetRathCharacterFromUMG()->ClientCallServerSwapInventory(OtherInventory_Slot->InventoryId,InventoryId);
			return true;
		}
	}
	return false;
}

void UUMG_Inventory_Slot::OnButtonClicked()
{
	Super::OnButtonClicked();

	UKismetSystemLibrary::PrintString(GetWorld(),TEXT("执行物品功能"));
}
