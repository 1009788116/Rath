// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/UMG/Inventory/UMG_Base.h"
#include "Rath/Public/Game/Character/Core/RathCharacter.h"

UUMG_Base::UUMG_Base(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UUMG_Base::PlayWidgetAnim(const FString& InAnimName)
{
	if(UWidgetAnimation* WidgetAnimation = GetNameWidgetAnimation(InAnimName))
	{
		PlayAnimation(WidgetAnimation);
	}
}

UWidgetAnimation* UUMG_Base::GetNameWidgetAnimation(const FString& InWidgetName)
{
	return nullptr;
}

ARathCharacter* UUMG_Base::GetRathCharacterFromUMG()
{
	return Cast<ARathCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}
