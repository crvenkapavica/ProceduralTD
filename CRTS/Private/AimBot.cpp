#include "AimBot.h"
#include "Components/PrimitiveComponent.h"
#include "EngineUtils.h"
#include "UObject/UObjectIterator.h"
#include "Ogre.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "ProjectileCannon.h"

UAimBot::UAimBot() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAimBot::BeginPlay() {

	Super::BeginPlay();
	SpawnTimer = clock();
}

void UAimBot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (World && GetEnemiesInRange()) {
		SpawnProjectile();
	}
}

bool UAimBot::IsInRange(AActor* Enemy) {
	
	return FVector::Dist(Enemy->GetActorLocation(), Owner->GetActorLocation()) < Radius ? true : false;
}

int UAimBot::GetEnemiesInRange() {

	Enemies.Empty();
	for (TActorIterator<AMonsterBaseClass> Iter(World); Iter; ++Iter) {
		AMonsterBaseClass* currMonster = *Iter;
		if (IsInRange(currMonster)) {
			Enemies.Add(currMonster);
		}
	}
	Owner->EnemiesInRange = Enemies;
	Owner->EnemyFirst = Enemies.Num() ? Enemies[0] : NULL;
	return Enemies.Num();
}

void UAimBot::SetRange(UWorld* World, float Range, TSubclassOf<AProjectileBaseClass> Projectile, 
	const FTransform Transform, ATowerBaseClass* Owner) {

	this->Owner = Owner;
	this->World = World;
	this->Range = Range;
	this->Projectile = Projectile;
	this->Transform = Transform;
	Radius = 3.14159 * 2 * Range;

	//adjust projectile position to match the barrel
	FVector TurretPosition = this->Transform.GetLocation();
	TurretPosition.Z += 105.f;
	FTransform UpdatedTransform{ TurretPosition };
	this->Transform.CopyTranslation(UpdatedTransform);
}

void UAimBot::SpawnProjectile() {

	if (GEngine && ((std::clock() - SpawnTimer) / CLOCKS_PER_SEC) > (1000 - Owner->AttackSpeed) / 1000) {
		SpawnedProjectile = World->SpawnActorDeferred<AProjectileBaseClass>(Projectile, Transform);
		SpawnedProjectile->Target = Owner->EnemyFirst;
		SpawnedProjectile->Damage = Owner->Damage;
		SpawnedProjectile->Speed = Owner->ProjectileSpeed;
		SpawnedProjectile->DamageType = Owner->DamageType;
		SpawnedProjectile->FinishSpawning(Transform);
		SpawnTimer = std::clock();
	}
}