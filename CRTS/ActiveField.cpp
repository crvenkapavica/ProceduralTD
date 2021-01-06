#include "ActiveField.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "UnitBuilder.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"

AActiveField::AActiveField()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AActiveField::BeginPlay() {

	Super::BeginPlay();
	/*
	Mesh = this->Mesh;
	Mat = Mesh->GetMaterial(0);
	
	Mat->GetUsedTextures(Textures, EMaterialQualityLevel::Num, true, ERHIFeatureLevel::Num, true);
	DefaultTexture = Textures[3];*/
}

void AActiveField::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AActiveField::OnMouseOver() {
	/*
	Mat->GetUsedTextures(Textures, EMaterialQualityLevel::Num, true, ERHIFeatureLevel::Num, true);
	Mat->OverrideTexture(Textures[3], HoverTexture, ERHIFeatureLevel::SM5);*/
}

void AActiveField::OnMouseLeave() {
	/*
	Mat->GetUsedTextures(Textures, EMaterialQualityLevel::Num, true, ERHIFeatureLevel::Num, true);
	Mat->OverrideTexture(Textures[3], DefaultTexture, ERHIFeatureLevel::SM5);*/
}