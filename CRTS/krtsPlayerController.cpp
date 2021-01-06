#include "krtsPlayerController.h"
#include "Engine/World.h"
#include "ActiveField.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UnitBuilder.h"
#include "EngineUtils.h"
#include "UObject/UObjectGlobals.h"

#define INTEREST_DELAY 3.5f

AkrtsPlayerController::AkrtsPlayerController()
{
	AkrtsPlayerController::bEnableClickEvents = true;
	AkrtsPlayerController::bEnableMouseOverEvents = true;
	bShowMouseCursor = true;
}

void AkrtsPlayerController::PlayerTick(float DeltaTime) {

	Super::PlayerTick(DeltaTime);

	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit && !bIsFieldSelected) {
		if (!ActorTick) {
			//New target, select
			ActorTick = Hit.GetActor();
			if (ActorTick->IsA<AActiveField>()) {
				Select(1, ActorTick);
			}
		}
		else if (ActorTick != Hit.GetActor()) {
			//Old target, deselect
			if (ActorTick->IsA<AActiveField>()) {
				Select(0, ActorTick);
			}
			//New target
			ActorTick = Hit.GetActor();
			if (ActorTick->IsA<AActiveField>()) {
				Select(1, ActorTick);
			}
		}
	}

	if ((std::clock() - GoldTimer) / CLOCKS_PER_SEC > INTEREST_DELAY) {
		++PlayerGold;
		GoldTimer = std::clock();
	}

	if (Button_Build_Rapid)
		Button_Build_Rapid->bIsEnabled = PlayerGold < 65 ? false : true;
	if (Button_Build_Fire)
		Button_Build_Fire->bIsEnabled = PlayerGold < 200 ? false : true;
	if (Button_Build_Ice)
		Button_Build_Ice->bIsEnabled = PlayerGold < 120 ? false : true;
}

void AkrtsPlayerController::SetupInputComponent() {

	// set up gameplay key bindings
	Super::SetupInputComponent();
	
	InputComponent->BindAction("Trace", IE_Pressed, this, &AkrtsPlayerController::Trace);
	//Get Spawner
	for (TActorIterator<ASpawner> Iter(GetWorld()); Iter; ++Iter) {
		Spawner = *Iter;
	}

	//HUD
	//Build
	BuildMenu = CreateWidget<UUserWidget>(GetWorld(), wBuildMenu);
	Button_Build_Rapid = (UButton*)BuildMenu->GetWidgetFromName(TEXT("Button_Build"));
	Button_Build_Fire = (UButton*)BuildMenu->GetWidgetFromName(TEXT("Button_Build_Fire"));
	Button_Build_Ice = (UButton*)BuildMenu->GetWidgetFromName(TEXT("Button_Build_Ice"));
	if (Button_Build_Rapid) {
		Button_Build_Rapid->OnClicked.AddDynamic(this, &AkrtsPlayerController::BuildRapid);
	}
	if (Button_Build_Fire) {
		Button_Build_Fire->OnClicked.AddDynamic(this, &AkrtsPlayerController::BuildFire);
	}
	if (Button_Build_Ice) {
		Button_Build_Ice->OnClicked.AddDynamic(this, &AkrtsPlayerController::BuildIce);
	}
	//Upgrade
	UpgradeMenu = CreateWidget<UUserWidget>(GetWorld(), wUpgradeMenu);
	///////////////////////////////////////////////////////////////////////////////////////

	GoldTimer = std::clock();
}


void AkrtsPlayerController::Trace() {
	
	GetHitResultUnderCursor(ECC_WorldDynamic, false, Hit);

	if (Hit.bBlockingHit) {
		ActorTrace = Hit.GetActor();

		if (ActorTrace->IsA<AActiveField>()) {
			if (!SelectedFields.Contains(ActorTrace)) {
				if (SelectedField && bIsFieldSelected) {
					Select(0, SelectedField);
				}
				bIsFieldSelected = false;
				SelectedField = Cast<AActiveField>(ActorTrace);
				Select(1, SelectedField);
				bIsFieldSelected = true;
				if (BuildMenu && !BuildMenu->IsInViewport()) {
					BuildMenu->AddToViewport();
				}
			}
		}
		else if (ActorTrace->IsA<ATowerBaseClass>()) {
			UpgradeMenu->AddToViewport();
			SelectedTower = Cast<ATowerBaseClass>(ActorTrace);
		}
		else if (bIsFieldSelected) {
			Select(0, SelectedField);
			bIsFieldSelected = false;
			if (BuildMenu && BuildMenu->IsInViewport()) {
				BuildMenu->RemoveFromViewport();
			}
		}
	}
}

void AkrtsPlayerController::Select(bool bSelect, AActor* Field) {

	if (bSelect) {
		FVector offsetUp{ 0.f, 0.f, 11.f };
		Field->ApplyWorldOffset(offsetUp, false);
	}
	else {
		FVector offsetDown{ 0.f, 0.f, -11.f };
		Field->ApplyWorldOffset(offsetDown, false);
	}
}

void AkrtsPlayerController::BuildRapid() {

	Select(0, SelectedField);
	bIsFieldSelected = false;
	AUnitBuilder::BuildTower(GetWorld(), TowerRapid_BP, SelectedField);
	SelectedFields.Add(Cast<AActor>(SelectedField));
	BuildMenu->RemoveFromViewport();
	PlayerGold -= 65;
}

void AkrtsPlayerController::BuildFire() {

	Select(0, SelectedField);
	bIsFieldSelected = false;
	AUnitBuilder::BuildTower(GetWorld(), TowerFire_BP, SelectedField);
	SelectedFields.Add(Cast<AActor>(SelectedField));
	BuildMenu->RemoveFromViewport();
	PlayerGold -= 200;
}

void AkrtsPlayerController::BuildIce() {

	Select(0, SelectedField);
	bIsFieldSelected = false;
	AUnitBuilder::BuildTower(GetWorld(), TowerIce_BP, SelectedField);
	SelectedFields.Add(Cast<AActor>(SelectedField));
	BuildMenu->RemoveFromViewport();
	PlayerGold -= 120;
}

void AkrtsPlayerController::ModifyHealth(int value) {

	PlayerHealth += value;
}

void AkrtsPlayerController::ModifyGold(int value) {

	PlayerGold += value;
}

int AkrtsPlayerController::GetGold() {
	
	return PlayerGold;
}

int AkrtsPlayerController::GetHealth() {

	return PlayerHealth;
}

float AkrtsPlayerController::GetHUDSpawnTimer() {

	return Spawner ? Spawner->GetSpawnTimer() : -1.f;
}

FString AkrtsPlayerController::GetTowerName() {

	if (SelectedTower) {
		FString Name = SelectedTower->GetName();
		if (Name.Contains("Rapid")) {
			Name = "Rapid Tower";
		}
		else if (Name.Contains("Ice")) {
			Name = "Ice Tower";
		}
		else if (Name.Contains("Fire")) {
			Name = "Fire Tower";
		}
		return Name + " - level 1";
	}
	else {
		return "No Tower Selected";
	}
}