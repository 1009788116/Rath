// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rath/Public/Game/Inventory/InventoryComponent.h"
#include "UMG_Base.h"
//#include "Rath/Game/Inventory/Public/InventoryInterface.h"
#include "UMG_Inventory.generated.h"

/**
 * 背包控件
 */
class UUMG_Inventory_Slot;
UCLASS()
class RATH_API UUMG_Inventory : public UUMG_Base
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION()
	void OnInventoryItemChanged(TArray<FInventoryItem> InInventoryItems);
private:
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel_SlotGrid;

	UPROPERTY(EditAnywhere,Category = "UI")
	TSubclassOf<UUMG_Inventory_Slot> UMG_Inventory_Slot;
	
	UPROPERTY(EditAnywhere)
	int ItemColumnCount = 10;

	UPROPERTY(EditAnywhere)
	int ItemRowCount = 1;
};
