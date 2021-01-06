#pragma once

#include "CoreMinimal.h"
#include "ProjectileCannon.h"
#include "TowerBaseClass.h"
#include "GameFramework/Actor.h"
#include "Tower_Rapid.generated.h"

UCLASS()
class CRTS_API ATower_Rapid : public ATowerBaseClass
{
	GENERATED_BODY()
	
public:	
	ATower_Rapid();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectileCannon> ProjectileCannon_BP;

	UPROPERTY()
	UStaticMesh* StaticMeshObject;
	/*UPROPERTY()
	TWeakObjectPtr<UStaticMeshComponent> TopComponent;*/
	UPROPERTY()
	UStaticMeshComponent* TopComponent;

	
	TInlineComponentArray<UStaticMeshComponent*> Components;

};