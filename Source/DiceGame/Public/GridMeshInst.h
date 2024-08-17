// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridMeshInst.generated.h"

enum class ETileState : uint8;

UCLASS()
class DICEGAME_API AGridMeshInst : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridMeshInst();
	void AddInstance(FTransform Transform, FIntPoint TileIndex,TArray<ETileState> States);
	void RemoveInstance(FIntPoint TileIndex);
	void ClearInstance();
	void InitializeGridMeshInst(UStaticMesh* Mesh, UMaterialInterface* Material,FLinearColor Color,ECollisionEnabled::Type CollisionEnabled);
	FLinearColor GetColorFromTileState(TArray<ETileState> States);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInstancedStaticMeshComponent* GridMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FIntPoint> GridTileIndices;
};
