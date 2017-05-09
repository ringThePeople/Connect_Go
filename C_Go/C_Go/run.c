#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define Bad -2000 
//initialize functions
void print_board(int board[][7]);
void push(int board[][7], int turn);
bool sub_check(int arr[][7], int x, int y);
//bool sub_check(int arr[][7], int y);
int winCheck(int arr[][7]);
void winnerPrint(int winCheck);
void Do_by_condition(int arr[][7], int who);
int fiveStone(int arr[][7], int x, int y, int who);

int check_make_four(int arr[][7], int x, int y, int who);	//simple check by Jongmin
int row_check_make_four(int arr[][7], int x, int y, int who);	//it can be 4 through row
int diagonal_check_make_four(int arr[][7], int x, int y, int who);		//check whether this position make win or not by 'diagonal - 4'			//Jongmin 
int column_check_make_four(int arr[][7], int x, int y, int who); // 세로로 연속된 3개가 있는지 체크

int check_make_three(int arr[][7], int x, int y, int who);
int row_check_make_three(int arr[][7], int x, int y, int who); // 가로로 연속된 3개를 만들 수 있는지 체크
int diagonal_check_make_three(int arr[][7], int x, int y, int who); // '／'대각선 연속된 3개를 만들 수 있는지 체크
int negative_diagonal_check_make_three(int arr[][7], int x, int y, int who); // '＼'대각선 연속된 3개를 만들 수 있는지 체크
int column_check_make_three(int arr[][7], int x, int y, int who);
int row_check_make_three_but_onesidebarrier(int arr[][7], int x, int y, int who);

int check_make_two(int arr[][7], int x, int y, int who);
int column_check_make_two(int arr[][7], int x, int y, int who);
int row_check_make_two(int arr[][7], int x, int y, int who);
int diagonal_check_make_two(int arr[][7], int x, int y, int who); // '／'대각선 연속된 2개를 만들 수 있는지 체크
int negative_diagonal_check_make_two(int arr[][7], int x, int y, int who); // '＼'대각선 연속된 2개를 만들 수 있는지 체크

int check_only_one(int arr[][7], int x, int y, int who);
int row_check_make_only_one(int arr[][7], int x, int y, int who); // 가로로 연결이 안될 때
int diagonal_check_make_only_one(int arr[][7], int x, int y, int who); // '／'대각선 연결이 안될 때
int negative_diagonal_check_make_only_one(int arr[][7], int x, int y, int who); // '＼'대각선 연결이 안될 때

int is_only_center(int arr[][7]);
void deepmind(int arr[][7], int who, int* score);
int* find_top_three(int*  arr);

int* calculate_score_by_condition(int arr[][7], int who);	//calculator module by Jongmin
int minMax_by_conditions(int arr[][7], int who, int cnt);	//Jongmin
void Do_by_minMax_using_condition(int arr[][7], int who);		//Jongmin

void ai_push(int board[][7], int turn);//인공지능 push를 위함
int ai(int board[][7], int first);//인공지능
int winHeuristic(int board[][7], int x, int turn);//내가 뒀을때 이기는지 계산하는 함수
int deathHeuristic(int board[][7], int x, int turn);//상대방이 둿을때 내가 지는지 계산하는 함수
int wSpot(int board[][7], int x, int turn);//그 수가 이기는 수인지 지는 수인지 계산하는 평가 함수
int cal_Winning(int board[][7], int x, int turn);//승리 가능성을 계산 하는 함수
int lookFront(int board[][7], int x, int depth);//7수 앞을 내다 보는 재귀함수
void copyBoard(int board[][7], int cpyB[][7]);//재귀함수를 위한 현 게임상태 복사 함수
int stopping(int board[][7], int x, int turn);//3목을 두는 것을 방해하게함을 위한 평가함수
int minMax(int cr[], int depth);//minmax알고리즘 구현 함수

int frontInt = 0;// 몇번 재귀하는지
int poss = 0;//현재 board에 놓은 수
int cr[830000];//재귀함수의 state를 저장
int onBoard = 0;
int oriDepth = 7;//in lookFront
int willLose = 0;//반드시 지는 값을 체크하기위한 변수
				 //main function
void main()
{
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
		printf("Which method ( 1. by algorithm  2. by condition  3. by push  4. by Jong-max )\n");
		scanf_s("%d", &methods);
		
		if (methods == 3)
			push(board, first + (turn++));
		else if (methods == 1)
		{
			printf("AI가 계산 중 입니다....\n");
			ai_push(board, first + 1 + (turn++));
		}
		else if (methods == 2)
		{
			Do_by_condition(board, first + (turn++));
		}	
		else if (methods == 4)
		{
			Do_by_minMax_using_condition(board, first + (turn++));
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

	winnerPrint(winner);

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
	if (turn<3)
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


 //// delete this sentence.. when 5 connected , it means win.. -> (some problem ..when it is connected five.. so develope more..)
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

void winnerPrint(int winCheck)
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
	for (i = x + 1; i < 7; i++)
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
	for (i = 1; i < 4; i++)				
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
	for (i = 1; i < 4; i++)				
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
/*
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
*/
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
				else	//y == 0 can be defensed
				{
					return 500;
				}
			}
		}
		else
		{
			if (arr[y][x - 1] == enm && arr[y][x + 1] == who && arr[y][x + 2] == who && arr[y][x + 3] == 0)
			{
				if (y > 0)
				{
					if (arr[y - 1][x + 3] == 0)
						return 1000;
					else
						return 500;
				}
				else	//y == 0 can be defensed
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
				else	//y == 0 can be defensed
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
				else	//y == 0 can be defensed
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
				else	//y == 0 can be defensed
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
				else	//y == 0 can be defensed
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
		else if (arr[y][x - i] == 0) {
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
		else if (arr[y][x + i] == 0) {
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
	if (y == 5)
		return 0;

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
	return(column_check_make_three(arr, x, y, who) + row_check_make_three(arr, x, y, who)  + diagonal_check_make_three(arr, x, y, who) + negative_diagonal_check_make_three(arr, x, y, who));
}
//+ row_check_make_three_but_onesidebarrier(arr, x, y, who)


int column_check_make_two(int arr[][7], int x, int y, int who)		//Jongmin
{
	int cnt = 0;
	int i = 0;
	if (y == 1)
	{
		if (arr[0][x] == who)
			return 50;
	}
	if (y > 1 && y <= 3) // 2 3
	{
		if (arr[y - 1][x] == who && arr[y - 2][x] != who)			//for checking not to give double point when connected three
			return 50;
	}

	return 0;
}



int row_check_make_two(int arr[][7], int x, int y, int who)		//big examination... by Jongmin
{
	int enm = 2;
	if (who == 2)
		enm = 1;

	switch (x)
	{
	case 0:
		if (arr[y][1] == who && arr[y][2] != who) //arr[y][2]!=who means, do not give double point when 3 connected
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
			if (arr[y][2] == enm)
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
	int L_w_x = x - 1;
	int R_w_x = x + 1;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) {
		if (y - i < 0)
			break;

		if (arr[y - i][x - i] == who) {
			L_w_x = x - i - 1;
			if (L_wall == 1) {
				L_x = x - i;
				count++;
			}
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

		if (arr[y + i][x + i] == who) {
			R_w_x = x + i + 1;
			if (R_wall == 1) {
				R_x = x + i;
				count++;
			}
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
			if (L_support == 0 && R_support == 0) {
				if (length == 4)
					return 200;
				else
					return 350;
			}
			else {
				if (length == 4)
					return 150;
				else
					return 300;
			}
		}
		else if (L_wall == 0) {
			if (L_support == 1) {
				return 150;
			}
			else {
				return 200;
			}
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 150;
			else
				return 200;
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
	int L_w_x = x - 1;
	int R_w_x = x + 1;
	int i;
	int count = 0;

	for (i = 1; i <= x; i++) {
		if (y + i > 5)
			break;

		if (arr[y + i][x - i] == who) {
			L_w_x = x - i - 1;
			if (L_wall == 1) {
				L_x = x - i;
				count++;
			}
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
			if (R_wall == 1) {
				R_x = x + i;
				count++;
			}
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
				if (length == 4)
					return 150;
				else
					return 300;
			}
			else if (L_support == 0 && R_support == 0) {
				if (length == 4)
					return 200;
				else
					return 300;
			}
			else {
				if (length == 4)
					return 150;
				else
					return 300;
			}
		}
		else if (L_wall == 0) {
			if (L_support == 1) {
				return 150;
			}
			else {
				return 200;
			}
		}
		else if (R_wall == 0) {
			if (R_support == 1)
				return 150;
			else
				return 200;
		}
		else
			return 0;
	}

	return 0;

}
// < - '＼'대각선 연속된 2개를 만들 수 있는지 체크 By JeongIn


int check_make_two(int arr[][7], int x, int y, int who)
{
	return (row_check_make_two(arr, x, y, who) + column_check_make_two(arr, x, y, who) + diagonal_check_make_two(arr, x, y, who) + negative_diagonal_check_make_two(arr, x, y, who));
}


// - > 가로로 연결이 안될 때 By JeongIn
int row_check_make_only_one(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int R_wall = 1;
	int R_support = 1;
	int i;
	int L_count = 0;
	int R_count = 0;

	if (y > 0) {
		if (arr[y - 1][x - 1] == 0)
			L_support = 0;
	}

	if (x > 1) {
		for (i = 2; i <= x; i++) {
			if (arr[y][x - 1] == 0) {

				if (arr[y][x - i] == who)
					L_count++;
				else if (arr[y][x - i] == enemy)
					break;
				else if (arr[y][x - i] == 0) {
					L_wall = 0;
					break;
				}
			}
		}
	}

	if (y > 0) {
		if (arr[y - 1][x + 1] == 0)
			R_support = 0;
	}

	if (x < 5) {
		for (i = 2; i <= 6 - x; i++) {

			if (arr[y][x + 1] == 0) {
				if (arr[y][x + i] == who)
					R_count++;
				else if (arr[y][x + i] == enemy)
					break;
				else if (arr[y][x + i] == 0) {
					R_wall = 0;
					break;
				}
			}
		}
	}

	if (L_count == 2 && R_count == 2) {
		if (L_support == 1 && R_support == 1)
			return 10000;
		else if (L_support == 0 && R_support == 0)
			return 2000;
		else
			return 1000;
	}
	else if (L_count == 2) {
		if (L_support == 0)
			return 1000;
		else
			return 500;
	}
	else if (R_count == 2) {
		if (R_support == 0)
			return 1000;
		else
			return 500;
	}
	else if (L_count == 1 && R_count == 1) {
		if (L_support == 1 && R_support == 1)
			return 200;
		else if (L_support == 0 && R_support == 0)
			return 150;
		else
			return 100;
	}
	else if (L_count == 1) {
		if (L_wall == 1 && R_wall == 1)
			return 0;
		else if (L_support == 0)
			return 200;
		else
			return 150;
	}
	else if (R_count == 1) {
		if (L_wall == 1 && R_wall == 1)
			return 0;
		else if (R_support == 0)
			return 200;
		else
			return 150;
	}
	else
		return 0;

}
// < - 가로로 연결이 안될 때 By JeongIn


// - > '＼' 대각선 연결이 안될 때 By JeongIn
int diagonal_check_make_only_one(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int R_wall = 1;
	int R_support = 1;
	int i;
	int L_count = 0;
	int R_count = 0;

	if (x > 0 && y > 2) {
		if (arr[y - 2][x - 1] == 0)
			L_support = 0;
	}
	if (y == 1)
		L_support = 0;

	if (x > 1 && y > 1) {
		for (i = 2; i <= x; i++) {
			if (y - i < 0)
				break;

			if (arr[y - 1][x - 1] == 0) {	
				if (arr[y - i][x - i] == who)
					L_count++;
				else if (arr[y - i][x - i] == enemy)
					break;
				else if (arr[y - i][x - i] == 0) {
					L_wall = 0;
					break;
				}
			}
		}
	}

	if (x < 6 && y < 5) {
		if (arr[y][x + 1] == 0)
			R_support = 0;
	}

	if (x < 5 && y < 4) {
		for (i = 2; i <= 6 - x; i++) {
			if (y + i > 5)
				break;

			if (arr[y + 1][x + 1] == 0) {
				if (arr[y + i][x + i] == who)
					R_count++;
				else if (arr[y + i][x + i] == enemy)
					break;
				else if (arr[y + i][x + i] == 0) {
					R_wall = 0;
					break;
				}
			}
		}
	}

	
	if (L_count == 2) {
		if (L_support == 0)
			return 1000;
		else
			return 500;
	}
	else if (R_count == 2) {
		if (R_support == 0)
			return 1000;
		else
			return 500;
	}
	else if (L_count == 1 && R_count == 1) {
		if (L_support == 1 && R_support == 1)
			return 200;
		else if (L_support == 0 && R_support == 0)
			return 150;
		else
			return 100;
	}
	else if (L_count == 1) {
		if (L_wall == 1 && R_wall == 1)
			return 0;
		else if (L_support == 0)
			return 200;
		else
			return 150;
	}
	else if (R_count == 1) {
		if (L_wall == 1 && R_wall == 1)
			return 0;
		else if (R_support == 0)
			return 200;
		else
			return 150;
	}
	else
		return 0;

}
// < - '＼' 대각선 연결이 안될 때 By JeongIn


// - > '／' 대각선 연결이 안될 때 By JeongIn
int negative_diagonal_check_make_only_one(int arr[][7], int x, int y, int who) {

	int enemy = 3 - who;
	int L_wall = 1;
	int L_support = 1;
	int R_wall = 1;
	int R_support = 1;
	int i;
	int L_count = 0;
	int R_count = 0;

	if (x > 0 && y < 5) {
		if (arr[y][x - 1] == 0)
			L_support = 0;
	}

	if (x > 1 && y < 4) {
		for (i = 2; i <= x; i++) {
			if (y + i > 5)
				break;

			if (arr[y + 1][x - 1] == 0) {
				if (arr[y + i][x - i] == who)
					L_count++;
				else if (arr[y + i][x - i] == enemy)
					break;
				else if (arr[y + i][x - i] == 0) {
					L_wall = 0;
					break;
				}
			}
		}
	}

	if (x < 6 && y > 1) {
		if (arr[y - 2][x + 1] == 0)
			R_support = 0;
	}
	if (y == 1)
		R_support = 0;

	if (x < 5 && y > 1) {
		for (i = 2; i <= 6 - x; i++) {
			if (y - i < 0)
				break;

			if (arr[y - 1][x + 1] == 0) {
				if (arr[y - i][x + i] == who)
					R_count++;
				else if (arr[y - i][x + i] == enemy)
					break;
				else if (arr[y - i][x + i] == 0) {
					R_wall = 0;
					break;
				}
			}
		}
	}


	if (L_count == 2) {
		if (L_support == 0)
			return 1000;
		else
			return 500;
	}
	else if (R_count == 2) {
		if (R_support == 0)
			return 1000;
		else
			return 500;
	}
	else if (L_count == 1 && R_count == 1) {
		if (L_support == 1 && R_support == 1)
			return 200;
		else if (L_support == 0 && R_support == 0)
			return 150;
		else
			return 100;
	}
	else if (L_count == 1) {
		if (L_wall == 1 && R_wall == 1)
			return 0;
		else if (L_support == 0)
			return 200;
		else
			return 150;
	}
	else if (R_count == 1) {
		if (L_wall == 1 && R_wall == 1)
			return 0;
		else if (R_support == 0)
			return 200;
		else
			return 150;
	}
	else
		return 0;

}
// < - '／' 대각선 연결이 안될 때 By JeongIn


int check_only_one(int arr[][7], int x, int y, int who) {
	return (row_check_make_only_one(arr, x, y, who) + diagonal_check_make_only_one(arr, x, y, who) + negative_diagonal_check_make_only_one(arr, x, y, who));
}


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
void Do_by_condition(int arr[][7], int who)	//condition module by Jongmin
{
	int yindex[7] = { -1,-1,-1,-1,-1,-1,-1 };
	int score[7] = { -1,-1,-1,-1,-1,-1,-1 };
	int maxIndex = 0;
	int maxScore = 0;
	int tempscore = 0;
	int i, j;
	who = (who % 2) + 1;
	int enm = 3 - who;

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

	for (i = 0; i < 7; i++)		//when it can win right-now, then do that
	{
		if (yindex[i] == -1)
			continue;
		else
		{
			tempscore = check_make_four(arr, i, yindex[i], who);
			if (tempscore > 10000)
			{
				arr[yindex[i]][i] = who;
				return;
			}
			else
			{
				score[i] = tempscore;
			}
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (yindex[i] == -1)
			continue;
		else
		{
			score[i] += check_make_three(arr, i, yindex[i], who);
			score[i] += check_make_two(arr, i, yindex[i], who);
			score[i] += check_only_one(arr, i, yindex[i], who);

			tempscore = check_make_four(arr, i, yindex[i], enm);
			if (tempscore > 10000)
			{
				arr[yindex[i]][i] = who;
				return;
			}
			else
			{
				score[i] += tempscore;
			}

			score[i] += check_make_three(arr, i, yindex[i], enm);
			score[i] += check_make_two(arr, i, yindex[i], enm);
			score[i] += check_only_one(arr, i, yindex[i], enm);

			if (yindex[i] < 5)
			{
				score[i] -= check_make_four(arr, i, yindex[i] + 1, who) / 2;
				score[i] -= check_make_three(arr, i, yindex[i] + 1, who) / 2;
				score[i] -= check_make_two(arr, i, yindex[i] + 1, who) / 4;
				score[i] -= check_only_one(arr, i, yindex[i] + 1, who) / 4;

				score[i] -= check_make_four(arr, i, yindex[i] + 1, enm);
				score[i] -= check_make_three(arr, i, yindex[i] + 1, enm) / 2;
				score[i] -= check_make_two(arr, i, yindex[i] + 1, enm) / 3;
				score[i] -= check_only_one(arr, i, yindex[i] + 1, enm) / 3;

			}
		}
	}

	deepmind(arr, who, score);
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

	arr[yindex[maxIndex]][maxIndex] = who;
}

void ai_push(int board[][7], int turn)//hwan
{
	int num, height = 0;
	int i;

	num = ai(board, turn);// call ai

	for (i = 0; i < 6; i++)
	{
		if (board[i][num] == 0)
		{
			height = i;
			break;
		}
	}
	board[height][num] = 1;
}

int cal_Winning(int board[][7], int x, int turn)
{
	int i, j, y = 0;
	int hValue = 0;
	int myTurn, yourTurn;
	for (i = 5; i >= 0; i--)//input x -> (x,y)
	{
		if (board[i][x] == 0)
		{
			y = i + 1;
			break;
		}
		if (i == 0)
			y = 0;
	}
	if (y == 6)
		return Bad;
	board[y][x] = (turn % 2);
	myTurn = (turn % 2);
	yourTurn = (turn % 2) + 1;

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((board[i][j] != yourTurn) && (board[i][j + 1] != yourTurn) && (board[i][j + 2] != yourTurn) && (board[i][j + 3] != yourTurn))
				hValue = hValue + 3;
			if ((board[i][j] != myTurn) && (board[i][j + 1] != myTurn) && (board[i][j + 2] != myTurn) && (board[i][j + 3] != myTurn))
				hValue = hValue - 2;
		}
	} //row heuristic value

	for (j = 0; j < 7; j++)
	{
		for (i = 0; i < 3; i++)
		{
			if ((board[i][j] != yourTurn) && (board[i + 1][j] != yourTurn) && (board[i + 2][j] != yourTurn) && (board[i + 3][j] != yourTurn))
				hValue = hValue + 2;
			if ((board[i][j] != myTurn) && (board[i + 1][j] != myTurn) && (board[i + 2][j] != myTurn) && (board[i + 3][j] != myTurn))
				hValue = hValue - 1;
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((board[i][j] != yourTurn) && (board[i + 1][j + 1] != yourTurn) && (board[i + 2][j + 2] != yourTurn) && (board[i + 3][j + 3] != yourTurn))
				hValue = hValue + 3;
			if ((board[i][j] != myTurn) && (board[i + 1][j + 1] != myTurn) && (board[i + 2][j + 2] != myTurn) && (board[i + 3][j + 3] != myTurn))
				hValue = hValue - 2;
		}
	}

	board[y][x] = 0;
	//if (turn > 13)//hmm
	//	return hValue / 2;
	return 9 * hValue;
}

int winHeuristic(int board[][7], int x, int turn)//x-> input number
{
	int i, y;
	y = 0;
	for (i = 5; i >= 0; i--)//input->(x,y)
	{
		if (board[i][x] != 0)
		{
			y = i + 1;
			break;
		}
		if (i == 0)
			y = 0;
	}
	if (y == 6)
		return Bad;
	board[y][x] = (turn % 2);
	if (winCheck(board) != 0)//Player 2(AI) Win then return 4000
	{
		board[y][x] = 0;
		return 4000;
	}
	board[y][x] = 0;
	return 0;
}

int wSpot(int board[][7], int x, int turn)
{
	int i, j, y, start, AI_33 = 0, People_33 = 0;
	int check[6][7];
	int atomResult = 0;
	int spot = 0;
	y = 0;
	for (i = 5; i >= 0; i--)
	{
		if (board[i][x] != 0)
		{
			y = i + 1;
			break;
		}
		if (i == 0)
			y = 0;
	}
	if (y == 6)
		return Bad;
	board[y][x] = (turn % 2);
	if (winCheck(board) == 0)//Game not Yet Finished
	{
		for (i = 0; i < 7; i++)
		{
			start = -1;
			for (j = 0; j < 6; j++)
			{
				if (board[j][i] == 0)
				{
					if (start == -1)
						start = j;
					board[j][i] = (turn % 2);
					if (winCheck(board) != 0)
					{
						spot += 6 - j;
						if (start == j)
							AI_33++;
					}//ai did 33
					board[j][i] = (turn % 2) + 1;
					if (winCheck(board) != 0)
					{
						spot -= 6 - j;
						if (start == j)
							People_33++;
					}//enemy do 33
					board[j][i] = 0;
					if (start != -1)
						break;
				}
			}
		}
	}

	if ((AI_33 >= 2) && (People_33 == 0))
		atomResult += 4100;//33 heuristic
	if ((AI_33 == 0) && (People_33 >= 2))
		atomResult -= 4099;
	board[y][x] = 0;
	copyBoard(board, check);

	for (j = 0; j < 7; j++)
	{
		for (i = 5; i >= 0; i--)
		{
			if (check[i][j] == 0)
			{
				check[i][j] = (turn % 2);
				if ((winCheck(check) != 0) && i < 5)
				{
					check[i][j] = (turn % 2) + 1;
					check[i + 1][j] = (turn % 2);
					if (winCheck(check) != 0)
						atomResult += 3777;
					check[i + 1][j] = 0;
				}
				check[i][j] = 0;
			}
		}
	}//AI가 놓으면 이기는 자리를 막아도 AI가 이기는 경우

	for (j = 0; j < 7; j++)
	{
		for (i = 5; i >= 0; i--)
		{
			if (check[i][j] == 0)
			{
				check[i][j] = (turn % 2) + 1;
				if ((winCheck(check) != 0) && i < 5)
				{
					check[i][j] = (turn % 2);
					check[i + 1][j] = (turn % 2) + 1;
					if (winCheck(check) != 0)
						atomResult -= 3891;
					check[i + 1][j] = 0;
				}
				check[i][j] = 0;
			}
		}
	}//상대방이 놓으면 이기는 자리를 막아도 AI가 지는 경우

	for (j = 0; j < 7; j++)
	{
		for (i = 5; i >= 0; i--)
		{
			if (check[i][j] == 0)
			{
				check[i][j] = (turn % 2);
				if (winHeuristic(check, j, turn + 1) == 4000)
					atomResult -= 3777;

				check[i][j] = 0;
			}
		}
	}
	if (atomResult != 0)
		return atomResult;//when 33
	return 31 * spot;
}

int deathHeuristic(int board[][7], int x, int turn)
{
	int i, y;
	y = 0;
	for (i = 5; i >= 0; i--)
	{
		if (board[i][x] != 0)
		{
			y = i + 1;
			break;
		}
		if (i == 0)
			y = 0;
	}
	if (y == 6)
		return Bad;
	board[y][x] = (turn % 2) + 1;
	if (winCheck(board) != 0)//player1(not AI) win then return 3000	
	{
		board[y][x] = 0;
		return 3000;
	}
	board[y][x] = 0;
	return 0;
}

int stopping(int board[][7], int x, int turn)
{
	int i, j, y;
	int myTurn, yourTurn, hValue = 0;
	y = 0;
	for (i = 5; i >= 0; i--)
	{
		if (board[i][x] != 0)
		{
			y = i + 1;
			break;
		}
	}
	if (i == 0)
		y = 0;
	if (y == 6)
		return Bad;
	board[y][x] = (turn) % 2;

	myTurn = (turn % 2);
	yourTurn = turn % 2 + 1;
	for (i = 0; i < 6; i++)
	{
		if ((board[i][0] == yourTurn) && (board[i][1] == yourTurn) && (board[i][2] == myTurn))
			hValue = hValue + 3;
		if ((board[i][1] == yourTurn) && (board[i][2] == yourTurn) && (board[i][3] == myTurn))
			hValue = hValue + 3;
		if ((board[i][1] == yourTurn) && (board[i][2] == yourTurn) && (board[i][0] == myTurn))
			hValue = hValue + 1;
		if ((board[i][3] == yourTurn) && (board[i][4] == yourTurn) && ((board[i][2] == myTurn) || (board[i][5] == myTurn)))
			hValue = hValue + 3;
		if ((board[i][5] == yourTurn) && (board[i][6] == yourTurn) && (board[i][4] == myTurn))
			hValue = hValue + 3;
		if ((board[i][4] == yourTurn) && (board[i][5] == yourTurn) && (board[i][6] == myTurn))
			hValue = hValue + 1;
		if ((board[i][4] == yourTurn) && (board[i][5] == yourTurn) && (board[i][3] == myTurn))
			hValue = hValue + 3;
	}//row 3 defense

	for (j = 0; j < 7; j++)
	{
		if ((board[0][j] == yourTurn) && (board[1][j] != yourTurn) && (board[2][j] == myTurn))
			hValue = hValue + 2;
		if ((board[1][j] == yourTurn) && (board[2][j] != yourTurn) && (board[3][j] == myTurn) && (board[0][j] == myTurn))
			hValue = hValue + 2;
		if ((board[2][j] == yourTurn) && (board[3][j] != yourTurn) && (board[4][j] == myTurn) && (board[1][j] == myTurn))
			hValue = hValue + 1;
	}//high
	for (j = 0; j < 5; j++)
	{
		if ((board[0][j] == yourTurn || board[0][j] == 0) && (board[1][j + 1] == yourTurn) && (board[2][j + 2] == myTurn))
			hValue = hValue + 3;
		if ((board[0][j + 2] == yourTurn || board[0][j + 2] == 0) && (board[1][j + 1] == yourTurn) && (board[2][j] == myTurn))
			hValue = hValue + 3;
		if (j != 4)
		{
			if ((board[0][j] == myTurn) && (board[1][j + 1] == yourTurn) && (board[2][j + 2] == yourTurn) && (board[3][j + 3] == myTurn))
				hValue = hValue + 3;
			if ((board[0][j + 3] == myTurn) && (board[1][j + 2] == yourTurn) && (board[2][j + 1] == yourTurn) && (board[3][j] == myTurn))
				hValue = hValue + 3;
		}//cross
	}

	return 7 * hValue;
}

int lookFront(int board[][7], int turn, int depth)
{
	int i, j, nonEmpty = 0;
	int height = 0;
	int x, y;
	int cpy[6][7];
	bool check_will_lose = false;

	if (depth == 1)
	{
		copyBoard(board, cpy);
		nonEmpty = 0;
		for (i = 0; i < 7; i++)
		{
			for (x = 0; x < 6; x++)
			{
				for (y = 0; y < 7; y++)
				{
					if (cpy[x][y] != 0)
						nonEmpty++;
				}
			}
			if (nonEmpty - poss == oriDepth - 1)//7수를 내다봤다면
			{
				if (willLose == 1 || (winCheck(cpy) != 0 && poss <= 25))
					cr[frontInt] = Bad;
				else
				{
					cr[frontInt] = winHeuristic(cpy, i, turn) + wSpot(cpy, i, turn) + cal_Winning(cpy, i, turn) + stopping(cpy, i, turn) + deathHeuristic(cpy, i, turn);
				}
			}
			else// 7수를 둘게 없네?!
			{
				cr[frontInt] = Bad;
			}
			frontInt++;

		}

	}
	else
	{
		for (i = 0; i < 7; i++)
		{
			copyBoard(board, cpy);
			for (j = 0; j < 6; j++)
			{
				if (cpy[j][i] == 0)
				{
					height = j;
					break;
				}
			}
			cpy[height][i] = (turn % 2) + 1;
			if (depth == oriDepth)
			{
				if (winHeuristic(cpy, i, turn + 1) == 4000)
				{
					willLose = 1;
				}
				lookFront(cpy, turn + 1, depth - 1);
				willLose = 0;
			}
			else
			{
				lookFront(cpy, turn + 1, depth - 1);
			}
			cpy[height][i] = 0;
		}
	}
	if (depth == oriDepth)
	{
		return minMax(cr, oriDepth);
	}
	return 0;
}

int minMax(int cr[], int depth)
{
	int i, j;
	int min = 99999, max = -99999;
	int rndNum;

	for (i = depth; i >= 0; i--)
	{
		for (j = 0; j < (int)pow(7, i); j++)
		{
			if (i == 1)//최종 결과물 출력
			{
				if (j == 0)
					printf("Heuristic Fuction Value : \n");
				printf("%d  ", cr[j]);
				if (j == 6)
					printf("\n");
			}

			if (i % 2 == 0)//min값 계산
			{
				if (min > cr[j])
					min = cr[j];
			}
			else//max값 계산
			{
				if (max < cr[j])
					max = cr[j];
			}
			if (i == 1 && j == 6)
			{
				srand((unsigned int)time(NULL));
				while (1)
				{
					rndNum = rand() % 7;
					if (cr[rndNum] == max)
						return rndNum;
					if (cr[0] == -100000 && cr[1] == -100000 && cr[2] == -100000 && cr[3] == -100000 && cr[4] == -100000 && cr[5] == -100000 && cr[6] == -100000)
						return -1;//죠때쓰마~
				}
			}
			if (j % 7 == 6)
			{
				if (i % 2 == 0)
				{
					if (min == Bad || min == 99999)
						cr[j / 7] = -100000;
					//cr[(j + 1) / 7 - 1] = -100000;
					else
						cr[j / 7] = min;
					//cr[(j + 1) / 7 - 1] = min;
				}
				else
				{
					if (max == Bad || max == -99999)
						cr[j / 7] = 100000;
					//cr[(j + 1) / 7 - 1] = 100000;
					else
						//cr[(j + 1) / 7 - 1] = max;
						cr[j / 7] = max;
				}
				max = -99999;
				min = 99999;
			}
		}
	}
	return cr[0];
}

int ai(int board[][7], int turn)
{

	int enemy, mine;
	//int depth=7;
	int i, j;
	int seDol;
	int front[7];
	int max = -9999;

	poss = 0;
	enemy = (turn) % 2 + 1;
	mine = (turn) % 2;

	for (i = 0; i < 7; i++)
	{
		if (winHeuristic(board, i, turn) == 4000)
			return i;
	}
	for (i = 0; i < 7; i++)
	{
		if (deathHeuristic(board, i, turn) == 3000)
			return i;
	}
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (board[i][j] != 0)
				poss++;
		}
	}
	if (poss >= 34)
	{
		frontInt = 0;
		if (poss == 41)
		{
			for (i = 0; i < 7; i++)
			{
				if (board[5][i] == 0)
					return i;
			}
		}
		else if (poss == 40)
			oriDepth = 1;
		else if (poss >= 38)
			oriDepth = 3;
		else
			oriDepth = 5;
		seDol = lookFront(board, turn, oriDepth);
	}
	else
	{
		frontInt = 0;
		oriDepth = 7;
		if (poss <= 4 && board[poss][3] == 0)
			return 3;
		seDol = lookFront(board, turn, oriDepth);

		if (seDol == -1)
		{
			for (i = 0; i < 7; i++)
			{
				front[i] = wSpot(board, i, turn) + cal_Winning(board, i, turn) + winHeuristic(board, i, turn) + stopping(board, i, turn);
				if (max <= front[i])
					seDol = i;
			}
			return seDol;
		}
	}

	return seDol;
}

void copyBoard(int board[][7], int cpyB[][7])
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			cpyB[i][j] = board[i][j];
		}
	}
}

void deepmind(int arr[][7], int who, int* score)	//deep mind by Jongmin
{
	int enm = 3 - who;
	int i;
	if (arr[0][3] == who && arr[1][3] == enm && arr[2][3] == who && arr[3][3] == enm && arr[4][3] == who)
	{
		if (arr[0][0] == enm && arr[1][0] == 0 && arr[5][3] == 0)
		{
			for (i = 1; i < 7; i++)
			{
				
				if (arr[0][i] != 0)
					return;
			}
			score[2] += 1000;
			return;
		}	
		if (arr[0][1] == enm && arr[1][1] == 0 && arr[5][3] == 0)
		{
			for (i = 0; i < 7; i++)
			{
				if (i == 1 || i== 3)
					continue;
				if (arr[0][i] != 0)
					return;
			}

			score[1] += 1000;
			return;
		}
		if (arr[0][2] == enm && arr[1][2] == 0 && arr[5][3] == 0)
		{
			for (i = 0; i < 7; i++)
			{
				if (i == 2 || i == 3)
					continue;
				if (arr[0][i] != 0)
					return;
			}

			score[2] += 1000;
			return;
		}
		if (arr[5][3] == enm)
		{
			for (i = 0; i < 7; i++)
			{
				if (i == 3 )
					continue;
				if (arr[0][i] != 0)
					return;
			}

			score[2] += 1000;
			return;
		}
		if (arr[0][4] == enm && arr[1][4] == 0 && arr[5][3] == 0)
		{
			for (i = 0; i < 7; i++)
			{
				if (i == 4 || i == 3)
					continue;
				if (arr[0][i] != 0)
					return;
			}

			score[4] += 1000;
			return;
		}
		if (arr[0][5] == enm && arr[1][5] == 0 && arr[5][3] == 0)
		{
			for (i = 0; i < 7; i++)
			{
				if (i == 5 || i == 3)
					continue;
				if (arr[0][i] != 0)
					return;
			}

			score[5] += 1000;
			return;
		}
		if (arr[0][6] == enm && arr[1][6] == 0 && arr[5][3] == 0)
		{
			for (i = 0; i < 7; i++)
			{
				if (i == 6 || i == 3)
					continue;
				if (arr[0][i] != 0)
					return;
			}

			score[4] += 1000;
			return;
		}
	}
	int check = 0;
	if (arr[0][0] == enm && arr[1][0] == 0)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == 0)
				continue;
			check += arr[0][i];
		}
		if (check == 0)
		{
			score[1] += 1000;
		}
	}
	if (arr[0][1] == enm && arr[1][1] == 0)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == 1)
				continue;
			check += arr[0][i];
		}
		if (check == 0)
		{
			score[2] += 1000;
		}
	}
	if (arr[0][2] == enm && arr[1][2] == 0)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == 2)
				continue;
			check += arr[0][i];
		}
		if (check == 0)
		{
			score[3] += 1000;
		}
	}
	if (arr[0][4] == enm && arr[1][4] == 0)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == 4)
				continue;
			check += arr[0][i];
		}
		if (check == 0)
		{
			score[3] += 1000;
		}
	}
	if (arr[0][5] == enm && arr[1][5] == 0)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == 5)
				continue;
			check += arr[0][i];
		}
		if (check == 0)
		{
			score[4] += 1000;
		}
	}
	if (arr[0][6] == enm && arr[1][6] == 0)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == 6)
				continue;
			check += arr[0][i];
		}
		if (check == 0)
		{
			score[3] += 1000;
		}
	}
}


// - > JeongIn
int* find_top_three(int* arr) {
	int* top = (int*)malloc(sizeof(int) * 3);
	int first = 0;
	int second = 0;
	int third = 0;

	int i;

	for (i = 0; i < 7; i++) {
		if (arr[first] < arr[i]) {
			first = i;
		}
	}

	if (first == 0) {
		second = 1;
	}
	for (i = 0; i < 7; i++) {
		if (i == first)
			continue;

		if (arr[second] < arr[i]) {
			second = i;
		}
	}

	if (first == 0) {
		if (second == 1)
			third = 2;
		else
			third = 1;
	}
	else if (second == 0) {
		if (first == 1)
			third = 2;
		else
			third = 1;
	}
	for (i = 0; i < 7; i++) {
		if (first == i || second == i)
			continue;

		if (arr[third] < arr[i]) {
			third = i;
		}
	}

	top[0] = first;
	top[1] = second;
	top[2] = third;

	return top;
}



int* calculate_score_by_condition(int arr[][7], int who)	//calculator module by Jongmin
{
	int yindex[7] = { -1,-1,-1,-1,-1,-1,-1 };
	int i, j;
	int* score = (int*)malloc(sizeof(int) * 7);
	for (i = 0; i < 7; i++)
	{
		score[i] = -1;
	}
	int maxIndex = 0;
	int maxScore = 0;
	int tempscore = 0;
	int enm = 3 - who;

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

	int tempScore = 0;
	for (i = 0; i < 7; i++)
	{
		if (yindex[i] == -1)
		{
			score[i] = 0; //can't do
			continue;
		}
		else
		{
			score[i] += check_make_four(arr, i, yindex[i], who);
			score[i] += check_make_three(arr, i, yindex[i], who);
			score[i] += check_make_two(arr, i, yindex[i], who);
			score[i] += check_only_one(arr, i, yindex[i], who);

			tempScore = check_make_four(arr, i, yindex[i], enm);
			if (tempScore > 10000)
				tempScore -= 1000;
			score[i] += tempScore;
			score[i] += check_make_three(arr, i, yindex[i], enm);
			score[i] += check_make_two(arr, i, yindex[i], enm);
			score[i] += check_only_one(arr, i, yindex[i], enm);

			if (yindex[i] < 5)
			{
				score[i] -= check_make_four(arr, i, yindex[i] + 1, who) / 2;
				score[i] -= check_make_three(arr, i, yindex[i] + 1, who) / 2;
				score[i] -= check_make_two(arr, i, yindex[i] + 1, who) / 4;
				score[i] -= check_only_one(arr, i, yindex[i] + 1, who) / 4;

				score[i] -= check_make_four(arr, i, yindex[i] + 1, enm);
				score[i] -= check_make_three(arr, i, yindex[i] + 1, enm) / 2;
				score[i] -= check_make_two(arr, i, yindex[i] + 1, enm) / 3;
				score[i] -= check_only_one(arr, i, yindex[i] + 1, enm) / 3;

			}
		}
	}

	deepmind(arr, who, score);
	score[3] += is_only_center(arr);

	return score;
}

int minMax_by_conditions(int arr[][7], int who, int cnt)	//Jongmin
{
	int i;
	int j;

	if (cnt > 5)
		return 0;
	int* scores = calculate_score_by_condition(arr, who);
	int mMarr[2][3] = { 0 };
	
	int* tops = find_top_three(scores);
	for (i = 0; i < 3; i++)
	{
		mMarr[0][i] = tops[i];
		mMarr[1][i] = scores[mMarr[0][i]];
	}

	int enm = 3 - who;
	int score = 0;
	int y = -1;
	for (i = 0; i < 3; i++)
	{
		if (arr[5][mMarr[0][i]] != 0)
			continue;
		else
		{
			score += mMarr[1][i];

			for (j = 0; j < 6; j++)
			{
				if (arr[j][mMarr[0][i]] == 0)
				{
					y = j;
					break;
				}
			}
			arr[y][mMarr[0][i]] = who;
			score -= minMax_by_conditions(arr, enm, cnt + 1) / 2;
			arr[y][mMarr[0][i]] = 0;
		}
	}
	free(scores);
	free(tops);

	return score;
}

void Do_by_minMax_using_condition(int arr[][7], int who)		//Jongmin
{
	who = (who % 2) + 1;
	int enm = 3 - who;
	int i;
	int j;
	int yIndex[7] = { -1, -1, -1, -1, -1, -1, -1 };
	int score[7] = { -1, -1, -1, -1, -1, -1, -1 };
	int maxIndex = -1;
	int maxScore = -1;
	int* scores = calculate_score_by_condition(arr, who);
	for (i = 0; i < 7; i++)
		score[i] = scores[i];
	free(scores);

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (arr[j][i] == 0)
			{
				yIndex[i] = j;
				break;
			}
		}
		if (yIndex[i] >= 0)
		{
			if (check_make_four(arr, i, yIndex[i], who) > 10000)
			{
				arr[yIndex[i]][i] = who;
				return;
			}
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (yIndex[i] < 0)
			continue;
		
		if (check_make_four(arr, i, yIndex[i], enm) > 10000)
		{
			arr[yIndex[i]][i] = who;
			return;
		}

		arr[yIndex[i]][i] = who;
		score[i] += minMax_by_conditions(arr, enm, 0);
		arr[yIndex[i]][i] = 0;

		if (yIndex[i] < 5)
		{
			if (check_make_four(arr, i, yIndex[i] + 1, enm) > 10000)
			{
				score[i] -= 500000;
			}
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (yIndex[i] >= 0)
		{
			maxIndex = i;
			maxScore = score[i];
			break;
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (yIndex[i] >= 0 && maxScore < score[i])
		{
			maxIndex = i;
			maxScore = score[i];
		}
	}

	arr[yIndex[maxIndex]][maxIndex] = who;
}