#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CRTSGameMode.generated.h"


UCLASS(minimalapi)
class ACRTSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACRTSGameMode();
	~ACRTSGameMode();
};