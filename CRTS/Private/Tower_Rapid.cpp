#include "Tower_Rapid.h"
#include "AimBot.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "ProjectileBaseClass.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

ATower_Rapid::ATower_Rapid() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATower_Rapid::BeginPlay() {

	Damage = 15;
	Range = 75.f;
	AttackSpeed = 850.f;
	ProjectileSpeed = 622;
	Projectile = ProjectileCannon_BP;
	DamageType = "cannon";
	RadiusColor = FColor(0.f, 255.f, 0.f);
	Cost = 65;

	GetComponents<UStaticMeshComponent>(Components);

	Super::BeginPlay();
}

void ATower_Rapid::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);

	if (EnemyFirst) {
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EnemyFirst->GetActorLocation());
		FRotator Rotation{ 0.f, LookAtRotation.Yaw - 90.f, 0.f };
		Components[0]->SetWorldRotation(FQuat(Rotation), false, nullptr, ETeleportType::None);
	}
}
