// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UMG/GAS/UMG_Attributes.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Game/Character/Core/RathCharacter.h"

void UUMG_Attributes::NativeConstruct()
{
	Super::NativeConstruct();
	AbilitySystemComponent = GetRathCharacterFromUMG()->GetAbilitySystemComponent();
	if(AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Base::GetHealthAttribute()).AddUObject(this,&UUMG_Attributes::AttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Base::GetMaxHealthAttribute()).AddUObject(this,&UUMG_Attributes::AttributeChanged);
	}
}

void UUMG_Attributes::AttributeChanged(const FOnAttributeChangeData& Data) const
{
	if(AbilitySystemComponent != nullptr)
	{
		bool bHealthFound = false;
		bool bMaxHealthFound = false;
		float HP = AbilitySystemComponent->GetGameplayAttributeValue(UAttributeSet_Base::GetHealthAttribute(),bHealthFound);
		float MaxHP = AbilitySystemComponent->GetGameplayAttributeValue(UAttributeSet_Base::GetMaxHealthAttribute(),bMaxHealthFound);
		if(MaxHP!=0.0f)
		{
			Text_HP->SetText(FText::FromString(FString::FromInt(HP)));
			Text_MaxHP->SetText(FText::FromString(FString::FromInt(MaxHP)));
			HPProgressBar->SetPercent(HP/MaxHP);
		}
		if(HPProgressBar)
		{
			UE_LOG(LogTemp,Warning,TEXT("HP: %f %d   MaxHP: %f %d"),HP,bHealthFound,MaxHP,bMaxHealthFound);
		}
	}
}
