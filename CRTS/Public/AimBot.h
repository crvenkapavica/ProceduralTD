#pragma once

#include "CoreMinimal.h"
#include <ctime>
#include "ProjectileBaseClass.h"
#include "MonsterBaseClass.h"
#include "TowerBaseClass.h"
#include "Components/ActorComponent.h"
#include "AimBot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRTS_API UAimBot : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAimBot();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetRange(UWorld* World, float Range, TSubclassOf<AProjectileBaseClass> Projectile,
		const FTransform Transform, ATowerBaseClass* Owner);

	UPROPERTY()
	AProjectileBaseClass* SpawnedProjectile;

protected:

	UFUNCTION()
	void SpawnProjectile();
	UFUNCTION()
	bool IsInRange(AActor* Enemy);
	UFUNCTION()
	int GetEnemiesInRange();

	UPROPERTY()
	ATowerBaseClass* Owner;
	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	float Range;
	UPROPERTY()
	float Radius;
	UPROPERTY()
	TSubclassOf<AProjectileBaseClass> Projectile;
	UPROPERTY()
	FTransform Transform;
	UPROPERTY()
	TArray<AMonsterBaseClass*> Enemies;

	UPROPERTY()
	float Bounds_X;
	UPROPERTY()
	float Bounds_Y;

	std::clock_t SpawnTimer;
};
