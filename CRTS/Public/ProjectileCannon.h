#pragma once

#include "CoreMinimal.h"
#include "ProjectileBaseClass.h"
#include "GameFramework/Actor.h"
#include "ProjectileCannon.generated.h"

UCLASS()
class CRTS_API AProjectileCannon : public AProjectileBaseClass
{
	GENERATED_BODY()
	
public:	
	AProjectileCannon();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
