#pragma once

#include "CoreMinimal.h"
#include "Data/GridShapeData.h"
#include "Data/TileType.h"
#include "Data/TileData.h"
#include "GameFramework/Actor.h"
#include "DiceGame/Public/Utils/Utilities.h"
#include "Grid.generated.h"
// Forward Declaration
class AGridVisual;
UCLASS()
class DICEGAME_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrid();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FGridShapeData GetCurrentGridShapeData();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	void CalculateCenterAndBottomLeft(FVector& Center, FVector& BottomLeft);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FRotator GetTileRotationFromGridIndex(FIntPoint index);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FVector GetTileLocationFromGridIndex(FIntPoint index);
	FTraceResult TraceForGround(FVector Location);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FVector GetCursorLocationOnGrid(int PlayerIndex);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FPlane MakePlaneFromPointAndNormal(FVector Point, FVector Normal);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool LinePlaneIntersection(const FVector& LineStart, const FVector& LineEnd, const FPlane& APlane, float& T, FVector& Intersection);
	UFUNCTION(BlueprintCallable)
	void AddGridTile(FTileData tileData);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FIntPoint GetGridIndexFromWorldLocation(FVector Location);
	
	UFUNCTION(BlueprintCallable)
	void AddStateToTile(FIntPoint TileIndex, ETileState TileState);
	
	UFUNCTION(BlueprintCallable)
	void RemoveStateFromTile(FIntPoint TileIndex, ETileState TileState);
	UFUNCTION(BlueprintCallable)
	FIntPoint GetTileIndexUnderCursor(int PlayerIndex);
	void DestroyGrid();
	UFUNCTION(BlueprintCallable)
	void SpawnGrids();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsIndexValid(FIntPoint Index);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	FVector GetTileScale();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGridShape GridShape = EGridShape::Square;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UChildActorComponent* ChildActor_GridVisual;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector GridCenterLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector GridTileSize = FVector(200.0f, 200.0f, 100.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint GridTileCount =  FIntPoint(10, 10);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGridShape GridShapeType = EGridShape::Square;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector GridLeftBottomCornerLocation = FVector(0.0f, 0.0f, 0.0f);

	FString TableLoadPath = FString(TEXT("/Game/Core/Data/DT_ShapeData.DT_ShapeData"));
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* GridShapeDataTable = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GridOffsetFromGround = 3.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AGridVisual* GridVisual;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FIntPoint,FTileData> GridTiles;
	
};

USTRUCT(BlueprintType)
struct FTraceResult
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	bool bHit = false;
	UPROPERTY(BlueprintReadWrite)
	FVector HitLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(BlueprintReadWrite)
	ETileType TileType = ETileType::Normal;
};