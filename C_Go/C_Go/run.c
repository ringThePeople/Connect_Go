#include <stdio.h>
#include <stdbool.h>

bool sub_check(int arr[][7], int x, int y)	//check LeftUp, Up, RightUp, Right
{
	int stone = arr[x][y];
	int i, j;
	if(x>2 && y<4)
		for (i = 1; i < 4; i++)
		{
			if (arr[x - i][y + i] != stone)
				break;
			if (i == 3)
				return true;
		}
	if (y<4)
		for (i = 1; i < 4; i++)
		{
			if (arr[x][y + i] != stone)
				break;
			if (i == 3)
				return true;
		}
	if (x<4 && y<4)
		for (i = 1; i < 4; i++)
		{
			if (arr[x + i][y + i] != stone)
				break;
			if (i == 3)
				return true;
		}
	if (x<4)
		for (i = 1; i < 4; i++)
		{
			if (arr[x + i][y] != stone)
				break;
			if (i == 3)
				return true;
		}

	return false;
}// 04/06 21:40		by Jongmin
int winCheck(int arr[][7])	// 0:: not yet finished ,  (1 or 2) winner , 3 draw
{
	int linked = 0;
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (arr[i][j] == 0)
				continue;
			if (sub_check(arr, j, i)) // important thing is x::j, y :: i
				return arr[i][j];
		}
	}
	return 3;
}//	04/06 21:41		by Jongmin
void main() {
	int board[6][7] = { 0 }; //empty state :: 0 , player 1 :: 1 ,  player 2 :: 2
	//initialized by JM

	
	int turn = 0;

	
}