#include "ProjectileBaseClass.h"

AProjectileBaseClass::AProjectileBaseClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileBaseClass::BeginPlay() {

	Super::BeginPlay();	
}

void AProjectileBaseClass::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (Target) {

		FVector location = GetActorLocation();
		location = FMath::VInterpConstantTo(location, Target->GetActorLocation(), DeltaTime, Speed);
		SetActorLocation(location);

		if (FMath::Abs(location.X - Target->GetActorLocation().X) < 2.f &&
			FMath::Abs(location.Y - Target->GetActorLocation().Y) < 2.f) {
			TargetHit();
		}
	}
}

void AProjectileBaseClass::TargetHit() {

	Destroy();
	ApplyDamage(Damage, DamageType);
}

void AProjectileBaseClass::ApplyDamage(int Damage, FString DamageType) {

	Target->ApplyDamage(Damage, DamageType);
}