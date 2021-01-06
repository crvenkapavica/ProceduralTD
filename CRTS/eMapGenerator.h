#pragma once

#include "CoreMinimal.h"
#include "TowerActor.h"
#include "Kismet/BlueprintFunctionLibrary.h"  
#include "ActiveField.h"
#include "eMapGenerator.generated.h"

UCLASS(Blueprintable)
class CRTS_API UeMapGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UeMapGenerator();

	UFUNCTION(BlueprintCallable)
	static int GetEnemyCount();
	UFUNCTION(BlueprintCallable, Category = "External")
	static void CRTS_Print(int value);
	UFUNCTION(BlueprintCallable, Category = "External")
	static void CRTS_Printf(float value);
	UFUNCTION(BlueprintCallable, Category = "External")
	static void CRTS_GeneratePosition(int dens, int cols, int rows);
	UFUNCTION(BlueprintCallable, Category = "New_External")
	static int CRTS_GetPosXAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "New_External")
	static int CRTS_GetPosYAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "New_External")
	static int CRTS_GetStartX();
	UFUNCTION(BlueprintCallable, Category = "New_External")
	static int CRTS_GetStartY();
	UFUNCTION()
	static void __BFS(int dens, int cols, int rows);

	UFUNCTION(BlueprintCallable, Category = "External")
	static TArray<int> CRTS_GetPosX();
	UFUNCTION(BlueprintCallable, Category = "External")
	static TArray<int> CRTS_GetPosY();
	UFUNCTION(BlueprintCallable, Category = "External")
	static TArray<int> CRTS_GetActiveX();
	UFUNCTION(BlueprintCallable, Category = "External")
	static TArray<int> CRTS_GetActiveY();
	UFUNCTION(BlueprintCallable, Category = "External")
	static TArray<int> CRTS_GetOrientation();

private:
	
	UFUNCTION()
	static void disable_adjacent(int x, int y);
	UFUNCTION()
	static void disable_behind(int x, int y);
	/*
	UFUNCTION()
	static void disable_col(int col, int y);
	UFUNCTION()
	static void disable_row(int x, int row);*/
	UFUNCTION()
	static void reset_moves();
	UFUNCTION()
	static void reset_direction();
	UFUNCTION()
	static void BFS(int x, int y);
};
