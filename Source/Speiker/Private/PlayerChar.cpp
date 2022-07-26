// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerChar::APlayerChar()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create the first person mesh
	MeshCharacter1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	MeshCharacter1P->SetOnlyOwnerSee(true);
	MeshCharacter1P->SetupAttachment(FirstPersonCameraComponent);
	MeshCharacter1P->bCastDynamicShadow = true;
	MeshCharacter1P->CastShadow = true;
	MeshCharacter1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	MeshCharacter1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create the weapon mesh
	MeshWeapon1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	MeshWeapon1P->SetOnlyOwnerSee(true);
	MeshWeapon1P->bCastDynamicShadow = true;
	MeshWeapon1P->CastShadow = true;

	// Construct Weapon Stats
	FWeaponDamages* partDamages = new FWeaponDamages(0.15f, 0.10f, 0.08f, 0.2f);
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon Component"));
	WeaponComponent->InitializeWeapon(*partDamages, 20.0f, 20.0f, true, 1.0f, 20.0f, 2.0f, 0.2f, true);

	WeaponAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Weapon Audio"));
	WeaponAudioComponent->bAutoActivate = false;
	WeaponAudioComponent->bCanPlayMultipleInstances = true;
	WeaponAudioComponent->AttenuationSettings = WeaponComponent->WeaponAudioAttenuation;
	WeaponAudioComponent->bAutoManageAttachment = false;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Attach weapon to hand
	MeshWeapon1P->AttachToComponent(MeshCharacter1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	MeshWeapon1P->SetRelativeLocation(FVector(-2.267020,-0.939935,-0.985463));
	MeshWeapon1P->SetRelativeRotation(FRotator(-0.000306,-9.106652,9.448061));
	MeshCharacter1P->SetRelativeLocation(FVector(10.836175,-11.747597,-151.969738));
	MeshCharacter1P->SetRelativeRotation(FRotator(9.835799,-0.328397,3.213572));
	WeaponAudioComponent->AttachToComponent(MeshWeapon1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	WeaponAudioComponent->SetRelativeLocation(FVector(0.0f, 15.0f, 0.0f));
	if (WeaponAudioComponent->IsValidLowLevelFast()) {
		WeaponAudioComponent->SetSound(WeaponComponent->WeaponAudio);
		WeaponAudioComponent->AttenuationSettings = WeaponComponent->WeaponAudioAttenuation;
	}
	// Halt execution if GEngine is nullptr
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

	// Fix motion blur
	FirstPersonCameraComponent->PostProcessSettings.bOverride_MotionBlurAmount = true;
	FirstPersonCameraComponent->PostProcessSettings.MotionBlurAmount = 0;
	FirstPersonCameraComponent->PostProcessSettings.MotionBlurMax = 0;
	FirstPersonCameraComponent->SetFieldOfView(103.0f);
	// APlayerController* controller = static_cast<APlayerController*>(GetController());
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Weapon Input
	//PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AFirstPersonCharacter::OnPrimaryAction);

	// Movement Input
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerChar::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerChar::MoveRight);

	// Jump Input
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Mouse Input
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APlayerChar::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APlayerChar::LookUpAtRate);

	// Weapon Input
	PlayerInputComponent->BindAction("Fire Weapon", IE_Pressed, this, &APlayerChar::StartShooting);
	PlayerInputComponent->BindAction("Fire Weapon", IE_Released, this, &APlayerChar::StopShooting);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerChar::ReloadWeapon);
}

void APlayerChar::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerChar::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerChar::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * Sensitivity);
}

void APlayerChar::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * Sensitivity);
}

void APlayerChar::PlayerTakeDamage(float damageAmount, APlayerController* eventInstigator, AActor* damageDealer, TEnumAsByte<EDamageSources> damageSource, TEnumAsByte<EDamageType> damageType)
{
	if (Health > 0.0f)
	{
		Health -= damageAmount;
	}
	if (Health < 0.0f)
	{
		Health = 0.0f;
	}

	FPlayerDamageEvent* damageEvent = new FPlayerDamageEvent(damageAmount, eventInstigator, damageDealer, damageSource, damageType, Health);
	PastDamageEvents.Add(*damageEvent);

	if (Health == 0.0f)
	{
		this->KillPlayer(0.0f, PastDamageEvents, true);
	}
}

void APlayerChar::KillPlayer(float respawnTime, TArray<FPlayerDamageEvent> damageEvents, bool shouldRespawn)
{
	WeaponComponent->FinishReload();
	WeaponComponent->EndShootInput();
}

void APlayerChar::StartShooting()
{
	WeaponComponent->StartShootInput();
}

void APlayerChar::ReloadWeapon()
{
	WeaponComponent->IsReloading = true;
	WeaponComponent->BeginReload();
}

void APlayerChar::StopShooting()
{
	WeaponComponent->EndShootInput();
}

