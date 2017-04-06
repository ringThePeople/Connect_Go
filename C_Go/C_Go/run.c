#include <stdio.h>

void print_board(int board[][7]) {
	int i,j;	//.∞≒

	for (i = 5; i >= 0; i--) {
		for (j = 6; j >= 0; j--) {
			if (board[i][j] == 0)
				printf("%2s", " .");
			else if (board[i][j] == 1)
				printf("%2s", "≒");
			else
				printf("%2s", "∞");
		}
		printf("\n");
	}
	printf("太0太1太2太3太4太5太6太");

} // 04/06 21:23 jeongin 

void main() {
	int board[6][7] = { 0 }; //empty state :: 0 , player 1 :: 1 ,  player 2 :: 2

	int turn = 0;
	
	// --> 04/06 21:37 jeongin
	int first, player1, player2;
	printf("Who start first?");
	scanf("%d", &turn);
	// <-- 04/06 21:37 jeongin

	print_board(board);

	getchar();

	
}