// Fill out your copyright notice in the Description page of Project Settings.


#include "GridModifier.h"


// Sets default values
AGridModifier::AGridModifier()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;
	// Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	// SetRootComponent(Root);
	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	// if (TileType == ETileType::Normal)
	// {
	// 	Mesh->SetVectorParameterValueOnMaterials(FName("Color"), FVector(1.0,1.0,1.0));
	// }else if (TileType == ETileType::Obstacle)
	// {
	// 	Mesh->SetVectorParameterValueOnMaterials(FName("Color"), FVector(1.0,0.0,0.0));
	// }
	// Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	// SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void AGridModifier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

