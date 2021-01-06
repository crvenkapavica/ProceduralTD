#pragma once

#include "CoreMinimal.h"
#include "MonsterBaseClass.h"
#include "GameFramework/Character.h"
#include "Riki.generated.h"

UCLASS()
class CRTS_API ARiki : public AMonsterBaseClass
{
	GENERATED_BODY()

public:

	ARiki();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void ApplyDamage(int Damage, FString Type) override;
};
