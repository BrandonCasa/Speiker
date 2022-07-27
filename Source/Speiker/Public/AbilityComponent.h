// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPEIKER_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Ability1Cooldown{5.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Ability2Cooldown{5.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Ability3Cooldown{45.0f};

	FTimerHandle Ability1Timer;
	FTimerHandle Ability2Timer;
	FTimerHandle Ability3Timer;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetAbilityCooldown(int abilityIndex);

	UFUNCTION(BlueprintCallable)
	void UseAbility1();

	UFUNCTION(BlueprintCallable)
	void RefreshAbility1();

	UFUNCTION(BlueprintCallable)
	void UseAbility2();
	
	UFUNCTION(BlueprintCallable)
	void RefreshAbility2();

	UFUNCTION(BlueprintCallable)
	void UseAbility3();
};
