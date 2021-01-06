#pragma once

#include "CoreMinimal.h"
#include "TowerBaseClass.h"
#include "ProjectileBaseClass.h"
#include "GameFramework/Actor.h"
#include "TowerIceBasic.generated.h"

UCLASS()
class CRTS_API ATowerIceBasic : public ATowerBaseClass
{
	GENERATED_BODY()
	
public:	
	ATowerIceBasic();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectileBaseClass> ProjectileCannon_BP;
};
