#include "TowerActor.h"

ATowerActor::ATowerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATowerActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
