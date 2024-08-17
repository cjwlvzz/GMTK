#pragma once

#include "CoreMinimal.h"
#include "GridMeshInst.h"
#include "Data/TileType.h"
#include "Data/GridShapeData.h"
#include "Data/TileData.h"
#include "GameFramework/Actor.h"
#include "GridVisual.generated.h"

// Forward Declaration
class AGrid;

UCLASS()
class DICEGAME_API AGridVisual : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridVisual();
	
	void InitializeGridVisual(AGrid* Grid);
	void SetOffsetFromGround(float Offset);
	void DestroyGridVisual();
	void UpdateTileVisual(FTileData TileData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UChildActorComponent* ChildActor_GridMeshInst;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AGrid* MyGrid = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AGridMeshInst* GridMeshInst = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float OffsetFromGround = 2.0f;
};


