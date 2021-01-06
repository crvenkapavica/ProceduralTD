#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParticleBaseClass.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRTS_API UParticleBaseClass : public UActorComponent
{
	GENERATED_BODY()

public:	
	UParticleBaseClass();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	class UParticleSystemComponent* Emitter;

	UPROPERTY()
	class UParticleSystem* Particle ;
	
};
