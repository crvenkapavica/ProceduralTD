#include "Cottage.h"

ACottage::ACottage()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACottage::BeginPlay() {

	Super::BeginPlay();
}

void ACottage::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

