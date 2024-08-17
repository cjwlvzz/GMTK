// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/GridShapeData.h"
#include "GameFramework/Actor.h"
#include "DiceGame/Public/Data//TileType.h"
#include "GridModifier.generated.h"

UCLASS()
class DICEGAME_API AGridModifier : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridModifier();
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// UStaticMeshComponent *Mesh;
	//
	// UPROPERTY(BlueprintReadWrite,EditAnywhere)
	// USceneComponent* Root = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGridShape GridShape = EGridShape::Triangle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ETileType TileType = ETileType::Obstacle;
	
};
