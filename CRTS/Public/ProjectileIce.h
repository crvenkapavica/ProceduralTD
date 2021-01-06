#pragma once

#include "CoreMinimal.h"
#include "ProjectileBaseClass.h"
#include "GameFramework/Actor.h"
#include "ProjectileIce.generated.h"

UCLASS()
class CRTS_API AProjectileIce : public AProjectileBaseClass
{
	GENERATED_BODY()
	
public:	
	AProjectileIce();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyDamage(int InDamage, FString InDamageType) override;
	
	UPROPERTY()
	float SlowRange;
};
