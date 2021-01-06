#pragma once

#include "CoreMinimal.h"
#include "ProjectileBaseClass.h"
#include "GameFramework/Actor.h"
#include "ProjectileFire.generated.h"

UCLASS()
class CRTS_API AProjectileFire : public AProjectileBaseClass
{
	GENERATED_BODY()
	
public:	

	AProjectileFire();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
