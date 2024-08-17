// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/MainPawn.h"

// Sets default values
AMainPawn::AMainPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArmComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Location_Desired = GetActorLocation();
	Zoom_Desired = SpringArmComponent->TargetArmLength;
	Rotation_Desired = GetActorRotation();
	Super::BeginPlay();
}

// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, Zoom_Desired, DeltaTime,
	                                                       2.0f);

	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), Location_Desired, DeltaTime, 5.0f);

	SetActorLocation(NewLocation);

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), Rotation_Desired, DeltaTime, 5.0f);

	SetActorRotation(NewRotation);
	
}

void AMainPawn::OnMouseWheelAxis(float AxisValue)
{
	Zoom_Desired = FMath::Clamp(AxisValue * 40.0f + Zoom_Desired, 100.0f, 5000.0f);
}

void AMainPawn::OnInputAxis_Forward(float AxisValue)
{
	Location_Desired = AxisValue * 20.0f * GetActorForwardVector() + Location_Desired;
}

void AMainPawn::OnInputAxis_Right(float AxisValue)
{
	Location_Desired = AxisValue * 20.0f * GetActorRightVector() + Location_Desired;
}

void AMainPawn::OnInputAction_RotationRight()
{
	Rotation_Desired += FRotator(0.0f, 45.0f, 0.0f);
}

void AMainPawn::OnInputAction_RotationLeft()
{
	Rotation_Desired += FRotator(0.0f, -45.0f, 0.0f);
}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// PlayerInputComponent->BindAxis("InputAxis_Zoom", this, &AMainPawn::OnMouseWheelAxis);
	//
	// PlayerInputComponent->BindAxis("InputAxis_Forward", this, &AMainPawn::OnInputAxis_Forward);
	//
	// PlayerInputComponent->BindAxis("InputAxis_Right", this, &AMainPawn::OnInputAxis_Right);
	//
	// PlayerInputComponent->BindAction("InputAction_RotationRight", IE_Pressed, this, &AMainPawn::OnInputAction_RotationRight);
	//
	// PlayerInputComponent->BindAction("InputAction_RotationLeft", IE_Pressed, this, &AMainPawn::OnInputAction_RotationLeft);
	
}
