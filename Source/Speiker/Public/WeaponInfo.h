// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponInfo.generated.h"

USTRUCT(BlueprintType)
struct FWeaponDamages
{
	GENERATED_USTRUCT_BODY()
	FWeaponDamages()
	{
		this->TorsoDamage = 0.0f;
		this->LegDamage = 0.0f;
		this->ArmDamage = 0.0f;
		this->HeadDamage = 0.0f;
	}

	FWeaponDamages(float torsoDamage, float legDamage, float armDamage, float headDamage)
	{
		this->TorsoDamage = torsoDamage;
		this->LegDamage = legDamage;
		this->ArmDamage = armDamage;
		this->HeadDamage = headDamage;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TorsoDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LegDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadDamage;
};

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()
	FWeaponInfo()
	{
		FWeaponDamages* weaponDamages = new FWeaponDamages(0.0f, 0.0f, 0.0f, 0.0f);
		this->WeaponDamages = *weaponDamages;
		this->IsFiring = false;
		this->RemainingMagazine = 0.0f;
		this->MaxMagazine = 0.0f;
		this->ReloadTime = 0.0f;
		this->IsReloading = false;
		this->CanFire = true;
		this->CanReload = true;
		this->FireRate = 0.1f;
		this->AmmoCostPerShot = 1.0f;
		this->WantsToShoot = false;
	}

	FWeaponInfo(FWeaponDamages weaponDamages, float maxMagazine, float reloadTime, float fireRate, float ammoPerShot)
	{
		this->WeaponDamages = weaponDamages;
		this->IsFiring = false;
		this->RemainingMagazine = maxMagazine;
		this->MaxMagazine = maxMagazine;
		this->ReloadTime = reloadTime;
		this->IsReloading = false;
		this->CanFire = true;
		this->CanReload = true;
		this->FireRate = fireRate;
		this->AmmoCostPerShot = ammoPerShot;
		this->WantsToShoot = false;
	}

	void SetDamages(float torsoDamage, float legDamage, float armDamage, float headDamage)
	{
		FWeaponDamages* weaponDamages = new FWeaponDamages(torsoDamage, legDamage, armDamage, headDamage);
		this->WeaponDamages = *weaponDamages;
	}

	void SetMaxMagazine(float newMaxMagazine, bool shouldReload)
	{
		this->MaxMagazine = newMaxMagazine;
		if (shouldReload)
		{
			this->RemainingMagazine = newMaxMagazine;
		}
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponDamages WeaponDamages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemainingMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoCostPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WantsToShoot;
};
