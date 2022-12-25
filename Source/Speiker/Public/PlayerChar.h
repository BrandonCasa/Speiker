// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "DamageSources.h"
#include "NiagaraComponent.h"
#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PlayerChar.generated.h"
UCLASS()
class SPEIKER_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

	// Character Mesh 1P
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshCharacter1P;

	// Weapon Mesh 1P
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshWeapon1P;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	// Weapon Component
	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* WeaponAudioComponent;

	UPROPERTY(VisibleAnywhere)
	UAbilityComponent* AbilityComponent;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/////// Camera Settings ///////
	/// Mouse Sensitivity
	UPROPERTY(EditAnywhere)
	float Sensitivity{1.0f};

	/////// Stats Settings ///////
	/// Health
	UPROPERTY(EditAnywhere)
	float Health{1.0f};
	/// Past Damage Events
	UPROPERTY(VisibleAnywhere)
	TArray<FPlayerDamageEvent> PastDamageEvents;

	/////// Movement Input ///////
	/// Move Forward/Back
	void MoveForward(float Val);
	/// Move Right/Left
	void MoveRight(float Val);

	/////// Mouse Input ///////
	/// Look Left/Right
	void TurnAtRate(float Rate);
	/// Look Up/Down
	void LookUpAtRate(float Rate);

	/////// Stats Functions ///////
	/// Take Damage
	UFUNCTION(BlueprintCallable)
	void PlayerTakeDamage(float damageAmount, APlayerController* eventInstigator, AActor* damageDealer, TEnumAsByte<EDamageSources> damageSource, TEnumAsByte<EDamageType> damageType);
	/// Kill Player
	UFUNCTION(BlueprintCallable)
	void KillPlayer(float respawnTime, TArray<FPlayerDamageEvent> damageEvents, bool shouldRespawn);
	/// Get Player Health
	UFUNCTION(BlueprintPure)
	float GetHealth() const { return Health; }
	/// Set Player Health
	UFUNCTION(BlueprintCallable)
	void SetHealth(const float val) { Health = val; }

	UFUNCTION(BlueprintPure)
	UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	UFUNCTION(BlueprintCallable)
	void SetPlayingNow(const bool val) { PlayingNow = val; }
	UFUNCTION(BlueprintPure)
	bool GetPlayingNow() const { return PlayingNow; }

	UFUNCTION(BlueprintCallable)
	void StartShooting();
	UFUNCTION(BlueprintCallable)
	void StopShooting();
	UFUNCTION(BlueprintCallable)
	void ReloadWeapon();
	
	UFUNCTION(BlueprintCallable)
	void UseAbility1();
	UFUNCTION(BlueprintCallable)
	void UseAbility2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayingNow{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* FireEffect;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Returns Character Mesh 1P
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMeshCharacter1P() const { return MeshCharacter1P; }

	// Returns Weapon Mesh 1P
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMeshWeapon1P() const { return MeshWeapon1P; }

	// Returns Weapon Audio Component
	UFUNCTION(BlueprintCallable)
	UAudioComponent* GetWeaponAudioComponent() const { return WeaponAudioComponent; }

	// Returns Ability Component
	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent() const { return AbilityComponent; }

	// Returns Niagara Component
	UFUNCTION(BlueprintCallable)
	UNiagaraComponent* GetNiagaraComponent() const { return NiagaraComponent; }

	// Returns Niagara System
	UFUNCTION(BlueprintCallable)
	UNiagaraSystem* GetNiagaraFireSystem() const { return FireEffect; }

	// Returns Camera
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};
