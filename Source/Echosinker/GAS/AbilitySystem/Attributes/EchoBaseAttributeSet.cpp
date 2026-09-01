// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilitySystem/Attributes/EchoBaseAttributeSet.h"

void UEchoBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UEchoBaseAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}
