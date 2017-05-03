#include <stdio.h>
#include <stdbool.h>

//initialize functions
void print_board(int board[][7]);
void push(int board[][7], int turn);
bool sub_check(int arr[][7], int x, int y);
int winCheck(int arr[][7]);
int column_check(int arr[][7], int x, int y);
void winnerPrint(int first, int winCheck);

//main function
void main() {
	int board[6][7] = { 0 }; //empty state :: 0 , player 1 :: 1 ,  player 2 :: 2
							 //initialized by JM


	int turn = 1;

	// --> 04/06 21:37 jeongin
	int first;
	printf("Who start first?");
	scanf_s("%d", &first);
	// <-- 04/06 21:37 jeongin

	int winner = 0;
	while (winner == 0)
	{
		push(board, first+(turn++));

		print_board(board);


		winner = winCheck(board);
	}
	//winner 1or2 -> 1or 2 win ,,  3 -> draw
	
	winnerPrint(first, winner);

	getchar();
}


//fucntion interface
void print_board(int board[][7])
{
	int i, j;	// we use ○● to identify units


	for (i = 5; i >= 0; i--) {
		for (j = 0; j < 7; j++) {
			if (board[i][j] == 0)
				printf("%2s", " .");
			else if (board[i][j] == 1)
				printf("%2s", "●");
			else
				printf("%2s", "○");
		}
		printf("\n");
	}
	printf("|0|1|2|3|4|5|6|\n\n");

} // 04/06 21:23 jeongin 


void push(int board[][7], int turn)
{
	int num;//num : insert place, turning : who will push
	int height = 0;//table height
	if(turn<3)
		printf("|0|1|2|3|4|5|6|\n\n");
	printf("위치의 번호를 입력하시오 : ");
	scanf_s("%d", &num); //Push Point Insert

	int i;
	for (i = 0; i < 6; i++)		// 04/06 22:10 develop height check function, by Jongmin
	{
		if (board[i][num] == 0)
		{
			height = i;
			break;
		}
		if (i == 5)
		{
			printf("숫자를 잘못 입력하였습니다.\n");
			return push(board, turn);
		}
	}
	board[height][num] = (turn % 2) + 1;	

}//4.06 21:46 JH



bool sub_check(int arr[][7], int x, int y)	//check LeftUp, Up, RightUp, Right
{
	int stone = arr[y][x];
	int i, j;
	if (x>2 && y>2)
		for (i = 1; i < 4; i++)
		{
			if (arr[y - i][x - i] != stone)
				break;
			if (i == 3)
				return true;
		}
	if (y>2)
		for (i = 1; i < 4; i++)
		{
			if (arr[y - i][x] != stone)
				break;
			if (i == 3)
				return true;
		}
	if (x<4 && y>2)
		for (i = 1; i < 4; i++)
		{
			if (arr[y - i][x + i] != stone)
				break;
			if (i == 3)
				return true;
		}
	if (x<4)
		for (i = 1; i < 4; i++)
		{
			if (arr[y][x + i] != stone)
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
	for (i = 5; i >= 0; i--)
	{
		for (j = 0; j < 7; j++)
		{
			if (arr[i][j] == 0)
				continue;
			if (sub_check(arr, j, i)) // important thing is x::j, y :: i
				return arr[i][j];
		}
	}

	for (i = 0; i < 6; i++)
		for (j = 0; j < 7; j++)
			if (arr[i][j] == 0)
				return 0;
	return 3;
}//	04/06 21:41		by Jongmin


//세로로 이기는 경우 or 지는 경우 체크
int column_check(int arr[][7], int x, int y) {

	int i;
	int count = 0;

	for (i = y; i >= 0; i--) {
		if (arr[i][x] == 1)
			count++;
		else if (arr[i][x] == 2)
			return 0;

		if (count == 3)
			return 2000;
	}

	count = 0;

	for (i = y; i >= 0; i--) {
		if (arr[i][x] == 2)
			count++;
		else if (arr[i][x] == 1)
			return 0;

		if (count == 3)
			return 1000;
	}

	return 0;
} // 세로로 이기는 경우 or 지는 경우 by JeongIn.

void winnerPrint(int first, int winCheck)
{
	printf("\n\n");
	
	if (winCheck == 3)
		printf("!!  Draw !!\n\n");
	else
		printf("Winner is %d\n\n", first);
}// 04/06 23:14		by Jongmin