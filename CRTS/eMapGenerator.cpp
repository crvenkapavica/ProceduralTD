#include "eMapGenerator.h"
#include "CRTS_static.h"
#include "CameraPawn.h"
#include "GameFramework/Pawn.h"


#define max_map_size 101

int map[max_map_size][max_map_size];
int dX[4] = { 0, 0, 1, -1 };
int dY[4] = { -1, 1, 0, 0 };
int density;
int C, R;
bool crash, returning;

int way;
int direction_curr;
int moves_curr_cnt;
int moves_granted;
int moves_total;
int EnemiesRemaining;
int startX, startY;
//bool behind = false;

TArray<int> posX;
TArray<int> posY;
TArray<int> activeX;
TArray<int> activeY;
TArray<int> orientation;

UeMapGenerator::UeMapGenerator() { }

/*
void UeMapGenerator::disable_col(int col, int y) {
	for (int i = 0; i < moves_curr_cnt; i++) {
		int mdf = y + i * way;
		if (map[col][mdf] == -2) {
			map[col][mdf] = 0;
			activeX.Add(col);
			activeY.Add(mdf);
		}
	}
}
void UeMapGenerator::disable_row(int x, int row) {
	for (int i = 0; i < moves_curr_cnt; i++) {
		int mdf = x + i * way;
		if (map[mdf][row] == -2) {
			map[mdf][row] = 0;
			activeX.Add(mdf);
			activeY.Add(row);
		}
	}
}

void UeMapGenerator::disable_adjacent(int x, int y) {

	if (moves_curr_cnt > 1) {
		int d = -1, u = -1, r = -1, l = -1;
		//finished moving right or left
		if (direction_curr == 2 || direction_curr == 3) {
			if (y + 1 < R) {
				d = y + 1;
			} 
			if (y - 1 >= 0) {
				u = y - 1;
			}
			way = (direction_curr == 2) ? -1 : 1;
		}
		//finished moving up or down
		else {
			if (x + 1 < C) {
				r = x + 1;
			} 
			if (x - 1 >= 0) {
				l = x - 1;
			}
			way = direction_curr ? 1 : -1;
		}
		if (d != -1) {
			disable_row(x + 1*way, d);
		}
		if (u != -1) {
			disable_row(x + 1*way, u);
		}
		if (l != -1) {
			disable_col(l, y + 1*way);
		}
		if (r != -1) {
			disable_col(r, y + 1*way);
		}
	}
}*/

void UeMapGenerator::disable_adjacent(int x, int y) {

	//moving up or down
	if (direction_curr == 1 || direction_curr == 0) {
		//disable left
		if (map[x + 1][y] == -2) {
			activeX.Add(x + 1);
			activeY.Add(y);
			orientation.Add(2);
			map[x + 1][y] = 0;
		}
		//disable right
		if (map[x - 1][y] == -2) {
			activeX.Add(x - 1);
			activeY.Add(y);
			orientation.Add(3);
			map[x - 1][y] = 0;
		}
	}
	else {
		if (map[x][y + 1] == -2) {
			activeX.Add(x);
			activeY.Add(y + 1);
			orientation.Add(1);
			map[x][y + 1] = 0;
		}
		if (map[x][y - 1] == -2) {
			activeX.Add(x);
			activeY.Add(y - 1);
			orientation.Add(0);
			map[x][y - 1] = 0;
		}
	}
}

void UeMapGenerator::disable_behind(int x, int y) {

	activeX.Add(x);
	activeY.Add(y);
	map[x][y] = 0;
}

void UeMapGenerator::reset_moves() {
	//number of moves in this direction
	moves_granted = FMath::RandRange(1, 1777) % 5 + 2;
	moves_curr_cnt = 0;
}
void UeMapGenerator::reset_direction() {
	//new direction
	direction_curr = FMath::RandRange(0, 1777) % 4;
	reset_moves();
}

void UeMapGenerator::BFS(int x, int y) {

	if (returning) return;
	/*if (crash) {
		reset_direction();
		crash = 0;
		return;
	}*/
	if (moves_total >= density) {
		returning = 1;
		return;
	}
	crash = 1;
	if (x < 0 || x > C) return;
	if (y < 0 || y > R) return;
	if (map[x][y] >= 0) return;
	//at this point we're in bounds
	crash = 0;

	moves_curr_cnt++;
	moves_total++;
	map[x][y] = moves_total;
	posX.Add(x);
	posY.Add(y);

	if (moves_curr_cnt < moves_granted && map[x + dX[direction_curr]][y + dY[direction_curr]] < 0) {
		disable_adjacent(x, y);
	}
	else {
		int direction_old = direction_curr;
		reset_direction();
		if (direction_old == direction_curr) {
			disable_adjacent(x, y);
		}
		else {
			if (direction_curr == 1 && map[x][y - 1] == -2) {
				disable_behind(x, y - 1);
				orientation.Add(5);
				//disable_adjacent(x, y);
			}
			else if (direction_curr == 0 && map[x][y + 1] == -2) {
				disable_behind(x, y + 1);
				orientation.Add(5);
				//disable_adjacent(x, y);
			}
			else if (direction_curr == 2 && map[x - 1][y] == -2) {
				disable_behind(x - 1, y);
				orientation.Add(5);
				//disable_adjacent(x, y);
			}
			else if (map[x + 1][y] == -2) { //dir = 3
				disable_behind(x + 1, y);
				orientation.Add(5);
				//disable_adjacent(x, y);
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		direction_curr = (direction_curr + i) % 4;
		int d = direction_curr;
		BFS(x + dX[d], y + dY[d]);
	}                   
	returning = 1;
}

/*
 * Initialize BFS.
 */
void UeMapGenerator::__BFS(int dens, int cols, int rows) {
	//initialize 
	C = cols; R = rows;
	density = dens;

	//reset
	moves_total = 0;
	crash = 0;
	returning = 0;
	way = 1;
	posX.Empty();
	posY.Empty();
	activeX.Empty();
	activeY.Empty();
	reset_direction();

	//initialize empty map
	for (int i = 0; i < C; i++)
		for (int j = 0; j < R; j++)
			map[i][j] = -2;
	
	//start generating using BFS at (X,Y)
	startX = FMath::RandRange(5, 35);
	startY = FMath::RandRange(5, 35);
	BFS(startX, startY);
}

void UeMapGenerator::CRTS_Print(int value) {
	UE_LOG(LogTemp, Warning, TEXT("%d"), value);
}
void UeMapGenerator::CRTS_Printf(float value) {
	UE_LOG(LogTemp, Warning, TEXT("%f"), value);
}

/*
 * BlueprintCall for generating positions, returns a 1D TArray<int>
 */
void UeMapGenerator::CRTS_GeneratePosition(int dens, int cols, int rows) {
	__BFS(dens, cols, rows);
	EnemiesRemaining = 8;
}

int UeMapGenerator::CRTS_GetPosXAtIndex(int index) {
	return posX[index];
}

int UeMapGenerator::CRTS_GetPosYAtIndex(int index) {
	return posY[index];
}

int UeMapGenerator::CRTS_GetStartX() {
	return startX;
}

int UeMapGenerator::CRTS_GetStartY() {
	return startY; 
}

TArray<int> UeMapGenerator::CRTS_GetPosX() {
	return posX;
}
TArray<int> UeMapGenerator::CRTS_GetPosY() {
	return posY;
}
TArray<int> UeMapGenerator::CRTS_GetActiveX() {
	return activeX;
}
TArray<int> UeMapGenerator::CRTS_GetActiveY() {
	return activeY;
}
TArray<int> UeMapGenerator::CRTS_GetOrientation() {
	return orientation;
}
 
int UeMapGenerator::GetEnemyCount() {
	return EnemiesRemaining;
}