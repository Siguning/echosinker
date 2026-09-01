// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EchoBaseAttributeSet.h"
#include "EchoCharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEchoPoiseBrokenSignature, AActor*, InstigatorActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEchoDeathSignature, AActor*, InstigatorActor);

/**
 * 
 */
UCLASS()
class ECHOSINKER_API UEchoCharacterAttributeSet : public UEchoBaseAttributeSet
{
	GENERATED_BODY()
	
public:
	UEchoCharacterAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// ---- Attributes ----
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, MaxStamina);
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_Poise)
	FGameplayAttributeData Poise;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, Poise)
 
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_MaxPoise)
	FGameplayAttributeData MaxPoise;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, MaxPoise)
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, Mana)
 
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Vital", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, MaxMana)
	
	// ---- Meta Attributes ----
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Meta")
	FGameplayAttributeData IncomingDamage;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, IncomingDamage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Meta")
	FGameplayAttributeData IncomingPoiseDamage;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, IncomingPoiseDamage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Echo|Meta")
	FGameplayAttributeData IncomingHealing;
	ECHO_ATTRIBUTE_ACCESSORS(UEchoCharacterAttributeSet, IncomingHealing)
	
	// ---- Events ----
	UPROPERTY(BlueprintAssignable, Category = "Echo|Events")
	FEchoAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Echo|Events")
	FEchoPoiseBrokenSignature OnPoiseBroken;
	
	UPROPERTY(BlueprintAssignable, Category = "Echo|Events")
	FEchoDeathSignature OnDeath;
	
	// ---- Binds ----
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	
	UFUNCTION()
	virtual void OnRep_Poise(const FGameplayAttributeData& OldPoise);
	
	UFUNCTION()
	virtual void OnRep_MaxPoise(const FGameplayAttributeData& OldMaxPoise);
	
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	
private:
	static void ClampCurrentAttribute(float MaxValue, float& NewValue);
	
};
