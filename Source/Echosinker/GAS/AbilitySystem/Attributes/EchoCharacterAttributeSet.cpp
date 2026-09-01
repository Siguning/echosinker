// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UEchoCharacterAttributeSet::UEchoCharacterAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitStamina(90.f);
	InitMaxStamina(90.f);
	InitPoise(50.f);
	InitMaxPoise(50.f);
	InitMana(70.f);
	InitMaxMana(70.f);
}

void UEchoCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, Poise, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, MaxPoise, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEchoCharacterAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UEchoCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, Health, OldHealth);
}

void UEchoCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void UEchoCharacterAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, Stamina, OldStamina);
}

void UEchoCharacterAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, MaxStamina, OldMaxStamina);
}

void UEchoCharacterAttributeSet::OnRep_Poise(const FGameplayAttributeData& OldPoise)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, Poise, OldPoise);
}

void UEchoCharacterAttributeSet::OnRep_MaxPoise(const FGameplayAttributeData& OldMaxPoise)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, MaxPoise, OldMaxPoise);
}

void UEchoCharacterAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, Mana, OldMana);
}

void UEchoCharacterAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEchoCharacterAttributeSet, MaxMana, OldMaxMana);
}

void UEchoCharacterAttributeSet::ClampCurrentAttribute(float MaxValue, float& NewValue)
{
	NewValue = FMath::Clamp(NewValue, 0.f, MaxValue);
}

void UEchoCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		ClampCurrentAttribute(GetMaxHealth(), NewValue);
	}
	else if (Attribute == GetStaminaAttribute())
	{
		ClampCurrentAttribute(GetMaxStamina(), NewValue);
	}
	else if (Attribute == GetPoiseAttribute())
	{
		ClampCurrentAttribute(GetMaxPoise(), NewValue);
	}
	else if (Attribute == GetManaAttribute())
	{
		ClampCurrentAttribute(GetMaxMana(), NewValue);
	}
}

void UEchoCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	const FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	AActor* Instigator = Context.GetOriginalInstigator();
	
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float DamageDone = GetIncomingDamage();
		SetIncomingDamage(0.f);
		
		if (DamageDone > 0.f)
		{
			const float NewHealth = FMath::Clamp(GetHealth() - DamageDone, 0.f, GetMaxHealth());
			SetHealth(NewHealth);
			
			OnHealthChanged.Broadcast(-DamageDone, NewHealth);
			
			if (NewHealth <= 0.f)
			{
				OnDeath.Broadcast(Instigator);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingPoiseDamageAttribute())
	{
		const float PoiseDamageDone = GetIncomingPoiseDamage();
		SetIncomingPoiseDamage(0.f);
		
		if (PoiseDamageDone > 0.f)
		{
			const float NewPoise = FMath::Clamp(GetPoise() - PoiseDamageDone, 0.f, GetMaxPoise());
			SetPoise(NewPoise);
			
			if (NewPoise <= 0.f)
			{
				OnPoiseBroken.Broadcast(Instigator);
				SetPoise(GetMaxPoise());
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingHealingAttribute())
	{
		const float HealingDone = GetIncomingHealing();
		SetIncomingHealing(0.f);
		
		if (HealingDone > 0.f)
		{
			const float NewHealth = FMath::Clamp(GetHealth() + HealingDone, 0.f, GetMaxHealth());
			SetHealth(NewHealth);
			OnHealthChanged.Broadcast(HealingDone, NewHealth);
		}
	}
}
