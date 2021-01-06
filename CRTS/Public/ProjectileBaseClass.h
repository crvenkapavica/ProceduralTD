#pragma once

#include "CoreMinimal.h"
#include "TowerBaseClass.h"
#include "MonsterBaseClass.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "ProjectileBaseClass.generated.h"

UCLASS()
class CRTS_API AProjectileBaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBaseClass();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyDamage(int InDamage, FString InDamageType);

	UPROPERTY()
	AMonsterBaseClass* Target;
	UPROPERTY()
	int Damage;
	UPROPERTY()
	float Speed;
	UPROPERTY()
	FString DamageType;

protected:
	UFUNCTION()
	void TargetHit();
};
