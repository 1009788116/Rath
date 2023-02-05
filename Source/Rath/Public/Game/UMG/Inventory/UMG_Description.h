// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rath/Public/Game/UMG/Inventory/UMG_Base.h"
#include "Components/TextBlock.h"
#include "UMG_Description.generated.h"

/**
 * 物品信息描述
 */
UCLASS()
class RATH_API UUMG_Description : public UUMG_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionTextBlock;
};
