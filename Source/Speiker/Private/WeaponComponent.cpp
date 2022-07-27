// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "PlayerChar.h"
#include "Components/AudioComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWeaponComponent::InitializeWeapon(FWeaponDamages partDamages, float startingAmmo, float maxAmmo, bool autoReload, float ammoPerShot, float ammoPerReload, float reloadSpeed, float fireRate, bool automaticWeapon)
{
	PartDamages = partDamages;
	InputShooting = false;
	RemainingAmmo = startingAmmo;
	MaxAmmo = maxAmmo;
	IsFiring = false;
	IsReloading = false;
	AutoReload = autoReload;
	AmmoPerShot = ammoPerShot;
	AmmoPerReload = ammoPerReload;
	ReloadSpeed = reloadSpeed;
	ReloadMultiplier = 1.0f;
	FireRate = fireRate;
	FireRateMultiplier = 1.0f;
	AutomaticWeapon = automaticWeapon;
}

void UWeaponComponent::StartShootInput()
{
	InputShooting = true;
	if (!IsFiring && !IsReloading)
	{
		if (RemainingAmmo >= AmmoPerShot)
		{
			IsFiring = true;
			BeginFiring();
		} else
		{
			IsReloading = true;
			BeginReload();
		}
	}
}

void UWeaponComponent::EndShootInput()
{
	InputShooting = false;
	if (IsFiring)
	{
		IsFiring = false;
	}
}

void UWeaponComponent::StartReloadInput()
{
	if (RemainingAmmo < MaxAmmo)
	{
		IsReloading = true;
		BeginReload();
	}
}

void UWeaponComponent::BeginReload()
{
	IsFiring = false;
	GetWorld()->GetTimerManager().ClearTimer(FiringTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &UWeaponComponent::FinishReload, ReloadSpeed * ReloadMultiplier, false, -1.0f);
}

void UWeaponComponent::FinishReload()
{
	IsReloading = false;
	RemainingAmmo += AmmoPerReload;
	if (RemainingAmmo > MaxAmmo)
	{
		RemainingAmmo = MaxAmmo;
	}
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
	if (InputShooting)
	{
		IsFiring = true;
		BeginFiring();
	}
}

void UWeaponComponent::BeginFiring()
{
	if (!FiringTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(FiringTimerHandle, this, &UWeaponComponent::FireShot, FireRate * FireRateMultiplier, true, 0.0f);
	}
}

void UWeaponComponent::FireShot()
{
	if (IsFiring)
	{
		if (RemainingAmmo >= AmmoPerShot)
		{
			RemainingAmmo -= AmmoPerShot;
			TraceShot();
		}
	} else 
	{
		GetWorld()->GetTimerManager().ClearTimer(FiringTimerHandle);
	}
	if (!AutomaticWeapon)
	{
		IsFiring = false;
	}
	if (RemainingAmmo < AmmoPerShot && AutoReload)
	{
		IsReloading = true;
		BeginReload();
	}
}

void UWeaponComponent::TraceShot()
{
	FHitResult outHit;
	APlayerChar* myOwningCharacter = Cast<APlayerChar>(GetOwner());
	FVector start = myOwningCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	
	FVector forwardVector = myOwningCharacter->GetFirstPersonCameraComponent()->GetForwardVector();
	FVector end = ((forwardVector * 10000.0f) + start);
	FCollisionQueryParams collisionParams;
	
	//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, FireRate * FireRateMultiplier * 3.0f);

	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionParams);
	if (isHit)
	{
		if (outHit.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Hit Actor With Name: %s"),
			*outHit.GetActor()->GetName()));
		}
	}

	// Play firing animation montage
	myOwningCharacter->GetMeshCharacter1P()->GetAnimInstance()->Montage_Play(M_ShootMontage, 1.0f);
	myOwningCharacter->GetWeaponAudioComponent()->Play();
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

