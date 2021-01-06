#pragma once

#include "CoreMinimal.h"
#include "StaticMeshResources.h"
#include "GameFramework/Actor.h"
#include "Components/Button.h"
#include "Tower_Rapid.h"
#include "TowerIceBasic.h"
#include "TowerFireBasic.h"
#include "ActiveField.generated.h"

UCLASS(BlueprintType, Blueprintable)

class CRTS_API AActiveField : public AActor
{
	GENERATED_BODY()
	
public:	
	AActiveField();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UStaticMesh* Mesh;

	//FStaticMeshInstanceData* MeshInstance;

	UPROPERTY(EditAnywhere)
	UTexture* HoverTexture;
	UPROPERTY()
	UTexture* DefaultTexture;
	UPROPERTY()
	UMaterialInterface* Mat;
	UPROPERTY()
	TArray<UTexture*> Textures;
	UPROPERTY()
	int Orientation;

	UFUNCTION(BlueprintCallable)
	void OnMouseOver();
	UFUNCTION(BlueprintCallable)
	void OnMouseLeave();
};
