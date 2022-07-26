// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DamageSources.generated.h"

UENUM(BlueprintType)
enum EDamageSources
{
	Gun_Source UMETA(DisplayName = "Gun"),
	Environment_Source UMETA(DisplayName = "Environment"),
	Unknown_Source UMETA(DisplayName = "Unknown"),
};

UENUM(BlueprintType)
enum EDamageType
{
	UpperTorso_Type UMETA(DisplayName = "Upper Torso"),
	LowerTorso_Type UMETA(DisplayName = "Lower Torso"),
	LeftLeg_Type UMETA(DisplayName = "Left Leg"),
	RightLeg_Type UMETA(DisplayName = "Right Leg"),
	LeftArm_Type UMETA(DisplayName = "Left Arm"),
	RightArm_Type UMETA(DisplayName = "Right Arm"),
	Head_Type UMETA(DisplayName = "Head"),
	Unknown_Type UMETA(DisplayName = "Unknown"),
};

USTRUCT(BlueprintType)
struct FPlayerDamageEvent
{
	GENERATED_USTRUCT_BODY()
	
	FPlayerDamageEvent()
	{
		this->DamageSource = EDamageSources::Unknown_Source;
		this->DamageType = EDamageType::Unknown_Type;
		this->DamageAmount = 0.0f;
		this->EventInstigator = nullptr;
		this->DamageDealer = nullptr;
		this->RemainingHealth = 1.0f;
	}

	FPlayerDamageEvent(float damageAmount, APlayerController* eventInstigator, AActor* damageDealer, TEnumAsByte<EDamageSources> damageSource, TEnumAsByte<EDamageType> damageType, float remainingHealth)
	{
		this->DamageSource = damageSource;
		this->DamageType = damageType;
		this->DamageAmount = damageAmount;
		this->EventInstigator = eventInstigator;
		this->DamageDealer = damageDealer;
		this->RemainingHealth = remainingHealth;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDamageSources> DamageSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerController* EventInstigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* DamageDealer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemainingHealth;
};
