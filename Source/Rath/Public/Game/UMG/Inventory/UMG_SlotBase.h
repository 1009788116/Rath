// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG_Description.h"
#include "UMG_Base.h"
#include "UMG_SlotBase.generated.h"

class UButton;
class UImage;
/**
 * 基础插槽
 */
UCLASS(Abstract)
class RATH_API UUMG_SlotBase : public UUMG_Base
{
	GENERATED_BODY()
public:
	UUMG_SlotBase(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UImage* SlotIcon;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonClick;

	UFUNCTION()
	virtual void OnButtonClicked(){};
	
	UPROPERTY(EditDefaultsOnly,Category = "UMG")
	TSubclassOf<UUMG_Description> UMG_Tip;

	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "Tip")
	UWidget* GetSlotTip();
	
	void HiddenSlotIcon();
	void ShowSlotIcon();

	FText SlotDescriptionText;

	bool bValid = false;
};