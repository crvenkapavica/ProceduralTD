#include "CameraPawn.h"
#include "eMapGenerator.h"



ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-50, 0, 0));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

void ACameraPawn::BeginPlay()
{
	PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->CurrentMouseCursor = EMouseCursor::Default;

	Super::BeginPlay();
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACameraPawn::CameraZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACameraPawn::CameraZoomOut);
}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(GetCameraPanDirection() * CameraSpeed);


	/*
		TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
		LEARN FUCKING OOP !!!!!!!!!!! 
		BAD IMPLEMENTATION !!!!!!!
	*/
	if (!fuckIt) 
		if (!(UeMapGenerator::CRTS_GetStartX() == 0 && UeMapGenerator::CRTS_GetStartY() == 0)) {
			SetCameraStart();
			fuckIt = 1;
		}
	/*
		BAD IMPLEMENTATION // USE OOP!!!!!!!!!!!!!!!
	*/
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FVector ACameraPawn::GetCameraPanDirection()
{
	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;
	//OUT
	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
	PC->GetMousePosition(MousePosX, MousePosY);

	if (MousePosX == 0) {
		CamDirectionY = -1;
	}
	if (MousePosX >= ScreenSizeX - 2.f) {
		CamDirectionY = 1;
	}
	if (MousePosY == 0) {
		CamDirectionX = 1;
	}
	if (MousePosY >= ScreenSizeY - 2.f) {
		CamDirectionX = -1;
	}
	return FVector(CamDirectionX, CamDirectionY, 0.f);
}

void ACameraPawn::CameraZoomIn() {

	UE_LOG(LogTemp, Error, TEXT("Attempting camera ZoomIN"));
	if (GetActorTransform().GetLocation().Z > 150.f)
		AddActorWorldOffset(FVector(0.f, 0.f, -50.f));
}

void ACameraPawn::CameraZoomOut() {

	UE_LOG(LogTemp, Error, TEXT("Attempting camera ZoomOUT"));
	if (GetActorTransform().GetLocation().Z < 1550.f)
		AddActorWorldOffset(FVector(0.f, 0.f, 50.f));
}

void ACameraPawn::SetCameraStart() {

	int x = UeMapGenerator::CRTS_GetStartX() * 128.f - ScreenSizeX / 2;
	int y = UeMapGenerator::CRTS_GetStartY() * 128.f - ScreenSizeY / 2;
	AddActorWorldOffset(FVector(x, y, 1050.f));
}