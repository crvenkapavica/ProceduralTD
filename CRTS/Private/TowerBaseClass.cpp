#include "TowerBaseClass.h"
#include "AimBot.h"
#include "DrawDebugHelpers.h"

ATowerBaseClass::ATowerBaseClass() 
{
	PrimaryActorTick.bCanEverTick = true;
	AimBot = CreateDefaultSubobject<UAimBot>(TEXT("AimBot"));
}

void ATowerBaseClass::BeginPlay() {

	Super::BeginPlay();
	
	AimBot->SetRange(GetWorld(), Range, Projectile, GetTransform(), this);

	Radius = 3.14159 * 2 * Range;
	DrawDebugCircle(GetWorld(), GetActorLocation(), Radius, 250, RadiusColor, true, -1, 0, 3,
		FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f), false);
}

void ATowerBaseClass::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

