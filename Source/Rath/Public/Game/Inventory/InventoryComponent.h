// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Rath/Public/Game/Character/Core/RathCharacter.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_USTRUCT_BODY()
	
	FInventoryItem();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "InventoryItem")
	UItemBase* ItemBase;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "InventoryItem")
	int ItemCount;

	bool IsValid();

	void ResetSelf();
};
//传指针，引用，拷贝，单播，多播合适?
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryChangedNative, TArray<FInventoryItem>);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RATH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category = "Inventory")
	bool AddInventoryItem(FInventoryItem InInventoryItem);

	UFUNCTION(BlueprintCallable,Category = "Inventory")
	void RemoveInventoryItem(int Index_Remove);

	UFUNCTION(BlueprintCallable,Category = "Inventory")
	void RemoveInventoryItemByItem(FInventoryItem InInventoryItem);
	
	UFUNCTION(BlueprintCallable,Category = "Inventory")
	void SwepInventoryItem(int Index_i,int Index_j);

	//通知客户端UI刷新界面
	UFUNCTION(Client,Reliable)//Reliable: 可靠的
	void InventoryItemChanged(const TArray<FInventoryItem>& InInventoryItems);

	UFUNCTION()
	void UpdateUMG();
	
	//给UI绑定的代理
	FOnInventoryChangedNative OnInventoryChanged;

	//背包容量
	UPROPERTY()
	int InventoryCapacity = 10;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Inventory")
	TArray<FInventoryItem> InventoryItems;
	
	UPROPERTY()
	TWeakObjectPtr<ARathCharacter> RathCharacter;
};
