#pragma once

#include "CoreMinimal.h"
#include <ctime>
#include "GameFramework/PlayerController.h"
#include "eMapGenerator.h"
#include "Spawner.h"
#include "krtsPlayerController.generated.h"

UCLASS()
class AkrtsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AkrtsPlayerController();

	UFUNCTION()
	void ModifyGold(int value);
	UFUNCTION()
	void ModifyHealth(int value);

	UPROPERTY()
	ASpawner* Spawner = NULL;

protected:

	uint32 bMoveToMouseCursor;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	//Player
	UPROPERTY()
	int PlayerGold = 12265;
	UPROPERTY()
	int PlayerHealth = 15;

	//World
	UPROPERTY()
	FHitResult Hit;
	UPROPERTY()
	AActor* ActorTick;
	UPROPERTY()
	AActor* ActorTrace;
	UPROPERTY()
	class AActiveField* SelectedField;
	UPROPERTY()
	TArray<AActor*> SelectedFields;
	UPROPERTY()
	bool bIsFieldSelected = false;
	UPROPERTY()
	ATowerBaseClass* SelectedTower = NULL;

	//HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildMenu")
	TSubclassOf<class UUserWidget> wBuildMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildMenu")
	TSubclassOf<class UUserWidget> wUpgradeMenu;
	UPROPERTY()
	UUserWidget* BuildMenu;
	UPROPERTY()
	UUserWidget* UpgradeMenu;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Build_Rapid;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Build_Fire;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Build_Ice;
	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
	TSubclassOf<ATower_Rapid> TowerRapid_BP;
	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
	TSubclassOf<ATowerBaseClass> TowerFire_BP;
	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
	TSubclassOf<ATowerBaseClass> TowerIce_BP;
	UFUNCTION()
	void BuildRapid();
	UFUNCTION()
	void BuildFire();
	UFUNCTION()
	void BuildIce();
	UFUNCTION(BlueprintCallable)
	int GetGold();
	UFUNCTION(BlueprintCallable)
	int GetHealth();
	UFUNCTION(BlueprintCallable)
	float GetHUDSpawnTimer();
	UFUNCTION(BlueprintCallable)
	FString GetTowerName();
	////////////////////////////////////////////////////////////////////////

	UFUNCTION()
	void Trace();
	UFUNCTION()
	void Select(bool bSelect, AActor* Field);

	std::clock_t GoldTimer;
};

