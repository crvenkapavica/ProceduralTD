#include "ParticleBaseClass.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


UParticleBaseClass::UParticleBaseClass()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UParticleBaseClass::BeginPlay() {

	Super::BeginPlay();
}


void UParticleBaseClass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Particle->AttachTo(this, FName(NAME_None), EAttachLocation::SnapToTarget, false);
