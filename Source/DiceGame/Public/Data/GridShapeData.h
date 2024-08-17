#pragma once
#include "Engine/DataTable.h"
#include "VisualLogger/VisualLoggerTypes.h"
#include "GridShapeData.generated.h"
USTRUCT(BlueprintType)
struct FGridShapeData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector MeshSize = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstance* MeshMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* FlatMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstance* FlatMaterial;
	
};

UENUM(BlueprintType)
enum class EGridShape : uint8 {
	None,
	Square,
	Triangle,
	Hexagon
};
