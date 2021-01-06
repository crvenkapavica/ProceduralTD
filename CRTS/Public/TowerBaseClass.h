#pragma once

#include "CoreMinimal.h"
#include "MonsterBaseClass.h"
#include "GameFramework/Actor.h"
#include "TowerBaseClass.generated.h"

UCLASS()
class CRTS_API ATowerBaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	ATowerBaseClass();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UAimBot* AimBot;
	
	UPROPERTY()
	int Damage;
	UPROPERTY()
	float Range;
	UPROPERTY()
	float Radius;
	UPROPERTY()
	float AttackSpeed;
	UPROPERTY()
	float ProjectileSpeed;
	UPROPERTY()
	int Cost;
	UPROPERTY()
	FString DamageType;

	UPROPERTY()
	TSubclassOf<class AProjectileBaseClass> Projectile;
	UPROPERTY()
	AMonsterBaseClass* EnemyFirst;
	UPROPERTY()
	AMonsterBaseClass* StrongestEnemy;
	UPROPERTY()
	TArray<AMonsterBaseClass*> EnemiesInRange;
	UPROPERTY()
	FColor RadiusColor;
};
