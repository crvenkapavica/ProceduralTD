#include "MonsterBaseClass.h"
#include "eMapGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "krtsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#define DEBUFF_FIRE_TICKS 
#define DEBUFF_ICE_DURATION 8.f

AMonsterBaseClass::AMonsterBaseClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMonsterBaseClass::BeginPlay() {

	Super::BeginPlay();	

	Player = Cast<AkrtsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	HealthbarUI = CreateWidget<UUserWidget>(GetWorld(), wHealthbarUI);
	HealthbarUI->AddToViewport();
	HealthbarUI->SetAlignmentInViewport(FVector2D(0.5, 0.5));
	Healthbar = (UProgressBar*)HealthbarUI->GetWidgetFromName(TEXT("Healthbar"));

	wave = Player->Spawner->GetCurrentWave();
	Health = HealthAtWave[wave];
	Armor = ArmorAtWave[wave];
	MoveSpeed = SpeedAtWave[wave];

	posX = UeMapGenerator::CRTS_GetPosX();
	posY = UeMapGenerator::CRTS_GetPosY();
}

void AMonsterBaseClass::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	Interpolate(DeltaTime);
	ApplyBuffs();

	FVector2D ScreenLocation;
	Player->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);
	HealthbarUI->SetPositionInViewport(ScreenLocation);
	float percent = ((float)Health / (float)HealthAtWave[wave]);
	Healthbar->SetPercent(percent);
	Healthbar->SetFillColorAndOpacity(FLinearColor(1.f - percent, 0.15f, percent - 0.1f , 1.f));
	
	if (Health <= 0) {
		Destroy();
		HealthbarUI->RemoveFromViewport();
		Player->ModifyGold(8);
	}
}

void AMonsterBaseClass::Interpolate(float DeltaTime) {

	if (curr_index < posX.Num()) {
		float x = AMonsterBaseClass::GetTransform().GetTranslation().X;
		float y = AMonsterBaseClass::GetTransform().GetTranslation().Y;
		float destinationX = posX[curr_index] * 128.f;
		float destinationY = posY[curr_index] * 128.f;

		if (FMath::Abs(destinationX - x) >= 1.f) {
			x = FMath::FInterpConstantTo(x, destinationX, DeltaTime, 130.f * MoveSpeed);
		}
		else if (FMath::Abs(destinationY - y) >= 1.f) {
			y = FMath::FInterpConstantTo(y, destinationY, DeltaTime, 130.f * MoveSpeed);
		}
		else {
			curr_index++;
		}

		FVector position = FVector(x, y, 150);
		AMonsterBaseClass::SetActorLocation(position);
	}
	else {
		Destroy();
		Player->ModifyHealth(-1);
	}
}

void AMonsterBaseClass::ApplyDamage(int Damage, FString Type) {

	int DamageRange = Damage / 10;
	int MinDamage = Damage - DamageRange;
	int MaxDamage = Damage + DamageRange;
	Damage = FMath::RandRange(MinDamage, MaxDamage);
	Health -= (Damage - Armor * 33);

	if (Type == "ice") {
		ApplyIce();
	}
	if (Type == "fire") {
		if (!Debuffs.Contains("fire")) {
			Debuffs.Add("fire");
			FireTickTimer = std::clock();
		}
		FireTicksRemaining = 5;
	}
}

void AMonsterBaseClass::ApplyBuffs() {

	if (Debuffs.Contains("ice")) {
		if ((std::clock() - IceDurationTimer) / CLOCKS_PER_SEC < DEBUFF_ICE_DURATION) {
			MoveSpeed = 0.66f;
		}
		else {
			MoveSpeed = 1.f;
			Debuffs.Remove("ice");
		}
	}

	if (Debuffs.Contains("fire")) {
		if (FireTicksRemaining) {
			if ((std::clock() - FireTickTimer) / CLOCKS_PER_SEC > 1.f) {
				Health -= 35;
				FireTicksRemaining--;
				FireTickTimer = std::clock();
			}
		}
		else {
			Debuffs.Remove("fire");
		}
	}
}

void AMonsterBaseClass::ApplyIce() {

	if (!Debuffs.Contains("ice")) {
		Debuffs.Add("ice");
	}
	IceDurationTimer = std::clock();
}