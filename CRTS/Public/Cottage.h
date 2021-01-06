#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cottage.generated.h"

UCLASS()
class CRTS_API ACottage : public AActor
{
	GENERATED_BODY()
	
public:	

	ACottage();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
