#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "krtsPlayerController.h"
#include "CameraPawn.generated.h"

UCLASS()
class CRTS_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACameraPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY()
	USceneComponent* RootScene;
	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere)
	APlayerController* PC;
	UPROPERTY()
	int32 ScreenSizeX;
	UPROPERTY()
	int32 ScreenSizeY;
	UPROPERTY()
	float CameraSpeed = 25.6f;

	UFUNCTION()
	FVector GetCameraPanDirection();
	UFUNCTION()
	void CameraZoomIn();
	UFUNCTION()
	void CameraZoomOut();
	UFUNCTION()
	void SetCameraStart();

	bool fuckIt = 0;
};
