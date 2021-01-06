#include "ProjectileIce.h"
#include "EngineUtils.h"
#include "MonsterBaseClass.h"

AProjectileIce::AProjectileIce()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileIce::BeginPlay() {

	Super::BeginPlay();

	SlowRange = 128.f;
}

void AProjectileIce::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AProjectileIce::ApplyDamage(int Damage, FString DamageType) {

	Super::ApplyDamage(Damage, DamageType);

	for (TActorIterator<AMonsterBaseClass> Iter(GetWorld()); Iter; ++Iter) {
		AMonsterBaseClass* CurrEnemy = *Iter;
		if (FVector::Dist(CurrEnemy->GetActorLocation(), Target->GetActorLocation()) <= SlowRange) {
			CurrEnemy->ApplyIce();
		}
	}
}
