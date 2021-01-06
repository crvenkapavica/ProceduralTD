#include "Spawner.h"
#include "eMapGenerator.h"
#include "MonsterBaseClass.h"

#define WAVE_DELAY 8.f

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawner::BeginPlay() {

	Super::BeginPlay();
	posX = UeMapGenerator::CRTS_GetPosX();
	posY = UeMapGenerator::CRTS_GetPosY();
	activeX = UeMapGenerator::CRTS_GetActiveX();
	activeY = UeMapGenerator::CRTS_GetActiveY();
	startX = UeMapGenerator::CRTS_GetStartX() * 128;
	startY = UeMapGenerator::CRTS_GetStartY() * 128;
	Orientation = UeMapGenerator::CRTS_GetOrientation();
	WaveTimer = clock();
	SpawnTimer = clock();

	DrawMap();
}

void ASpawner::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (Waves[CurrentWave]) {
		if ((std::clock() - WaveTimer) / CLOCKS_PER_SEC > WAVE_DELAY &&
			(std::clock() - SpawnTimer) / CLOCKS_PER_SEC > 0.8f) {
			Spawn();
		}
	}
	else {
		if (CurrentWave == Waves.Num() - 1) {
			CurrentWave = 0;
		}
		else {
			++CurrentWave;
		}
		WaveTimer = clock();
	}
}

void ASpawner::Spawn() {

	FTransform Transform(FVector(startX, startY, 500.f));
	TSubclassOf<AMonsterBaseClass> CurrentMonster = CurrentWave < 3 ? MonsterToSpawn : NewMonster;
	AMonsterBaseClass* currEnemy = GetWorld()->SpawnActor<AMonsterBaseClass>(CurrentMonster, Transform);
	SpawnTimer = clock();
	--Waves[CurrentWave];
}

void ASpawner::DrawMap() {

	//Draw Path
	for (int i = 0; i < posX.Num() - 1; i++) {
		FTransform Transform(FVector(posX[i] * 128.f, posY[i] * 128.f, 111.f));
		AActor* currTile = GetWorld()->SpawnActor<ATowerActor>(PathTile, Transform);
	}

	//Draw End
	FRotator rotation{ 0.f, 0.f, 0.f };
	if (posX[posX.Num() - 2] == posX[posX.Num() - 1]) {
		rotation.Yaw = 90.f;
	}
	FQuat Quat(rotation);
	FVector Position(posX[posX.Num() - 1] * 128.f, posY[posY.Num() - 1] * 128.f, 111.f);
	ACottage* cottage = GetWorld()->SpawnActor<ACottage>(Cottage, FTransform(Quat, Position));

	//Draw active tiles
	for (int i = 0; i < activeX.Num(); i++) {
		AActiveField* activeTile = GetWorld()->SpawnActor<AActiveField>
			(ActiveTile, FTransform(FVector(activeX[i] * 128.f, activeY[i] * 128.f, 111.f)));
		activeTile->Orientation = Orientation[i];
	}
}

float ASpawner::GetSpawnTimer() {

	float time = (std::clock() - WaveTimer) / CLOCKS_PER_SEC;
	
	return WAVE_DELAY - time;
}

int ASpawner::GetCurrentWave() {

	return CurrentWave;
}
