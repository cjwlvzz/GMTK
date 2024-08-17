// Fill out your copyright notice in the Description page of Project Settings.


#include "DiceGame/Public/Utils/Utilities.h"

#include "Data/TileType.h"

FVector UUtilities::SnapVectorToVectorGrid(FVector V1, FVector V2)
{
	
	return FVector(FMath::GridSnap(V1.X, V2.X), FMath::GridSnap(V1.Y, V2.Y), FMath::GridSnap(V1.Z, V2.Z));
}

bool UUtilities::ISFloatEven(float Value)
{
	return fmod(Value, 2) == 0;
}

bool UUtilities::ISIntEven(int Value)
{
	return Value % 2 == 0;
}

bool UUtilities::IsTileTypeWalkable(ETileType TileType)
{
	if (TileType == ETileType::Normal)
	{
		return true;
	}
	else
	{
		return false;
	}
}
