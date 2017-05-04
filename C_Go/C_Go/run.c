#include <stdio.h>
#include <stdbool.h>

//initialize functions
void print_board(int board[][7]);
void push(int board[][7], int turn);
//bool sub_check(int arr[][7], int x, int y);
bool sub_check(int arr[][7], int y);
int winCheck(int arr[][7]);
int column_check(int arr[][7], int x, int y, int who); // 세로로 연속된 3개가 있는지 체크
void winnerPrint(int first, int winCheck);
void Do_by_condition(int arr[][7]);
int row_check(int arr[][7], int x, int y);
int fiveStone(int arr[][7], int x, int y, int who); // 5목이 되는경우 판단


//main function
void main() {
	int board[6][7] = { 0 }; //empty state :: 0 , player 1 :: 1 ,  player 2 :: 2
							 //initialized by JM


	int turn = 1;

	// --> 04/06 21:37 jeongin
	int first;
	printf("Who start first?\n(Connect-Go : 1 , You : 2)");
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


//some problem ..when it is connected five.. so develope more..
//bool sub_check(int arr[][7], int x, int y)	//check LeftUp, Up, RightUp, Right
//{
//	int stone = arr[y][x];
//	int i, j;
//	if (x>2 && y>2)
//		for (i = 1; i < 4; i++)
//		{
//			if (arr[y - i][x - i] != stone)
//				break;
//			if (i == 3)
//				return true;
//		}
//	if (y>2)
//		for (i = 1; i < 4; i++)
//		{
//			if (arr[y - i][x] != stone)
//				break;
//			if (i == 3)
//				return true;
//		}
//	if (x<4 && y>2)
//		for (i = 1; i < 4; i++)
//		{
//			if (arr[y - i][x + i] != stone)
//				break;
//			if (i == 3)
//				return true;
//		}
//	if (x<4)
//		for (i = 1; i < 4; i++)
//		{
//			if (arr[y][x + i] != stone)
//				break;
//			if (i == 3)
//				return true;
//		}
//
//	return false;
//}// 04/06 21:40		by Jongmin
//
//
//int winCheck(int arr[][7])	// 0:: not yet finished ,  (1 or 2) winner , 3 draw
//{
//	int linked = 0;
//	int i, j;
//	for (i = 5; i >= 0; i--)
//	{
//		for (j = 0; j < 7; j++)
//		{
//			if (arr[i][j] == 0)
//				continue;
//			if (sub_check(arr, j, i)) // important thing is x::j, y :: i
//				return arr[i][j];
//		}
//	}
//
//	for (i = 0; i < 6; i++)
//		for (j = 0; j < 7; j++)
//			if (arr[i][j] == 0)
//				return 0;
//	return 3;
//}//	04/06 21:41		by Jongmin

bool sub_check(int arr[][7], int y)		//redevelope subcheck by Jongmin
{
	int i;
	int cnt = 0;
	int stone = arr[y][3];

	for (i = 1; i < 4; i++)		//win, row case
	{
		if (arr[y][3 + i] != stone)
			break;
		cnt++;
	}
	for (i = 1; i < 4; i++)
	{
		if (arr[y][3 - i] != stone)
			break;
		cnt++;
	}
	if (cnt == 3)
		return true;
	cnt = 0;
	
	for (i = 1; i < 4; i++)		//win , '/' diagonal
	{
		if (y + i > 5)
			break;

		if (arr[y + i][3 + i] != stone)
			break;
		cnt++;
	}
	for (i = 1; i < 4; i++)
	{
		if (y - i < 0)
			break;

		if (arr[y - i][3 - i] != stone)
			break;
		cnt++;
	}
	if (cnt == 3)
		return true;
	cnt = 0;

	for (i = 1; i < 4; i++)			//win , 'reverse / ' diagonal
	{
		if (y + i > 5)
			break;

		if (arr[y + i][3 - i] != stone)
			break;
		cnt++;
	}
	for (i = 1; i < 4; i++)
	{
		if (y - i < 0)
			break;

		if (arr[y - i][3 + i] != stone)
			break;
		cnt++;
	}
	if (cnt == 3)
		return true;

	else
		return false;
}


int winCheck(int arr[][7])	// 0:: not yet finished ,  (1 or 2) winner , 3 draw
{
	int i,j;
	int stone = 0;
	int check = 0;
	for (i = 0; i < 7; i++)
	{
		check = 0;
		stone = arr[0][i];
		if (stone == 0)
			continue;

		for (j = 1; j < 4; j++)
			if (arr[j][i] != stone)
				check = -1;
		if (check == 0 && arr[4][i] != stone)
			return stone;

		check = 0;
		stone = arr[1][i];
		if (stone == 0)
			continue;

		for (j = 2; j < 5; j++)
			if (arr[j][i] != stone)
				check = -1;
		if (check == 0 && arr[5][i] != stone && arr[0][i] != stone)
			return stone;

		check = 0;
		stone = arr[2][i];
		if (stone == 0)
			continue;

		for (j = 3; j < 6; j++)
			if (arr[j][i] != stone)
				check = -1;
		if (check == 0 && arr[1][i] != stone)
			return stone;
	}

	for (i = 0; i < 6; i++)
	{
		if (sub_check(arr, i))
			return arr[i][3];
	}

	for (i = 0; i < 6; i++)
		for (j = 0; j < 7; j++)
			if (arr[i][j] == 0)
				return 0;
	
	return 3;



}//	05/03 21:41		by Jongmin


// --> 2017/05/03 15:19 세로로 연속된 3개가 있는지 체크
int column_check(int arr[][7], int x, int y, int who) {

	int i;
	int count = 0;

	for (i = y; i >= 0; i--) {
		if (arr[i][x] == who)
			count++;
		else if (arr[i][x] != who)
			return 0;

		if (count == 3)
			return 2000;
	}

	/*
	count = 0;

	for (i = y; i >= 0; i--) {
		if (arr[i][x] == 2)
			count++;
		else if (arr[i][x] == 1)
			return 0;

		if (count == 3)
			return 1000;
	}
	*/

	return 0;
} // <-- 2017/05/03 15:19 세로로 연속된 3개가 있는지 체크 by JeongIn. 

void winnerPrint(int first, int winCheck)
{
	printf("\n\n");
	
	if (winCheck == 3)
		printf("!!  Draw !!\n\n");
	else if (winCheck == 1)
		printf("Connect-Go win\n\n");
	else
		printf("Connect-GO resign\n\n");
}// 04/06 23:14		by Jongmin



//connect Go :: in board :: '1'
void Do_by_condition(int arr[][7])	//condition module by Jongmin
{
	int yindex[7] = { -1 };
	int score[7] = { -1 };

	int i, j;
	for (i = 0; i < 7; i++) //i :: x index
	{
		for (j = 0; j < 6; j++)
		{
			if (arr[j][i] == 0)
			{
				yindex[i] = j;
				break;
			}
		}
	} // if yindex :: -1 -> that line don't have empty position
	//find which position can be done

	for (i = 0; i < 7; i++)
	{
		if (yindex[i] == -1)
			continue;
		else
		{
			



		}
	}



}


int row_check(int arr[][7], int x, int y)	//check whether this position make win or not by 'row - 4'  //Jongmin
{
	int cnt = 0;
	int i, j;
	for (i = x+1; i < 7; i++)
	{
		if (arr[y][i] == 1)
		{
			cnt++;
		}
		else
			break;
	}
	for (i = x - 1; i >= 0; i--)
	{
		if (arr[y][i] == 1)
		{
			cnt++;
		}
		else
			break;
	}

	if (cnt == 3)
		return 2000;
	
	cnt = 0;

	for (i = x + 1; i < 7; i++)
	{
		if (arr[y][i] == 1)
		{
			cnt++;
		}
		else
			break;
	}
	for (i = x - 1; i >= 0; i--)
	{
		if (arr[y][i] == 1)
		{
			cnt++;
		}
		else
			break;
	}

	if (cnt == 3)
		return 1000;
	else
		return 0;
}


int diagonal_check(int arr[][7], int x, int y)		//check whether this position make win or not by 'diagonal - 4'			//Jongmin 
{
	int i;
	int cnt = 0;
	for (i = 1; i < 4; i++)				//first, check like '/'
	{
		if (y + i > 5 || x + i > 6)
			break;
		if (arr[y + i][x + i] == 1)
			cnt++;
		else
			break;
	}
	for (i = 1; i < 4; i++)				//first, check like '/'
	{
		if (y - i < 0 || x - i < 0)
			break;
		if (arr[y - i][x - i] == 1)
			cnt++;
		else
			break;
	}

	if (cnt == 3)
		return 2000;

	cnt = 0;
	for (i = 1; i < 4; i++)				//second, check like '| :: reverse /'
	{
		if (y - i < 0 || x + i > 6)
			break;
		if (arr[y - i][x + i] == 1)
			cnt++;
		else
			break;
	}
	for (i = 1; i < 4; i++)				//second, check like '| :: reverse /'
	{
		if (y + i > 5 || x - i < 0)
			break;
		if (arr[y + i][x - i] == 1)
			cnt++;
		else
			break;
	}

	if (cnt == 3)
		return 2000;



	//opositie check
	cnt = 0;
	for (i = 1; i < 4; i++)				//first, check like '/'
	{
		if (y + i > 5 || x + i > 6)
			break;
		if (arr[y + i][x + i] == 2)
			cnt++;
		else
			break;
	}
	for (i = 1; i < 4; i++)				//first, check like '/'
	{
		if (y - i < 0 || x - i < 0)
			break;
		if (arr[y - i][x - i] == 2)
			cnt++;
		else
			break;
	}
	if (cnt == 3)
		return 1000;

	cnt = 0;
	for (i = 1; i < 4; i++)				//second, check like '| :: reverse /'
	{
		if (y - i < 0 || x + i > 6)
			break;
		if (arr[y - i][x + i] == 2)
			cnt++;
		else
			break;
	}
	for (i = 1; i < 4; i++)				//second, check like '| :: reverse /'
	{
		if (y + i > 5 || x - i < 0)
			break;
		if (arr[y + i][x - i] == 2)
			cnt++;
		else
			break;
	}

	if (cnt == 3)
		return 1000;
	else
		return 0;
}

// - > 2017/05/03 16:30 by JeongIn 
// check 5 stone
int fiveStone(int arr[][7], int x, int y, int who) {

	bool check = false;

	if (x > 0 && x < 6) {

		if (x < 4) { // 1,2,3
			if (arr[y][x - 1] == who && arr[y][x + 1] == who && arr[y][x + 2] == who && arr[y][x + 3] == who)
				check = true;

			if (y == 1 || y == 2) { //positive diagonal
				if (arr[y - 1][x - 1] == who && arr[y + 1][x + 1] == who && arr[y + 2][x + 2] == who && arr[y + 3][x + 3] == who)
					check = true;
			}

			if (y == 3 || y == 4) { //negative diagonal
				if (arr[y + 1][x - 1] == who && arr[y - 1][x + 1] == who && arr[y - 2][x + 2] == who && arr[y - 3][x + 3] == who)
					check = true;
			}
		}

		if (x > 1 && x < 5) { // 2,3,4
			if (arr[y][x - 2] == who && arr[y][x - 1] == who && arr[y][x + 1] == who && arr[y][x + 2] == who)
				check = true;

			if (y == 2 || y == 3 || y == 4) { 
				//positive diagonal
				if (arr[y - 2][x - 2] == who && arr[y - 1][x - 1] == who && arr[y + 1][x + 1] == who && arr[y + 2][x + 2] == who)
					check = true;
			
				//negative diagonal
				if (arr[y + 2][x - 2] == who && arr[y + 1][x - 1] == who && arr[y - 1][x + 1] == who && arr[y - 2][x + 2] == who)
					check = true;
			}

		}

		if (x > 2) { // 3,4,5
			if (arr[y][x - 3] == who && arr[y][x - 2] == who && arr[y][x - 1] == who && arr[y][x + 1] == who)
				check = true;

			if (y == 3 || y == 4) { //positive diagonal
				if (arr[y - 3][x - 3] == who && arr[y - 2][x - 2] == who && arr[y - 1][x - 1] == who && arr[y + 1][x + 2] == who)
					check = true;
			}

			if (y == 1 || y == 2) { //negative diagonal
				if (arr[y + 3][x - 3] == who && arr[y + 2][x - 2] == who && arr[y + 1][x - 1] == who && arr[y - 1][x + 2] == who)
					check = true;
			}
		}

	}

	if (check == true) {
		if (who == 1)
			return -1000;

		if (who == 2)
			return -1000;
	}

}
// < - 2017/05/03 16:30 by JeongIn