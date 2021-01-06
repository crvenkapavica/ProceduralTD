#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerActor.generated.h"

UCLASS()
class CRTS_API ATowerActor : public AActor
{
	GENERATED_BODY()

public:

	ATowerActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};