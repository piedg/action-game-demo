// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AAGCharacter::AAGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 450.f;
	CameraBoom->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>("ViewCamera");
	ViewCamera->SetupAttachment(CameraBoom);

}

void AAGCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GetMesh()->HideBoneByName(TEXT("weapon"), EPhysBodyOp::PBO_None);
	//GetMesh()->HideBoneByName(TEXT("pistol"), EPhysBodyOp::PBO_None);
}

void AAGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAGCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AAGCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AAGCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AAGCharacter::Aim);
}

void AAGCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		// find out which way is forward
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAGCharacter::MoveRight(float Value)
{
	if (Controller && (Value != 0.f))
	{
		// find out which way is right
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AAGCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AAGCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AAGCharacter::Aim()
{
	UE_LOG(LogTemp, Display, TEXT("Aiming..."));
	IsAiming = true;
}
