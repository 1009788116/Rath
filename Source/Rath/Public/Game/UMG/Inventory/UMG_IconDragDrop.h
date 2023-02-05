// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_IconDragDrop.generated.h"

/**
 * 绘制一个用于拖拽的图片的UMG
 */
UCLASS()
class RATH_API UUMG_IconDragDrop : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UImage* Icon;
public:
	void DrawIcon(UTexture2D* InIcon) const;
};
