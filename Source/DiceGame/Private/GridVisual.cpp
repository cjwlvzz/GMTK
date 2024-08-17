// Fill out your copyright notice in the Description page of Project Settings.


#include "GridVisual.h"

#include "Grid.h"
#include "GridMeshInst.h"


// Sets default values
AGridVisual::AGridVisual()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(Root);
	ChildActor_GridMeshInst = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridMeshInst"));
	ChildActor_GridMeshInst->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ChildActor_GridMeshInst->SetChildActorClass(AGridMeshInst::StaticClass());
}

void AGridVisual::InitializeGridVisual(AGrid* Grid)
{
	this->MyGrid = Grid;
	if(Cast<AGridMeshInst>(ChildActor_GridMeshInst->GetChildActor()))
	{
		GridMeshInst = Cast<AGridMeshInst>(ChildActor_GridMeshInst->GetChildActor());
	}
	if (IsValid(GridMeshInst) && GridMeshInst != nullptr)
	{
		//TODO: remove the argument from GetCurrentGridShapeData
		auto GridShapeData = MyGrid->GetCurrentGridShapeData();
		GridMeshInst->InitializeGridMeshInst(GridShapeData.FlatMesh, GridShapeData.FlatMaterial, FLinearColor(0.0,0.0,0.0), ECollisionEnabled::QueryOnly);
		SetActorLocation(FVector(0.0f,0.0f,0.0f));
		SetOffsetFromGround(OffsetFromGround);
	}
}

void AGridVisual::SetOffsetFromGround(float Offset)
{
	OffsetFromGround = Offset;
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, OffsetFromGround));
}

void AGridVisual::DestroyGridVisual()
{

	if(IsValid(GridMeshInst))
	{
		GridMeshInst->ClearInstance();
	}
}

void AGridVisual::UpdateTileVisual(FTileData TileData)
{
	GridMeshInst->RemoveInstance(TileData.TileIndex);
	if (UUtilities::IsTileTypeWalkable(TileData.TileType))
	{
		GridMeshInst->AddInstance(TileData.TileTransform, TileData.TileIndex,TileData.TileStates);
	}
}

// Called when the game starts or when spawned
void AGridVisual::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	
}

// Called every frame
void AGridVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

