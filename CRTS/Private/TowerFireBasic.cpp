#include "TowerFireBasic.h"
#include "AimBot.h"
#include "DrawDebugHelpers.h"

ATowerFireBasic::ATowerFireBasic()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerFireBasic::BeginPlay() {

	Damage = 45;
	Range = 52.f;
	AttackSpeed = 585.f;
	ProjectileSpeed = 485;
	Projectile = ProjectileCannon_BP;
	DamageType = "fire";
	RadiusColor = FColor(255.f, 0.f, 0.f);
	Cost = 200;

	Super::BeginPlay();
}

void ATowerFireBasic::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

