#include "Grid.h"
#include "GridModifier.h"
#include "GridVisual.h"
#include "IAutomationControllerManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// Enum To String
// Usage Example:
//		FString EnumString = EnumToString( EnumValue );
//////////////////////////////////////////////////////////////////////////
template <typename T>
FString EnumToString(T EnumValue)
{
	static_assert(TIsUEnumClass<T>::Value, "'T' template parameter to EnumToString must be a valid UEnum");
	return StaticEnum<T>()->GetNameStringByValue((int64)EnumValue);
}

FGridShapeData AGrid::GetCurrentGridShapeData()
{
	if (IsValid(GridShapeDataTable))
	{
		return *GridShapeDataTable->FindRow<FGridShapeData>(FName(*EnumToString(GridShapeType)), TEXT("Lookup failed"));
	}
	else
	{
		return FGridShapeData();
	}
}

void AGrid::CalculateCenterAndBottomLeft(FVector& Center, FVector& BottomLeft)
{
	Center = UUtilities::SnapVectorToVectorGrid(GridCenterLocation, GridTileSize);

	float temp1 = FMath::FloatSelect(UUtilities::ISIntEven(GridTileCount.X), 0.0f, 1.0f);

	float temp2 = FMath::FloatSelect(UUtilities::ISIntEven(GridTileCount.Y), 0.0f, 1.0f);

	UE::Math::TIntPoint<uint32> tempGridTileCount = UE::Math::TIntPoint<uint32>(
		GridTileCount.X - temp1, GridTileCount.Y - temp2);

	tempGridTileCount = UE::Math::TIntPoint<uint32>(tempGridTileCount.X / 2, tempGridTileCount.Y / 2);

	FVector temp = FVector(tempGridTileCount.X * GridTileSize.X, tempGridTileCount.Y * GridTileSize.Y, 0.0f);

	BottomLeft = Center - temp;
}

FRotator AGrid::GetTileRotationFromGridIndex(FIntPoint index)
{
	if (GridShapeType == EGridShape::Triangle)
	{
		return FRotator(
			0.0f, FMath::FloatSelect(UUtilities::ISFloatEven(index.X), 180.0f, 0.0f) +
			FMath::FloatSelect(UUtilities::ISFloatEven(index.Y), 180.0f, 0.0f),
			FMath::FloatSelect(UUtilities::ISFloatEven(index.Y), 180.0f, 0.0f));
	}
	else
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
}

FVector AGrid::GetTileLocationFromGridIndex(FIntPoint index)
{
	FVector GridTileSize2D = FVector(index.X * GridTileSize.X, index.Y * GridTileSize.Y, 0.0f);
	return GridTileSize2D + GridLeftBottomCornerLocation;
}


FTraceResult AGrid::TraceForGround(FVector Location)
{
	FTraceResult result;

	float radius = GridTileSize.X / 3.0f;

	ETileType retType = ETileType::Normal;

	FCollisionShape SphereCollision = FCollisionShape::MakeSphere(radius);

	TArray<FHitResult> OutResults;

	FVector Start = Location + FVector(0.0f, 0.0f, 1000.0f);

	FVector End = Location - FVector(0.0f, 0.0f, 1000.0f);

	float retZ = 0.0f;


	GetWorld()->SweepMultiByChannel(OutResults, Start, End, FQuat::Identity, ECC_GameTraceChannel1, SphereCollision);

	if (OutResults.Num() <= 0)
	{
		result.bHit = false;
		result.HitLocation = Location;
		result.TileType = retType;
	}
	else
	{
		result.bHit = true;
		for (int32 i = 0; i < OutResults.Num(); i++)
		{
			// retType = Cast<AGridModifier>(OutResults[i].GetActor())->TileType;
			// result.TileType = retType;
			if (Cast<AGridModifier>(OutResults[i].GetActor()))
			{
				retType = Cast<AGridModifier>(OutResults[i].GetActor())->TileType;
				result.TileType = retType;
			}
			retZ = FMath::GridSnap(OutResults[i].Location.Z - radius, GridTileSize.Z);
		}
		result.HitLocation = FVector(Location.X, Location.Y, retZ);
	}
	return result;
}

FVector AGrid::GetCursorLocationOnGrid(int PlayerIndex)
{
	FHitResult HitResult;
	auto const PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex);
	if (PlayerController->GetHitResultUnderCursorByChannel((UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2)),
	                                                       false, HitResult))
	{
		return HitResult.Location;
	}
	else
	{
		FVector MouseLocation(0.0f), MouseDirection(0.0f);
		PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
		FVector Start = MouseLocation;
		FVector End = MouseLocation + MouseDirection * 999999.0f;
		float T = 0.0f;
		FVector Intersection = FVector::ZeroVector;
		FPlane Plane = MakePlaneFromPointAndNormal(GridCenterLocation, FVector(0.0f, 0.0f, 1.0f));
		if (LinePlaneIntersection(Start, End, Plane, T, Intersection))
		{
			return Intersection;
		}
		else
		{
			return FVector(-999.0f);
		}
	}
}

FPlane AGrid::MakePlaneFromPointAndNormal(FVector Point, FVector Normal)
{
	return FPlane(Point, Normal.GetSafeNormal());
}

bool AGrid::LinePlaneIntersection(const FVector& LineStart, const FVector& LineEnd, const FPlane& APlane, float& T,
                                  FVector& Intersection)
{
	{
		FVector RayDir = LineEnd - LineStart;

		// Check ray is not parallel to plane
		if ((RayDir | APlane) == 0.0f)
		{
			T = -1.0f;
			Intersection = FVector::ZeroVector;
			return false;
		}

		T = ((APlane.W - (LineStart | APlane)) / (RayDir | APlane));

		// Check intersection is not outside line segment
		if (T < 0.0f || T > 1.0f)
		{
			Intersection = FVector::ZeroVector;
			return false;
		}

		// Calculate intersection point
		Intersection = LineStart + RayDir * T;

		return true;
	}
}

void AGrid::AddGridTile(FTileData tileData)
{
	GridTiles.Add(tileData.TileIndex, tileData);
	GridVisual->UpdateTileVisual(tileData);
}

FIntPoint AGrid::GetGridIndexFromWorldLocation(FVector Location)
{
	FVector LocationOnGrid = Location - GridLeftBottomCornerLocation;
	FVector2d SnappedLocationOnGrid = FVector2d(UUtilities::SnapVectorToVectorGrid(LocationOnGrid, GridTileSize));
	return FIntPoint((SnappedLocationOnGrid / FVector2d(GridTileSize)).X,
	                 (SnappedLocationOnGrid / FVector2d(GridTileSize)).Y);
}

void AGrid::AddStateToTile(FIntPoint TileIndex, ETileState TileState)
{
	FTileData data;
	if (GridTiles.Find(TileIndex) != nullptr)
	{
		data = *GridTiles.Find(TileIndex);
		if(data.TileStates.AddUnique(TileState) >= 0)
		{
			GridTiles.Add(data.TileIndex, data);
			GridVisual->UpdateTileVisual(data);
		}
	}
}

void AGrid::RemoveStateFromTile(FIntPoint TileIndex, ETileState TileState)
{
	FTileData data;
	if (GridTiles.Find(TileIndex) != nullptr)
	{
		data = *GridTiles.Find(TileIndex);
		if(data.TileStates.Remove(TileState) >= 0)
		{
			GridTiles.Add(data.TileIndex, data);
			GridVisual->UpdateTileVisual(data);
		}
	}
}

FIntPoint AGrid::GetTileIndexUnderCursor(int PlayerIndex)
{
	auto location = GetCursorLocationOnGrid(PlayerIndex);
	auto index = GetGridIndexFromWorldLocation(location);
	return index;
}

void AGrid::DestroyGrid()
{
	GridTiles.Empty();
	GridVisual->DestroyGridVisual();
}

void AGrid::SpawnGrids()
{
	DestroyGrid();
	GridVisual->InitializeGridVisual(this);
	GridCenterLocation = GetActorLocation();
	CalculateCenterAndBottomLeft(GridCenterLocation, GridLeftBottomCornerLocation);
	for (int32 x = 0; x < GridTileCount.X - 1; x++)
	{
		for (int32 y = 0; y < GridTileCount.Y - 1; y++)
		{
			FIntPoint index = FIntPoint(x, y);
			FVector TileTransformLocation = GridLeftBottomCornerLocation + FVector(
				x * GridTileSize.X, y * GridTileSize.Y, 3.0f);
			FRotator TileTransformRotation = GetTileRotationFromGridIndex(index);
			FVector TileTransformScale = GridTileSize / GetCurrentGridShapeData().MeshSize;
			FTraceResult traceResult = TraceForGround(TileTransformLocation);
			FTransform TileTransform = FTransform(TileTransformRotation, traceResult.HitLocation, TileTransformScale);
			AddGridTile(FTileData(index, traceResult.TileType, TileTransform));
		}
	}
}

bool AGrid::IsIndexValid(FIntPoint Index)
{
	return GridTiles.Contains(Index);
}

FVector AGrid::GetTileScale()
{
	return 	GridTileSize / GetCurrentGridShapeData().MeshSize;
}

// Sets default values
AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(Root);
	GridShapeDataTable = LoadObject<UDataTable>(NULL, *TableLoadPath);
	ChildActor_GridVisual = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridMeshInst"));
	ChildActor_GridVisual->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ChildActor_GridVisual->SetChildActorClass(AGridVisual::StaticClass());
}


// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	if (Cast<AGridVisual>(ChildActor_GridVisual->GetChildActor()))
	{
		GridVisual = Cast<AGridVisual>(ChildActor_GridVisual->GetChildActor());
	}
	if (IsValid(GridVisual))
	{
		SpawnGrids();
	}
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
