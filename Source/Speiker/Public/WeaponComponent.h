// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInfo.h"
#include "Animation/AnimMontage.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundAttenuation.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Config=Game )
class SPEIKER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//UFirstPersonWeaponComponent();
	UWeaponComponent();
	
	UFUNCTION(BlueprintCallable)
	void InitializeWeapon(FWeaponDamages partDamages, float startingAmmo, float maxAmmo, bool autoReload, float ammoPerShot, float ammoPerReload, float reloadSpeed, float fireRate, bool automaticWeapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponDamages PartDamages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InputShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemainingAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsFiring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoPerReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRateMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutomaticWeapon;

	UFUNCTION(BlueprintCallable)
	void StartShootInput();

	UFUNCTION(BlueprintCallable)
	void EndShootInput();

	UFUNCTION(BlueprintCallable)
	void StartReloadInput();

	UFUNCTION(BlueprintCallable)
	void BeginReload();
	
	UFUNCTION(BlueprintCallable)
	void FinishReload();
	
	UFUNCTION(BlueprintCallable)
	void BeginFiring();

	UFUNCTION(BlueprintCallable)
	void FireShot();

	UFUNCTION(BlueprintCallable)
	void TraceShot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* M_ShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* WeaponAudioAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* WeaponAudio;

	UFUNCTION(BlueprintPure)
	float GetRemainingAmmo() const { return RemainingAmmo; }
	
	UFUNCTION(BlueprintPure)
	float GetMaxAmmo() const { return MaxAmmo; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle FiringTimerHandle;
	FTimerHandle ReloadTimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
