#include "ProjectileCannon.h"

AProjectileCannon::AProjectileCannon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileCannon::BeginPlay() {

	Super::BeginPlay();
}

void AProjectileCannon::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

