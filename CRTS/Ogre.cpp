#include "Ogre.h"
#include "eMapGenerator.h"
#include "krtsPlayerController.h"

AOgre::AOgre()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOgre::BeginPlay() {

	Super::BeginPlay();
}

void AOgre::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AOgre::ApplyDamage(int Damage, FString Type) {

	Super::ApplyDamage(Damage, Type);
}