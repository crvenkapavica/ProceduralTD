#pragma once

#include "CoreMinimal.h"
#include <ctime>
#include "TowerActor.h"
#include "Cottage.h"
#include "Ogre.h"
#include "ActiveField.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class CRTS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Spawn();

	UFUNCTION()
	void DrawMap();

	UFUNCTION(BlueprintCallable)
	float GetSpawnTimer();

	UFUNCTION()
	int GetCurrentWave();

private:
	std::clock_t SpawnTimer;
	std::clock_t WaveTimer;

	UPROPERTY()
	TArray<int> Waves = { 12, 12, 12, 15, 15, 18, 18, 20, 20, 22, 22, 22, 22, 22, 25, 25, 25, 25, 25, 25, 28, 28, 30 };
	UPROPERTY()
	int CurrentWave = 0;
	UPROPERTY()
	int EnemyCount;
	UPROPERTY()
	TArray<int> activeX;
	UPROPERTY()
	TArray<int> activeY;
	UPROPERTY()
	TArray<int> posX;
	UPROPERTY()
	TArray<int> posY;
	UPROPERTY()
	TArray<int> Orientation;
	UPROPERTY()
	int startX;
	UPROPERTY()
	int startY;

	UPROPERTY(EditAnywhere, Category = "Monster")
	TSubclassOf<AMonsterBaseClass> MonsterToSpawn;
	UPROPERTY(EditAnywhere, Category = "Monster")
	TSubclassOf<AMonsterBaseClass> NewMonster;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATowerActor> PathTile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActiveField> ActiveTile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACottage> Cottage;
};
