#include <stdio.h>
#include <stdbool.h>

//initialize functions
void print_board(int board[][7]);
void push(int board[][7], int turn);
bool sub_check(int arr[][7], int x, int y);
//bool sub_check(int arr[][7], int y);
int winCheck(int arr[][7]);
void winnerPrint(int first, int winCheck);
void Do_by_condition(int arr[][7]);
int fiveStone(int arr[][7], int x, int y, int who);

int check_make_four(int arr[][7], int x, int y, int who);	//simple check by Jongmin
int row_check_make_four(int arr[][7], int x, int y, int who);	//it can be 4 through row
int diagonal_check_make_four(int arr[][7], int x, int y, int who);		//check whether this position make win or not by 'diagonal - 4'			//Jongmin 
int column_check_make_four(int arr[][7], int x, int y, int who); // 세로로 연속된 3개가 있는지 체크

int check_make_three(int arr[][7], int x, int y, int who);
int row_check_make_three(int arr[][7], int x, int y, int who); // 가로로 연속된 3개를 만들 수 있는지 체크
int diagonal_check_make_three(int arr[][7], int x, int y, int who); // '／'대각선 연속된 3개를 만들 수 있는지 체크
int negative_diagonal_check_make_three(int arr[][7], int x, int y, int who); // '＼'대각선 연속된 3개를 만들 수 있는지 체크
int row_check_make_three_but_onesidebarrier(int arr[][7], int x, int y, int who);
int column_check_make_three(int arr[][7], int x, int y, int who);


int check_make_two(int arr[][7], int x, int y, int who);
int column_check_make_two(int arr[][7], int x, int y, int who);		
int row_check_make_two(int arr[][7], int x, int y, int who);
int diagonal_check_make_two(int arr[][7], int x, int y, int who); // '／'대각선 연속된 2개를 만들 수 있는지 체크
int negative_diagonal_check_make_two(int arr[][7], int x, int y, int who); // '＼'대각선 연속된 2개를 만들 수 있는지 체크

int is_only_center(int arr[][7]);

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
	int methods = 0;
	while (winner == 0)
	{
		printf("Which method ( 1. by algorithm  2. by condition  3. by push )\n");
		scanf_s("%d", &methods);
		if (methods == 3)
			push(board, first + (turn++));
		//else if(methods == 1)

		else if (methods == 2)
		{
			Do_by_condition(board);
			turn++;
		}
		else
		{
			printf("wrong methods\n");
			continue;
		}
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
			push(board, turn);
			return;
		}
	}
	board[height][num] = (turn % 2) + 1;	

}//4.06 21:46 JH


//// delete this sentence.. when 5 connected , it means win.. -> some problem ..when it is connected five.. so develope more..
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


//bool sub_check(int arr[][7], int y)		//redevelope subcheck by Jongmin ->but, when 5connected, it means win , so re, redevelope
//{
//	int i;
//	int cnt = 0;
//	int stone = arr[y][3];
//
//	for (i = 1; i < 4; i++)		//win, row case
//	{
//		if (arr[y][3 + i] != stone)
//			break;
//		cnt++;
//	}
//	for (i = 1; i < 4; i++)
//	{
//		if (arr[y][3 - i] != stone)
//			break;
//		cnt++;
//	}
//	if (cnt == 3)
//		return true;
//	cnt = 0;
//	
//	for (i = 1; i < 4; i++)		//win , '/' diagonal
//	{
//		if (y + i > 5)
//			break;
//
//		if (arr[y + i][3 + i] != stone)
//			break;
//		cnt++;
//	}
//	for (i = 1; i < 4; i++)
//	{
//		if (y - i < 0)
//			break;
//
//		if (arr[y - i][3 - i] != stone)
//			break;
//		cnt++;
//	}
//	if (cnt == 3)
//		return true;
//	cnt = 0;
//
//	for (i = 1; i < 4; i++)			//win , 'reverse / ' diagonal
//	{
//		if (y + i > 5)
//			break;
//
//		if (arr[y + i][3 - i] != stone)
//			break;
//		cnt++;
//	}
//	for (i = 1; i < 4; i++)
//	{
//		if (y - i < 0)
//			break;
//
//		if (arr[y - i][3 + i] != stone)
//			break;
//		cnt++;
//	}
//	if (cnt == 3)
//		return true;
//
//	else
//		return false;
//}


//int winCheck(int arr[][7])	// 0:: not yet finished ,  (1 or 2) winner , 3 draw
//{
//	int i,j;
//	int stone = 0;
//	int check = 0;
//	for (i = 0; i < 7; i++)
//	{
//		check = 0;
//		stone = arr[0][i];
//		if (stone == 0)
//			continue;
//
//		for (j = 1; j < 4; j++)
//			if (arr[j][i] != stone)
//				check = -1;
//		if (check == 0 && arr[4][i] != stone)
//			return stone;
//
//		check = 0;
//		stone = arr[1][i];
//		if (stone == 0)
//			continue;
//
//		for (j = 2; j < 5; j++)
//			if (arr[j][i] != stone)
//				check = -1;
//		if (check == 0 && arr[5][i] != stone && arr[0][i] != stone)
//			return stone;
//
//		check = 0;
//		stone = arr[2][i];
//		if (stone == 0)
//			continue;
//
//		for (j = 3; j < 6; j++)
//			if (arr[j][i] != stone)
//				check = -1;
//		if (check == 0 && arr[1][i] != stone)
//			return stone;
//	}
//
//	for (i = 0; i < 6; i++)
//	{
//		if (sub_check(arr, i))
//			return arr[i][3];
//	}
//
//	for (i = 0; i < 6; i++)
//		for (j = 0; j < 7; j++)
//			if (arr[i][j] == 0)
//				return 0;
//	
//	return 3;
//
//
//
//}//	05/03 21:41		by Jongmin


// --> 2017/05/03 15:19 세로로 연속된 3개가 있는지 체크
int column_check_make_four(int arr[][7], int x, int y, int who) {

	int i;
	int count = 0;

	for (i = y - 1; i >= 0; i--) {		//modify Jongmin , more check needed
		if (arr[i][x] == who)
			count++;
		else if (arr[i][x] != who)
			return 0;

		if (count == 3)
			return 500000;
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





int row_check_make_four(int arr[][7], int x, int y, int who)	//check whether this position make win or not by 'row - 4'  //Jongmin
{
	int cnt = 0;
	int i = 0;
	int j = 0;
	for (i = x+1; i < 7; i++)
	{
		if (arr[y][i] == who)
		{
			cnt++;
		}
		else
			break;
	}
	for (i = x - 1; i >= 0; i--)
	{
		if (arr[y][i] == who)
		{
			cnt++;
		}
		else
			break;
	}

	if (cnt >= 3)		//change for 5connected
		return 500000;
	else
		return 0;
}


int diagonal_check_make_four(int arr[][7], int x, int y, int who)		//check whether this position make win or not by 'diagonal - 4'			//Jongmin 
{
	int i;
	int cnt = 0;
	for (i = 1; i < 4; i++)				//first, check like '/'
	{
		if (y + i > 5 || x + i > 6)
			break;
		if (arr[y + i][x + i] == who)
			cnt++;
		else
			break;
	}
	for (i = 1; i < 4; i++)				//first, check like '/'
	{
		if (y - i < 0 || x - i < 0)
			break;
		if (arr[y - i][x - i] == who)
			cnt++;
		else
			break;
	}

	if (cnt >= 3)		//change for 5connected
		return 500000;

	cnt = 0;
	for (i = 1; i < 4; i++)				//second, check like '| :: reverse /'
	{
		if (y - i < 0 || x + i > 6)
			break;
		if (arr[y - i][x + i] == who)
			cnt++;
		else
			break;
	}
	for (i = 1; i < 4; i++)				//second, check like '| :: reverse /'
	{
		if (y + i > 5 || x - i < 0)
			break;
		if (arr[y + i][x - i] == who)
			cnt++;
		else
			break;
	}

	if (cnt >= 3)
		return 500000;
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

	return 0;
}
// < - 2017/05/03 16:30 by JeongIn


int check_make_four(int arr[][7], int x, int y, int who)	//simple check by Jongmin
{
	return (column_check_make_four(arr, x, y, who) + diagonal_check_make_four(arr, x, y, who) + row_check_make_four(arr, x, y, who));
}


int row_check_make_three_but_onesidebarrier(int arr[][7], int x, int y, int who)
{
	int enm = 1;
	if (who == 1)
		enm = 2;


	if (x >= 0 && x < 4) // 0 1 2 3 
	{
		if (x == 0)
		{
			if (arr[y][x + 1] == who && arr[y][x + 2] == who && arr[y][x + 3] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][x + 3] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be difensed
				{
					return 500;
				}
			}
		}
		else
		{
			if (arr[y][x-1] ==enm && arr[y][x + 1] == who && arr[y][x + 2] == who && arr[y][x + 3] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][x + 3] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be difensed
				{
					return 500;
				}
			}
		}
	}
	if (x >= 1 && x < 5) // 1 2 3 4
	{
		if (x == 1)
		{
			if (arr[y][0] == who && arr[y][2] == who && arr[y][3] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be difensed
				{
					return 500;
				}
			}
		}
		else
		{
			if (arr[y][x - 2] == enm && arr[y][x - 1] == who && arr[y][x + 1] == who && arr[y][x + 2] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][x + 2] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be difensed
				{
					return 500;
				}
			}
		}
	}
	if (x >= 2 && x < 6) // 2 3 4 5
	{
		if (x == 2)
		{
			if (arr[y][0] == who && arr[y][1] == who && arr[y][3] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be difensed
				{
					return 500;
				}
			}
		}
		else
		{
			if (arr[y][x - 3] == enm && arr[y][x - 2] == who && arr[y][x - 1] == who && arr[y][x + 1] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][x + 1] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be difensed
				{
					return 500;
				}
			}
		}
	}

	//case 2


	if (x >= 1 && x < 5)	// 1 2 3 4
	{
		if (x == 4)
		{
			if (arr[y][3] == 0 && arr[y][5] == who && arr[y][6] == who)
			{
				if (y > 0)
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else return 500;
				}
				else
					return 500;
			}
		}
		else
		{
			if (arr[y][x - 1] == 0 && arr[y][x + 1] == who && arr[y][x + 2] == who && arr[y][x + 3] == enm)
			{
				if (y > 0)
				{
					if (arr[y][x - 1] == 0)
						return 1000;
					else
						return 500;
				}
				else
					return 500;
			}
		}
	}
	if (x >= 2 && x < 6)
	{
		if (x == 5)
		{
			if (arr[y][3] == 0 && arr[y][4] == who && arr[y][6] == who)
			{
				if (y > 0)
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else return 500;
				}
				else
					return 500;
			}
		}
		else
		{
			if (arr[y][x - 2] == 0 && arr[y][x - 1] == who && arr[y][x + 1] == who && arr[y][x + 2] == enm)
			{
				if (y > 0)
				{
					if (arr[y][x - 2] == 0)
						return 1000;
					else
						return 500;
				}
				else
					return 500;
			}
		}
	}

	if (x >= 3 && x < 7)	// 3 4 5 6
	{
		if (x == 6)
		{
			if (arr[y][3] == 0 && arr[y][4] == who && arr[y][5] == who)
			{
				if (y > 0)
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else return 500;
				}
				else
					return 500;
			}
		}
		else
		{
			if (arr[y][x - 3] == 0 && arr[y][x - 2] == who && arr[y][x - 1] == who && arr[y][x + 1] == enm)
			{
				if (y > 0)
				{
					if (arr[y][x - 3] == 0)
						return 1000;
					else
						return 500;
				}
				else
					return 500;
			}
		}
	}

	return 0;
}


// - > 가로로 연속된 3개를 만들 수 있는지 체크 By JeongIn
int row_check_make_three(int arr[][7], int x, int y, int who) { // 가로로 연속된 3개를 만들 수 있는지 체크

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int R_wall = 1;
	int R_support = 1;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) { // 왼쪽

		if (arr[y][x - i] == who) {
			count++;
		}
		else if (arr[y][x - i] == enemy)
			break;
		else if (arr[y][x - i] == 0){
			L_wall = 0;
			if (y - 1 >= 0) {
				if (arr[y - 1][x - i] == 0)
					L_support = 0;
			}
			break;
		}
	}

	for (i = 1; i <= 6 - x; i++) { // 오른쪽

		if (arr[y][x + i] == who) {
			count++;
		}
		else if (arr[y][x + i] == enemy)
			break;
		else if (arr[y][x + i] == 0){
			R_wall = 0;
			if (y - 1 >= 0) {
				if (arr[y - 1][x + i] == 0)
					R_support = 0;
			}
			break;
		}
	}

	if (count == 2) {

		if (L_wall == 0 && R_wall == 0) {
			if (L_support == 1 && R_support == 1)
				return 10000;
			else if (L_support == 0 && R_support == 0)
				return 2000;
			else
				return 1000;
		}
		else if (L_wall == 0) {
			if (L_support == 1)
				return 1000;
			else
				return 500;
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 1000;
			else
				return 500;
		}
		else
			return 0;
	}

	return 0;

} // < - 가로로 연속된 3개를 만들 수 있는지 체크 By JeongIn


// - > '／' 대각선 연속된 3개를 만들 수 있는지 체크 By JeongIn
int diagonal_check_make_three(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int R_wall = 1;
	int R_support = 1;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) {
		if (y - i < 0)
			break;

		if (arr[y - i][x - i] == who) {
			count++;
		}
		else if (arr[y - i][x - i] == enemy)
			break;
		else if (arr[y - i][x - i] == 0) {
			L_wall = 0;
			if (y - i - 1 >= 0) {
				if (arr[y - i - 1][x - i] == 0)
					L_support = 0;
			}
			break;
		}
	}

	for (i = 1; i <= 6 - x; i++) {
		if (y + i > 5)
			break;

		if (arr[y + i][x + i] == who) {
			count++;
		}
		else if (arr[y + i][x + i] == enemy)
			break;
		else if (arr[y + i][x + i] == 0) {
			R_wall = 0;
			if (arr[y + i - 1][x + i] == 0)
				R_support = 0;
			break;
		}
	}

	if (count == 2) {

		if (L_wall == 0 && R_wall == 0) {
			if (L_support == 1 && R_support == 1)
				return 10000;
			else if (L_support == 0 && R_support == 0)
				return 2000;
			else
				return 1000;
		}
		else if (L_wall == 0) {
			if (L_support == 1)
				return 1000;
			else
				return 500;
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 1000;
			else
				return 500;
		}
		else
			return 0;
	}

	return 0;

} // < - '／' 대각선 연속된 3개를 만들 수 있는지 체크 By JeongIn


  // - > '＼' 대각선 연속된 3개를 만들 수 있는지 체크 By JeongIn
int negative_diagonal_check_make_three(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int R_wall = 1;
	int R_support = 1;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) {
		if (y + i > 5)
			break;

		if (arr[y + i][x - i] == who) {
			count++;
		}
		else if (arr[y + i][x - i] == enemy)
			break;
		else if (arr[y + i][x - i] == 0) {
			L_wall = 0;
			if (arr[y + i - 1][x - i] == 0)
				L_support = 0;
			break;
		}
	}

	for (i = 1; i <= 6 - x; i++) {
		if (y - i < 0)
			break;

		if (arr[y - i][x + i] == who) {
			count++;
		}
		else if (arr[y - i][x + i] == enemy)
			break;
		else if (arr[y - i][x + i] == 0) {
			R_wall = 0;
			if (y - i - 1 >= 0) {
				if (arr[y - i - 1][x + i] == 0)
					R_support = 0;
			}
			break;
		}
	}

	if (count == 2) {

		if (L_wall == 0 && R_wall == 0) {
			if (L_support == 1 && R_support == 1)
				return 10000;
			else if (L_support == 0 && R_support == 0)
				return 2000;
			else
				return 1000;
		}
		else if (L_wall == 0) {
			if (L_support == 1)
				return 1000;
			else
				return 500;
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 1000;
			else
				return 500;
		}
		else
			return 0;
	}

	return 0;

} // < - '＼' 대각선 연속된 3개를 만들 수 있는지 체크 By JeongIn


int column_check_make_three(int arr[][7], int x, int y, int who)	//simple implementation by Jongmin
{
	int i;
	int cnt = 0;
	for (i = y - 1; i >= 0; i--)
	{
		if (arr[i][x] == who)
			cnt++;
		else
			break;
	}
	if (cnt == 2)
		return 500;
	else
		return 0;
}


int check_make_three(int arr[][7], int x, int y, int who)	//control by Jongmin
{
	return(column_check_make_three(arr, x, y, who) + row_check_make_three(arr, x, y, who) + row_check_make_three_but_onesidebarrier(arr, x, y, who) + diagonal_check_make_three(arr, x, y, who) + negative_diagonal_check_make_three(arr, x, y, who));
}


int column_check_make_two(int arr[][7], int x, int y, int who)		//Jongmin
{
	int cnt = 0;
	int i = 0;
	if (y == 1)
	{
		if (arr[0][x] == who)
			return 50;
	}
	if (y > 1)
	{
		if (arr[y - 1][x] == who && arr[y - 2][x] != who)			//for checking not to give double point when connected three
			return 50;
	}

	return 0;
}


//need revision
int row_check_make_two(int arr[][7], int x, int y, int who)		//big examination... by Jongmin
{
	int enm = 2;
	if (who == 2)
		enm = 1;

	switch (x)
	{
	case 0:
		if (arr[y][1] == who && arr[y][2] != who ) //arr[y][2]!=who means, do not give double point when 3 connected
		{
			if (arr[y][2] == enm || arr[y][3] == enm)
				return 0;

			if (arr[y][3] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][2] == 0)
						return 1000;
					else
						return 500;
				}
			}
			else
				return 100;
		}
		break;
	case 1:
	{
		if (arr[y][0] == who && arr[y][2] != who)
		{
			if (arr[y][2] == enm || arr[y][3] == enm)
				return 0;

			if (arr[y][3] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][2] == 0)
						return 1000;
					else
						return 500;
				}
			}
			else
				return 100;
		}
		if (arr[y][2] == who && arr[y][0] != who)
		{
			if (arr[y][0] == enm)
			{
				if (arr[y][3] == enm || arr[y][4] == enm)
					return 0;

				if (arr[y][4] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][3] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 100;
			}
			else
			{
				if (arr[y][3] == enm)
					return 0;
				
				if (arr[y][4] == enm)
					return 150;

				if (arr[y][4] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][3] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 300;
			}
		}
	}
		break;
	case 2:
		if (arr[y][1] == who && arr[y][3] != who)
		{
			if (arr[y][3] == enm)
				return 0;
			if (arr[y][0] == enm)
			{
				if (arr[y][4] == enm)
					return 0;

				if (arr[y][4] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][3] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 150;
			}
			else if (arr[y][0] == 0)
			{
				if (arr[y][4] == enm)
					return 150;
				if (arr[y][4] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][3] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 300;
			}
		}
		if (arr[y][3] == who && arr[y][1] != who)
		{
			if (arr[y][1] == enm || arr[y][4] == enm)
				return 0;
			if (arr[y][0] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][1] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if (arr[y][5] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][4] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if (arr[y][0] == enm)
				return 150;
			if (arr[y][5] == enm)
				return 150;

			return 300;
		}

		break;
	case 3:
		if (arr[y][2] == who && arr[y][4] != who)
		{
			if (arr[y][1] == enm && arr[y][4] == enm)
				return 0;

			if (arr[y][1] == enm)
			{
				if (arr[y][4] == enm || arr[y][5] == enm)
					return 0;
				if (arr[y][5] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][4] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 100;
			}
			else if (arr[y][4] == enm)
			{
				if (arr[y][0] == enm)
					return 0;
				if (arr[y][0] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][1] == 0)
							return 1000;
						else
							return 500;
					}
				}

				return 100;
			}
			if (arr[y][0] == who && arr[y][4] != who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][1] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if (arr[y][5] == who && arr[y][1] != who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][4] == 0)
						return 1000;
					else
						return 500;
				}
			}

			return 300;
		}
		else if (arr[y][4] == who)
		{
			if (arr[y][2] == enm && arr[y][5] == enm)
				return 0;

			if (arr[y][2] == enm)
			{
				if (arr[y][6] == enm)
					return 0;
				if (arr[y][6] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][5] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 100;
			}
			else if (arr[y][5] == enm)
			{
				if (arr[y][1] == enm)
					return 0;

				if (arr[y][1] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][2] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 100;
			}
			if (arr[y][1] == who && arr[y][5] != who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][2] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if (arr[y][6] == who && arr[y][2] != who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][5] == 0)
						return 1000;
					else
						return 500;
				}
			}

			return 300;
		}
		break;
	case 4:
		if (arr[y][3] == who && arr[y][5] != who)
		{
			if (arr[y][5] == enm && arr[y][2] == enm)
				return 0;
			if (arr[y][2] == enm)
			{
				if (arr[y][6] == enm)
					return 0;

				if (arr[y][6] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][5] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 100;
			}
			
			if (arr[y][5] == enm)
			{
				if (arr[y][1] == enm)
					return 0;
				if (arr[y][1] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][2] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 100;
			}
			if (arr[y][1] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][2] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if (arr[y][6] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][5] == 0)
						return 1000;
					else
						return 500;
				}
			}


			if (arr[y][6] == enm || arr[y][1] == enm)
				return 150;

			return 300;
		}
		if (arr[y][5] == who && arr[y][3] != who)
		{
			if (arr[y][3] == enm)
				return 0;
			if (arr[y][6] == enm)
			{
				if (arr[y][2] == enm)
					return 0;
				if (arr[y][2] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][3] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 150;
			}
			if (arr[y][2] == who && arr[y][6] != who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if (arr[y][2] == enm)
				return 100;

			return 150;
		}
		break;
	case 5:
		if (arr[y][4] == who && arr[y][6] != who)
		{
			if (arr[y][3] == enm)
				return 0;
			if (arr[y][6] == enm)
			{
				if (arr[y][2] == enm)
					return 0;
				if (arr[y][2] == who)
				{
					if (y == 0)
						return 500;
					else
					{
						if (arr[y - 1][3] == 0)
							return 1000;
						else
							return 500;
					}
				}
				return 150;
			}
			if (arr[y][2] == who && arr[y][6] != who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][3] == 0)
						return 1000;
					else
						return 500;
				}
			}
			if(arr[y][2] == enm)
				return 150;
			return 300;

		}
		if (arr[y][6] == who && arr[y][4] != who)
		{
			if (arr[y][4] == enm || arr[y][3] == enm)
				return 0;
			if (arr[y][3] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][4] == 0)
						return 1000;
					else
						return 500;
				}
			}

			return 150;
		}
		break;
	case 6:
		if (arr[y][5] == who)
		{
			if (arr[y][3] == enm || arr[y][4] == enm)
				return 0;
			if (arr[y][3] == who)
			{
				if (y == 0)
					return 500;
				else
				{
					if (arr[y - 1][4] == 0)
						return 1000;
					else
						return 500;
				}
			}
			return 150;
		}
		break;
	}

	return 0;
}   


// - > '／'대각선 연속된 2개를 만들 수 있는지 체크 By JeongIn
int diagonal_check_make_two(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int L_three = 0;
	int R_wall = 1;
	int R_support = 1;
	int R_three = 0;
	int L_x = x;
	int R_x = x;
	int L_w_x = -1;
	int R_w_x = 7;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) {
		if (y - i < 0)
			break;

		if (arr[y - i][x - i] == who && L_wall == 1) {
			L_w_x = x - i - 1;
			L_x = x - i;
			count++;
		}
		else if (arr[y - i][x - i] == enemy) {
			L_w_x = x - i;
			break;
		}
		else if (arr[y - i][x - i] == 0) {
			L_w_x = x - i - 1;
			L_wall = 0;
			if (y - i - 1 >= 0 && x - i == L_x - 1) {
				if (arr[y - i - 1][x - i] == 0)
					L_support = 0;

				if (x - i - 1 >= 0) {
					if (arr[y - i - 1][x - i - 1] == who) {
						L_three = 1;
						L_w_x = x - i - 2;
					}
				}
			}
		}
	}

	for (i = 1; i <= 6 - x; i++) {
		if (y + i > 5)
			break;

		if (arr[y + i][x + i] == who && R_wall == 1) {
			R_w_x = x + i + 1;
			R_x = x + i;
			count++;
		}
		else if (arr[y + i][x + i] == enemy) {
			R_w_x = x + i;
			break;
		}
		else if (arr[y + i][x + i] == 0) {
			R_w_x = x + i + 1;
			R_wall = 0;
			if (arr[y + i - 1][x + i] == 0 && x + i == R_x + 1)
				R_support = 0;

			if (x + i + 1 <= 6 && y + i + 1 <= 5 && x + i == R_x + 1) {
				if (arr[y + i + 1][x + i + 1] == who) {
					R_three = x + i + 1;
					R_w_x = x + i + 2;
				}
			}
		}
	}

	int length = R_w_x - L_w_x - 1;

	if (count == 1) {

		if (length < 4)
			return 0;

		if (L_three == 1 && R_three == 1) {
			if (L_support == 1 && R_support == 1)
				return 10000;
			else if (L_support == 0 && R_support == 0)
				return 2000;
			else
				return 1000;
		}
		else if (L_three == 1) {
			if (L_support == 1)
				return 1000;
			else
				return 500;
		}
		else if (R_three == 1) {
			if (R_support == 1)
				return 1000;
			else
				return 500;
		}

		if (L_wall == 0 && R_wall == 0) {
			if (L_support == 1 && R_support == 1) {
				if (length == 4) {
					return 150;
				}
				else if (length == 5) {
					return 200;
				}
				else if (length == 6) {
					return 250;
				}
			}
			else if (L_support == 0 && R_support == 0) {
				if (length == 4) {
					return 200;
				}
				else if (length == 5) {
					return 250;
				}
				else if (length == 6) {
					return 300;
				}
			}
			else {
				if (length == 4) {
					return 100;
				}
				else if (length == 5) {
					return 150;
				}
				else if (length == 6) {
					return 200;
				}
			}
		}
		else if (L_wall == 0) {
			if (L_support == 1) {
				return 100;
			}
			else {
				return 150;
			}
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 100;
			else
				return 150;
		}
		else
			return 0;
	}

	return 0;

}
// < - '／'대각선 연속된 2개를 만들 수 있는지 체크 By JeongIn


// - > '＼'대각선 연속된 2개를 만들 수 있는지 체크 By JeongIn
int negative_diagonal_check_make_two(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int L_three = 0;
	int R_wall = 1;
	int R_support = 1;
	int R_three = 0;
	int L_x = x;
	int R_x = x;
	int L_w_x = -1;
	int R_w_x = 7;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) {
		if (y + i > 5)
			break;

		if (arr[y + i][x - i] == who) {
			L_w_x = x - i - 1;
			L_x = x - i;
			count++;
		}
		else if (arr[y + i][x - i] == enemy) {
			L_w_x = x - i;
			break;
		}
		else if (arr[y + i][x - i] == 0) {
			L_w_x = x - i - 1;
			L_wall = 0;

			if (arr[y + i - 1][x - i] == 0 && x - i == L_x - 1)
				L_support = 0;

			if (x - i - 1 >= 0 && y + i + 1 <= 5 && x - i == L_x - 1) {
				if (arr[y + i + 1][x - i - 1] == who) {
					L_three = 1;
					L_w_x = x - i - 2;
				}
			}
		}
	}

	for (i = 1; i <= 6 - x; i++) {
		if (y - i < 0)
			break;

		if (arr[y - i][x + i] == who) {
			R_w_x = x + i + 1;
			R_x = x + i;
			count++;
		}
		else if (arr[y - i][x + i] == enemy) {
			R_w_x = x + i;
			break;
		}
		else if (arr[y - i][x + i] == 0) {
			R_w_x = x + i + 1;
			R_wall = 0;
			if (y - i - 1 >= 0 && x + i == R_x + 1) {
				if (arr[y - i - 1][x + i] == 0)
					R_support = 0;

				if (x + i + 1 <= 6) {
					if (arr[y - i - 1][x + i + 1] == who) {
						R_three = x + i + 1;
						R_w_x = x + i + 2;
					}
				}
			}
		}
	}

	int length = R_w_x - L_w_x - 1;

	if (count == 1) {

		if (length < 4)
			return 0;

		if (L_three == 1 && R_three == 1) {
			if (L_support == 1 && R_support == 1)
				return 10000;
			else if (L_support == 0 && R_support == 0)
				return 2000;
			else
				return 1000;
		}
		else if (L_three == 1) {
			if (L_support == 1)
				return 1000;
			else
				return 500;
		}
		else if (R_three == 1) {
			if (R_support == 1)
				return 1000;
			else
				return 500;
		}

		if (L_wall == 0 && R_wall == 0) {
			if (L_support == 1 && R_support == 1) {
				if (length == 4) {
					return 150;
				}
				else if (length == 5) {
					return 200;
				}
				else if (length == 6) {
					return 250;
				}
			}
			else if (L_support == 0 && R_support == 0) {
				if (length == 4) {
					return 200;
				}
				else if (length == 5) {
					return 250;
				}
				else if (length == 6) {
					return 300;
				}
			}
			else {
				if (length == 4) {
					return 100;
				}
				else if (length == 5) {
					return 150;
				}
				else if (length == 6) {
					return 200;
				}
			}
		}
		else if (L_wall == 0) {
			if (L_support == 1) {
				return 100;
			}
			else {
				return 150;
			}
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 100;
			else
				return 150;
		}
		else
			return 0;
	}

	return 0;

}
// < - '＼'대각선 연속된 2개를 만들 수 있는지 체크 By JeongIn


int check_make_two(int arr[][7], int x, int y, int who)
{
	return (row_check_make_two(arr,x,y,who) + column_check_make_two(arr,x,y,who) + diagonal_check_make_two(arr,x,y,who) + negative_diagonal_check_make_two(arr,x,y,who) );
}
// To do things
/*
1. make three score balancing

*/

int is_only_center(int arr[][7])	//for only one line			//by Jongmin
{
	if (arr[0][0] == 0 && arr[0][1] == 0 && arr[0][2] == 0 && arr[0][4] == 0 && arr[0][5] == 0 && arr[0][6] == 0)
	{
		if (arr[4][3] == 0)
			return 1000;
	}
	
		return 0;
}


//connect Go :: in board :: '1'
void Do_by_condition(int arr[][7])	//condition module by Jongmin
{
	int yindex[7] = { -1,-1,-1,-1,-1,-1,-1 };
	int score[7] = { -1,-1,-1,-1,-1,-1,-1 };
	int maxIndex = 0;
	int maxScore = 0;
	int tempscore = 0;
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
			tempscore = check_make_four(arr, i, yindex[i], 1);
			if (tempscore > 10000)
			{
				arr[yindex[i]][i] = 1;
				return;
			}
			else
			{
				score[i] = tempscore;
			}
			score[i] += check_make_three(arr, i, yindex[i], 1);
			score[i] += check_make_two(arr, i, yindex[i], 1);

			tempscore = check_make_four(arr, i, yindex[i], 2) / 10;
			if (tempscore > 10000)
			{
				arr[yindex[i]][i] = 1;
				return;
			}
			else
			{
				score[i] += tempscore;
			}

			score[i] += check_make_three(arr, i, yindex[i], 2);
			score[i] += check_make_two(arr, i, yindex[i], 2);

			if (yindex[i] < 5)
			{
				score[i] -= check_make_four(arr, i, yindex[i] + 1, 1) /2 ;
				score[i] -= check_make_three(arr, i, yindex[i] + 1, 1) / 2;
				score[i] -= check_make_two(arr, i, yindex[i] + 1, 1) /2;

				score[i] -= check_make_four(arr, i, yindex[i] + 1, 2) ;
				score[i] -= check_make_three(arr, i, yindex[i] + 1, 2) /2;
				score[i] -= check_make_two(arr, i, yindex[i] + 1, 2) /2;

			}
		}
	}

	score[3] += is_only_center(arr);

	for (i = 0; i < 7; i++)
	{
		if (yindex[i] != -1)
		{
			maxIndex = i;
			maxScore = score[i];
			break;
		}
	}

	for (i = 0; i < 7; i++)	//check who is max
	{
		if (yindex[i] != -1 && score[i] > maxScore)
		{
			maxIndex = i;
			maxScore = score[i];
		}
	}

	arr[yindex[maxIndex]][maxIndex] = 1;
}