// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMeshInst.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Data/TileState.h"


// Sets default values
AGridMeshInst::AGridMeshInst()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GridMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	SetRootComponent(GridMesh);
	GridMesh->NumCustomDataFloats = 4;
}

void AGridMeshInst::AddInstance(FTransform Transform, FIntPoint TileIndex, TArray<ETileState> States)
{
	RemoveInstance(TileIndex);
	GridMesh->AddInstance(Transform,true);
	auto tempIdx =  GridTileIndices.Add(TileIndex);
	FLinearColor Color = GetColorFromTileState(States);
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("Color: %f, %f, %f"), Color.R, Color.G, Color.B));
	GridMesh->SetCustomDataValue(tempIdx, 0, Color.R);
	GridMesh->SetCustomDataValue(tempIdx, 1, Color.G);
	GridMesh->SetCustomDataValue(tempIdx, 2, Color.B);

	if(Color == FLinearColor(0.0f,0.0f,0.0f))
	{
		GridMesh->SetCustomDataValue(tempIdx,3,0.0);
	}
	else
	{
		GridMesh->SetCustomDataValue(tempIdx,3,1.0);
	}
	
}

void AGridMeshInst::RemoveInstance(FIntPoint TileIndex)
{
	GridMesh->RemoveInstance(GridTileIndices.Find(TileIndex));
	GridTileIndices.Remove(TileIndex);
}

void AGridMeshInst::ClearInstance()
{
	GridMesh->ClearInstances();
	GridTileIndices.Empty();
}

void AGridMeshInst::InitializeGridMeshInst(UStaticMesh* Mesh, UMaterialInterface* Material, FLinearColor Color, ECollisionEnabled::Type CollisionEnabled)
{
	GridMesh->SetStaticMesh(Mesh);
	GridMesh->SetMaterial(0, Material);
	GridMesh->SetVectorParameterValueOnMaterials(FName("Color"), FVector(Color.R, Color.G, Color.B));
	GridMesh->SetCollisionEnabled(CollisionEnabled);
}

FLinearColor AGridMeshInst::GetColorFromTileState(TArray<ETileState> States)
{

	TArray<ETileState> tempArray = {ETileState::Selected,ETileState::Hovered};
	
	if (States.Num() == 0)
	{
		return FLinearColor(0.0, 0.0, 0.0);
	}
	else
	{
		for (int i = 0; i < tempArray.Num(); i++)
		{
			if (States.Contains(tempArray[i]))
			{
				if (tempArray[i] == ETileState::Selected)
				{
					return FLinearColor(0.74, 0.28, 0.06);
				}
				else if (tempArray[i] == ETileState::Hovered)
				{
					return FLinearColor(0.80, 0.54, 0.15);
				}
			}
		}
		return FLinearColor(0.0, 0.0, 0.0);
	}
}

// Called when the game starts or when spawned
void AGridMeshInst::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

// Called every frame
void AGridMeshInst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

