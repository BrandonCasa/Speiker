// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UAbilityComponent::GetAbilityCooldown(int abilityIndex)
{
	if (abilityIndex == 0)
	{
		float time = GetWorld()->GetTimerManager().GetTimerRemaining(Ability1Timer);
		if (time != -1.0f)
		{
			time /= Ability1Cooldown;
		}
		if (time == -1.0f)
		{
			time = 0.0f;
		}
		return time;
	}
	if (abilityIndex == 1)
	{
		float time = GetWorld()->GetTimerManager().GetTimerRemaining(Ability2Timer);
		if (time != -1.0f)
		{
			time /= Ability2Cooldown;
		}
		if (time == -1.0f)
		{
			time = 0.0f;
		}
		return time;
	}
	if (abilityIndex == 2)
	{
		float time = GetWorld()->GetTimerManager().GetTimerRemaining(Ability3Timer);
		if (time != -1.0f)
		{
			time /= Ability3Cooldown;
		}
		if (time == -1.0f)
		{
			time = 0.0f;
		}
		return time;
	}
	return -2.0f;
}

void UAbilityComponent::UseAbility1()
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(Ability1Timer) == -1.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(Ability1Timer, this, &UAbilityComponent::RefreshAbility1, Ability1Cooldown, false, -1.0f);
	}
}

void UAbilityComponent::UseAbility2()
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(Ability2Timer) == -1.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(Ability2Timer, this, &UAbilityComponent::RefreshAbility2, Ability2Cooldown, false, -1.0f);
	}
}

void UAbilityComponent::UseAbility3()
{
}

void UAbilityComponent::RefreshAbility1()
{
	GetWorld()->GetTimerManager().ClearTimer(Ability1Timer);
}

void UAbilityComponent::RefreshAbility2()
{
	GetWorld()->GetTimerManager().ClearTimer(Ability2Timer);
}