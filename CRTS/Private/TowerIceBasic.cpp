#include "TowerIceBasic.h"
#include "AimBot.h"
#include "DrawDebugHelpers.h"

ATowerIceBasic::ATowerIceBasic()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerIceBasic::BeginPlay() {

	Damage = 18;
	Range = 38.f;
	AttackSpeed = 125.f;
	ProjectileSpeed = 395;
	Projectile = ProjectileCannon_BP;
	DamageType = "ice";
	RadiusColor = FColor(0.f, 0.f, 255.f);
	Cost = 120;

	Super::BeginPlay();
}

void ATowerIceBasic::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}
