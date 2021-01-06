#pragma once

#include "CoreMinimal.h"
#include "ProjectileBaseClass.h"
#include "TowerBaseClass.h"
#include "GameFramework/Actor.h"
#include "TowerFireBasic.generated.h"

UCLASS()
class CRTS_API ATowerFireBasic : public ATowerBaseClass
{
	GENERATED_BODY()
	
public:	
	ATowerFireBasic();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectileBaseClass> ProjectileCannon_BP;
};
