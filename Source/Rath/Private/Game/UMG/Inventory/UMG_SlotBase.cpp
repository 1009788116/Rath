#include "Rath/Public/Game/UMG/Inventory/UMG_SlotBase.h"
#include "Components/Button.h"
#include "Components/Image.h"
// Fill out your copyright notice in the Description page of Project Settings.
UUMG_SlotBase::UUMG_SlotBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UUMG_SlotBase::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonClick->OnClicked.AddDynamic(this,&UUMG_SlotBase::OnButtonClicked);
}

UWidget* UUMG_SlotBase::GetSlotTip()
{
	if(UMG_Tip && bValid)
	{
		if(UUMG_Description* TempTip = CreateWidget<UUMG_Description>(GetWorld(),UMG_Tip))
		{
			TempTip->DescriptionTextBlock->SetText(SlotDescriptionText);
			return TempTip;
		}
	}
	return nullptr;
}

void UUMG_SlotBase::HiddenSlotIcon()
{
	SlotIcon->SetVisibility(ESlateVisibility::Hidden);
}

void UUMG_SlotBase::ShowSlotIcon()
{
	SlotIcon->SetVisibility(ESlateVisibility::Visible);
}
