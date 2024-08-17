// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "GameFramework/Actor.h"
#include "PlayerAction.generated.h"

UCLASS()
class DICEGAME_API APlayerAction : public AActor
{	
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerAction();
	UFUNCTION(BlueprintCallable)
	void UpdateTileUnderCursor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint HoveredTile = FIntPoint(-1, -1);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint SelectedTile = FIntPoint(-1, -1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AGrid* Grid = nullptr;
	
};
