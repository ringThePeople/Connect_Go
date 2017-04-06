#include <stdio.h>

void print_board(int board[][7]) {
	int i,j;	//.¡Û¡Ü

	for (i = 5; i >= 0; i--) {
		for (j = 6; i >= 0; j++) {
			if (board[i][j] == 0)
				printf("%3s", " . ");
			else if (board[i][j] == 1)
				printf("%3s", "¡Ü");
			else
				printf("%3s", "¡Û");
		}
		printf("\n");
	}

}

void main() {
	int board[6][7] = { 0 }; //empty state :: 0 , player 1 :: 1 ,  player 2 :: 2

	int turn = 0;

	
}