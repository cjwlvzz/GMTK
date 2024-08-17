// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/TileType.h"

#include "Utilities.generated.h"

/**
 * 
 */
UCLASS()
class DICEGAME_API UUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static FVector SnapVectorToVectorGrid(FVector V1, FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static bool ISFloatEven(float Value);
	static bool ISIntEven(int Value);
	static bool IsTileTypeWalkable(ETileType TileType);
};