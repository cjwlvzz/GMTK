#pragma once
#include "TileState.h"
#include "Data/TileType.h"
#include "VisualLogger/VisualLoggerTypes.h"
#include "TileData.generated.h"
USTRUCT(BlueprintType)
struct FTileData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FIntPoint TileIndex = FIntPoint(0, 0);
	UPROPERTY(BlueprintReadWrite)
	ETileType TileType = ETileType::Normal;
	UPROPERTY(BlueprintReadWrite)
	FTransform TileTransform = FTransform();
	UPROPERTY(BlueprintReadWrite)
	TArray<ETileState> TileStates;
	//default constructor
	FTileData()
	{
	}
	
	// Constructor for FTileData
	FTileData(FIntPoint index, ETileType type, FTransform transform)
	{
		TileIndex = index;
		TileType = type;
		TileTransform = transform;
	}
};