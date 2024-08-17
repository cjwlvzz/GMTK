// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainPawn.generated.h"

UCLASS()
class DICEGAME_API AMainPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	void OnMouseWheelAxis(float AxisValue);

	void OnInputAxis_Forward(float AxisValue);

	void OnInputAxis_Right(float AxisValue);

	void OnInputAction_RotationRight();

	void OnInputAction_RotationLeft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Zoom_Desired = 700.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location_Desired = FVector(0.0f, 0.0f, 100.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Rotation_Desired = FRotator(0.0f, 0.0f, 0.0f);
	
};
