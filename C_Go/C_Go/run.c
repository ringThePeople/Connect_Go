#include <stdio.h>

void push(int board[][7],int);

void main() {
	int board[6][7] = { 0 }; //empty state :: 0 , player 1 :: 1 ,  player 2 :: 2

	int turn = 0;
	int height;

	
}

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
		if (board[num][height+1]==0)
		{
			board[num][height + 1] = 1;
		}
	}
	else if (turn = 0)
	{
		if (board[num][height + 1]==0)
		{
			board[num][height + 1] = 2;
		}
	}
	
}//4.06 21:46 JH