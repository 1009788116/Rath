// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Ability/AttributeSet/AttributeSet_Base.h"
#include "Game/Character/Core/RathCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UAttributeSet_Base::UAttributeSet_Base()
{
	InitHealth(60.0f);
	InitMaxHealth(100.0f);
}

void UAttributeSet_Base::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health,MaxHealth,NewValue,GetHealthAttribute());
	}
	// else if(Attribute == GetMaxHealthAttribe())
	// {
	// 	AdjustAttributeForMaxChange(Health,MaxHealth,NewValue,GetHealthAttribute());
	// }
}

void UAttributeSet_Base::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	//GameplayEffectContext结构体存有关于GameplayEffectSpec创建者(Instigator)和TargetData的信息
	// FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	// UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	// const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	//
	// float DeltaValue = 0;
	// if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	// {
	// 	DeltaValue = Data.EvaluatedData.Magnitude;
	// }
	//
	// //获取角色应用
	// AActor* TargetActor = nullptr;
	// ARathCharacter* TargetCharacter = nullptr;
	// if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	// {
	// 	TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	// 	TargetCharacter = Cast<ARathCharacter>(TargetActor);
	// }

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.0f,GetMaxHealth()));

		// if (TargetCharacter)
		// {
		// 	TargetCharacter->HandleHealthChanged(DeltaValue,SourceTags);
		// }
	}
}

// void UAttributeSet_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProperties) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProperties);
// }

void UAttributeSet_Base::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)const
{
	//获得UAbilitySystemComponent实例
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	//Getter方法获取的都是current value而不是base value
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		//Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;
		//通过UAbilitySystemComponent实例
		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

// void UAttributeSet_Base::OnRep_Health()
// {
// 	UE_LOG(LogTemp,Warning,TEXT("OnRep_Health"));
// }
//
// void UAttributeSet_Base::OnRep_MaxHealth()
// {
// 	UE_LOG(LogTemp,Warning,TEXT("OnRep_MaxHealth"));
// }