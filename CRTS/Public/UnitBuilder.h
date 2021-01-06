#pragma once

#include "Core.h"
#include "TowerBaseClass.h"
#include "GameFramework/Actor.h"
#include "UnitBuilder.generated.h"

UCLASS(abstract)
class CRTS_API AUnitBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	AUnitBuilder();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true",
		BlueprintInternalUseOnly = "true"))*/
	static void BuildTower(UObject* WorldContextObject, const TSubclassOf<ATowerBaseClass> TowerClass, 
		AActor* Parent);

	/*UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true",
		BlueprintInternalUseOnly = "true"))*/
	static void BuildTower(UObject* WorldContextObject, const TSubclassOf<ATowerBaseClass> TowerClass, 
		AActor* Parent, int Orientation);
};
 