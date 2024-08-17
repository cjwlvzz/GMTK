// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
}