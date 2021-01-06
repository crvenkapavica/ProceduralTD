#pragma once

#include "CoreMinimal.h"
#include <ctime>
#include "GameFramework/Pawn.h"
#include "MonsterBaseClass.generated.h"

UCLASS()
class CRTS_API AMonsterBaseClass : public APawn
{
	GENERATED_BODY()

public:
	AMonsterBaseClass();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyDamage(int Damage, FString Type);

	UPROPERTY()
	int Health;
	UPROPERTY()
	float Armor;
	UPROPERTY()
	float MoveSpeed;
	UPROPERTY()
	TArray<FString> Debuffs;

	UPROPERTY(EditAnywhere, Category = "Healthbar")
	TSubclassOf<class UUserWidget> wHealthbarUI;
	UUserWidget* HealthbarUI;
	class UProgressBar* Healthbar;

	UFUNCTION()
	void ApplyIce();

protected:
	UPROPERTY()
	TArray<int> posX;
	UPROPERTY()
	TArray<int> posY;
	UPROPERTY()
	int curr_index = 0;
	UPROPERTY()
	class AkrtsPlayerController* Player;

private:
	int wave;
	TArray<int> HealthAtWave{
		25, 55, 95, 160, 230, 300, 450, 650, 920, 985, 1425, 1680, 1950
	};
	TArray<float> ArmorAtWave{
		0,	0, 0.2, 0.3, 0.8, 1.1, 0.8, 1.5, 1.8, 2.8, 1.5, 3.3, 2.85
	};
	TArray<float> SpeedAtWave{
		1, 1, 1, 1, 1.3, 1.8, 1, 1, 1.3, 1, 1.8, 1, 1.3
	};
	std::clock_t FireDurationTimer;
	std::clock_t FireTickTimer;
	std::clock_t IceDurationTimer;
	std::clock_t IceTickTimer;
	int FireTicksRemaining = 5;
	
	UFUNCTION()
	void ApplyBuffs();
	UFUNCTION()
	void Interpolate(float DeltaTime);
};
