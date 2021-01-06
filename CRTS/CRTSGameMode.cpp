#include "CRTSGameMode.h"
#include "GenericPlatform/ICursor.h"
#include "krtsPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACRTSGameMode::ACRTSGameMode()
{
	PlayerControllerClass = AkrtsPlayerController::StaticClass();

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

ACRTSGameMode::~ACRTSGameMode()
{
}
