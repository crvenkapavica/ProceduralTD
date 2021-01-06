#include "UnitBuilder.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"

AUnitBuilder::AUnitBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AUnitBuilder::BeginPlay() {

	Super::BeginPlay();
}

void AUnitBuilder::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AUnitBuilder::BuildTower(UObject* WorldContextObject, const TSubclassOf<ATowerBaseClass> TowerClass, 
	AActor* Parent) {
	
	if (GEngine) {
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
		ATowerBaseClass* TowerToBuild = World->SpawnActor<ATowerBaseClass>(TowerClass, Parent->GetActorTransform());
		TowerToBuild->AttachToActor(Parent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AUnitBuilder::BuildTower(UObject* WorldContextObject, const TSubclassOf<ATowerBaseClass> TowerClass,
	AActor* Parent, int Orientation) {

	if (GEngine) {
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
		ATowerBaseClass* TowerToBuild = World->SpawnActor<ATowerBaseClass>(TowerClass, Parent->GetActorTransform());
		TowerToBuild->AttachToActor(Parent, FAttachmentTransformRules::KeepWorldTransform);
		
		switch (Orientation) {
		case 1:
			TowerToBuild->SetActorRotation(FQuat(FRotator(0.f, 180.f, 0.f)), ETeleportType::None);
			break;
		case 2:
			TowerToBuild->SetActorRotation(FQuat(FRotator(0.f, 90.f, 0.f)), ETeleportType::None);
			break;
		case 3:
			TowerToBuild->SetActorRotation(FQuat(FRotator(0.f, -90.f, 0.f)), ETeleportType::None);
			break;
		}
	}
}