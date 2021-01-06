#pragma once

#include "CoreMinimal.h"
#include "MonsterBaseClass.h"
#include "GameFramework/Character.h"
#include "Ogre.generated.h"


UCLASS(Blueprintable)
class CRTS_API AOgre : public AMonsterBaseClass
{
	GENERATED_BODY()

public:
	AOgre();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyDamage(int Damage, FString Type) override;
};
