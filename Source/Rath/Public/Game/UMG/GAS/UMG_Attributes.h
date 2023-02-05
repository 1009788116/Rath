// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Ability/AttributeSet/AttributeSet_Base.h"
#include "Game/UMG/Inventory/UMG_Base.h"
#include "UMG_Attributes.generated.h"

/**
 * UMG 属性 显示
 */
UCLASS()
class RATH_API UUMG_Attributes : public UUMG_Base
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar *HPProgressBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_HP;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_MaxHP;
	
	void AttributeChanged(const FOnAttributeChangeData & Data) const;

private:
	UAbilitySystemComponent* AbilitySystemComponent;
};
