#include "Riki.h"

ARiki::ARiki()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARiki::BeginPlay() {

	Super::BeginPlay();
}

void ARiki::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void ARiki::ApplyDamage(int Damage, FString Type) {

	Super::ApplyDamage(Damage, Type);
}

