// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/PlayerAction.h"

#include "Grid.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerAction::APlayerAction()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//get player controller
}

void APlayerAction::UpdateTileUnderCursor()
{
	if (HoveredTile != Grid->GetTileIndexUnderCursor(0))
	{
		Grid->RemoveStateFromTile(HoveredTile, ETileState::Hovered);
		HoveredTile = Grid->GetTileIndexUnderCursor(0);
		Grid->AddStateToTile(HoveredTile, ETileState::Hovered);
	}
}

// Called when the game starts or when spawned
void APlayerAction::BeginPlay()
{
	Super::BeginPlay();
	if (AGrid* FoundGrid = Cast<AGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), AGrid::StaticClass())))
	{
		Grid = FoundGrid;
	}
	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Controller Found"));
		playerController->EnableInput(playerController);
	}
	
}


// Called every frame
void APlayerAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTileUnderCursor();
	
	
}


