
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TileState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETileState : uint8 {
	None,
	Hovered,
	Selected
};
