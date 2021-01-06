#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FeSpectatorPawn.generated.h"

UCLASS()
class CRTS_API AFeSpectatorPawn : public APawn
{
	GENERATED_BODY()

public:

	AFeSpectatorPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
