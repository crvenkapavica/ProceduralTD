#include "ProjectileFire.h"

AProjectileFire::AProjectileFire()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileFire::BeginPlay() {

	Super::BeginPlay();
}

void AProjectileFire::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}
