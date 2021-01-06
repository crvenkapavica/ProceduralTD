#include "UI.h"
#include "Blueprint/UserWidget.h"

AUI::AUI()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUI::BeginPlay() {

	Super::BeginPlay();
}

void AUI::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}
