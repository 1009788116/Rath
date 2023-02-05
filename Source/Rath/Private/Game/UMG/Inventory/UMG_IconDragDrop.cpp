// Fill out your copyright notice in the Description page of Project Settings.
#include "Rath/Public/Game/UMG/Inventory/UMG_IconDragDrop.h"
#include "Components/Image.h"
void UUMG_IconDragDrop::DrawIcon(UTexture2D* InIcon) const
{
	Icon->SetBrushFromTexture(InIcon);
}
