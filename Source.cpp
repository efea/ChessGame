#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Board.h"
#include "Move.h"
#include "Player.h"
using namespace std;


void main() {
	bool validity;
	Board board1;
	Move move1;
	Player player1(false);
	char temppiece;
	char temprows;
	board1.intro();
	while (player1.getPlayAgain() == true) {
		validity = false;
		board1.setUpBoard();
		board1.setPieces();
		while (board1.isKingDead() == false) {
			while(validity == false) {
				board1.displayBoard();
				player1.showPlayer();
				move1.readMove();
				move1.displayMove();
				move1.checkSquare();
				move1.checkPiece(player1.getPlayer());
				cout << (char)move1.getCols() << endl;
				cout << (char)move1.getRows() << endl;
				validity = board1.isMoveValid(move1.getPiece(), move1.getCols(), move1.getRows(), move1.getCapture(), move1.getPawnFile());
			}
			player1.togglePlayer();
			validity = false;
		}
		board1.displayBoard();
		board1.outro(player1.getPlayer());
		player1.togglePlayer();
		player1.setPlayAgain();
	}
	board1.theVeryEnd();
	return;
}