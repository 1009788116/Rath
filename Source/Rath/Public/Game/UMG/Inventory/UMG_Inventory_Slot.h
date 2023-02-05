// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG_SlotBase.h"
#include "UMG_Inventory_Slot.generated.h"

class UTextBlock;
/**
 * 背包插槽控件
 */
class UTexture2D;
UCLASS()
class RATH_API UUMG_Inventory_Slot : public UUMG_SlotBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int InventoryId = 0;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Num;
	
	void HiddenSlotNum();
	void ShowSlotNum();
	
	UPROPERTY(EditAnywhere,Category = "UMG")
	TSubclassOf<class UUMG_IconDragDrop> UMG_IconDragDrop;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void OnButtonClicked() override;
};
