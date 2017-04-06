#include <stdio.h>
#include <stdbool.h>

bool sub_check(int arr[][7], int x, int y)	//check LeftUp, Up, RightUp, Right
{
	int stone = arr[x][y];
	int i, j;
	if (x>2 && y<4)
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
	
	// --> 04/06 21:37 jeongin
	int first, player1, player2;
	printf("Who start first?");
	scanf("%d", &turn);
	// <-- 04/06 21:37 jeongin

	print_board(board);

	getchar();

	int height;

	
}
void print_board(int board[][7])
{
	int i, j;	//.○●


	for (i = 5; i >= 0; i--) {
		for (j = 6; j >= 0; j--) {
			if (board[i][j] == 0)
				printf("%2s", " .");
			else if (board[i][j] == 1)
				printf("%2s", "●");
			else
				printf("%2s", "○");
		}
		printf("\n");
	}
	printf("ㅣ0ㅣ1ㅣ2ㅣ3ㅣ4ㅣ5ㅣ6ㅣ");

} // 04/06 21:23 jeongin 

void push(int board[][7],int turn)
{
	int num,player;//num : insert place, turning : who will push
	int height;//table height
	player = turn % 2;//player 1 turn : 1, player 2 turn : 0
	printf("|0|1|2|3|4|5|6|\n\n");
	printf("위치의 번호를 입력하시오 : ");
	scanf_s("%d", &num); //Push Point Insert
	if (turn = 1)
	{
		if (board[height + 1][num]==0)
		{
			board[height + 1][num] = 1;
		}
	}
	else if (turn = 0)
	{
		if (board[height + 1][num] ==0)
		{
			board[height + 1][num] = 2;
		}
	}
	
}//4.06 21:46 JH