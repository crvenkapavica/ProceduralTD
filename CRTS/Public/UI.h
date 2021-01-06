#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "GameFramework/Actor.h"
#include "UI.generated.h"

UCLASS()
class CRTS_API AUI : public AActor
{
	GENERATED_BODY()
	
public:	
	AUI();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
