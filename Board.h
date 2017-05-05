#include <iostream>
using namespace std;
const int rows = 33;
const int cols = 49;
class Board {

public:
	Board();
	void setUpBoard();
	void displayBoard();
	void setPieces();
	void intro();
	bool isMoveValid(char piece, char columns, char rows, bool capture, char pawnfile);
	void toRealcols(char colz);
	void toRealrowz(char rowz);
	bool checkIfAnything(int direction, int rowsofpiece, int colsofpiece);
	bool isKingDead();
	int findDirection();
	int leftOrRight(char pawnfile);
	void outro(bool player);
	void theVeryEnd();

private:
	char board[rows][cols];
	char *invalidmove = "Move was not valid. Try again.\n";
	int realcols;
	int realrows;
	int rowsofrook;
	int colsofrook;
	int rowconst = 4;
	int colconst = 6;
	int rowdiff;
	int coldiff;
	int rowsofbishop = 0;
	int colsofbishop = 0;
};
Board::Board() {
	realcols = 0;
	realrows = 0;
}
void Board::setUpBoard(){

	int i = 0;
	int k = 0;
	for (i = 0; i < rows; i++) {
		for (k = 0; k < cols; k++) {
			if (i == 0 || i == rows - 1)
				board[i][k] = '#';
			else if (i != 0 && (k == 0 || k == cols - 1))
				board[i][k] = '#';
			else if (i % 4 == 0 || k % 6 == 0)
				board[i][k] = '#';
			else
				board[i][k] = ' ';
		}
	}
	return;
};
void Board::displayBoard() {
	int i = 0;
	int k = 0;
	for (i = 0; i < rows; i++) {
		for (k = 0; k < cols; k++) {
			cout << board[i][k];
		}
		cout << endl;
	}
	return;
};
void Board::setPieces() {
	int i = 0;
	int k = 0;
	int count = 0;
	//set the pawns
	for (i = 0; i < rows; i++) {
		for (k = 0; k < cols; k++) {
			if (i == 6) {
				if (k % 3 == 0 && k != 0) {
						count++;
						if (count % 2 == 1) {
							board[i][k] = 'P';
					}
				}
			}
			else if(i == 26){
				if (k % 3 == 0 && k != 0) {
					count++;
					if (count % 2 == 1) {
						board[i][k] = 'p';
					}
				}
			}
		}
	}
	//set the rest of black
	board[2][3] = 'R';
	board[2][9] = 'N';
	board[2][15] = 'Z';
	board[2][21] = 'Q';
	board[2][27] = 'K';
	board[2][33] = 'Z';
	board[2][39] = 'N';
	board[2][45] = 'R';

	//set rest of white
	board[30][3] = 'r';
	board[30][9] = 'n';
	board[30][15] = 'z';
	board[30][21] = 'q';
	board[30][27] = 'k';
	board[30][33] = 'z';
	board[30][39] = 'n';
	board[30][45] = 'r';
	return;
}
void Board::intro() {

	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	cout << "Chess Game, by Efe Astarlioglu" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "How to play, use algebraic notation." << endl;
	cout << "For example, Be5 (move a bishop to e5)," << endl; 
	cout << "Nf3(move a knight to f3), c5(move a pawn to c5-no piece letter in" << endl;
	cout << "the case of pawn moves)." << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Capturing a piece" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "When a piece makes a capture, an x is inserted immediately before the destination square. For example, Bxe5 (bishop captures the piece on e5). When a pawn makes a capture, the file from which the pawn departed is used to identify the pawn. For example, exd5 (pawn on the e-file captures the piece on d5)." << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Black pieces are denoted with capital letters." << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "White will start." << endl;
	cout << "-----------------------------------------------------------------" << endl;
}
bool Board::isMoveValid(char piece, char columns, char rowz, bool capture, char pawnfile) {
	char temppi = piece;
	char tempcolumns = columns;
	char temprowz = rowz;
	int c = -12;
	int r = -8;
	char found;
	int howmanyfound = 0;
	int rowsofnight;
	int colsofnight;
	int i = 0;
	int o = 0;
	char temprook;
	
	int howmanyfoundr = 0;
	char tempbishop;
	int howmanyfoundbishop = 0;
	int rowsofqueen = 0;
	int colsofqueen = 0;
	int rowsofking = 0;
	int colsofking = 0;
	int direction = 0;
	int d = 0;
	bool checktemp;
	int templr = 0;
	cout << "piece is: " << temppi << endl;
	cout << "column is: " << tempcolumns << endl;
	cout << "rowz is: " << temprowz << endl;
	//transform so we can use in the array
	toRealcols(tempcolumns);
	toRealrowz(temprowz);
	//if (capture == false) {
		//there is no capture
	switch (piece) {
	case 'p':
		//white pawn
		if (capture == false) {
			if (board[realrows][realcols] == ' ' && board[realrows + 4][realcols] == 'p') {
				//move is valid
				board[realrows + 4][realcols] = ' ';
				board[realrows][realcols] = piece;
				cout << "Move was valid." << endl;
				return true;
			}

			else {
				cout << "Move was invalid." << endl;
				return false;
			}
		}
		else {
			//white pawn can only capture 
			templr = leftOrRight(pawnfile);
			if (templr < realcols && board[realrows][realcols] != ' ' && board[realrows - rowconst][realcols - colconst] == 'p') {
				//capture to the right
				//move is valid
				board[realrows - rowconst][realcols-colconst] = ' ';
				board[realrows][realcols] = piece;
				cout << "Move was valid." << endl;
				return true;

			}
			else if(templr > realcols && board[realrows][realcols] != ' ' && board[realrows + rowconst][realcols + colconst] == 'p'){
				//capture to the left
				//move is valid
				board[realrows + rowconst][realcols + colconst] = ' ';
				board[realrows][realcols] = piece;
				cout << "Move was valid." << endl;
				return true;
			}
			else {
				cout << "Move was invalid." << endl;
				return false;
			}
		}
	case 'P':
		//black pawn
		if (capture == false) {
			if (board[realrows][realcols] == ' ' && board[realrows - 4][realcols] == 'P') {
				//move is valid
				board[realrows - 4][realcols] = ' ';
				board[realrows][realcols] = piece;
				cout << "Move was valid." << endl;
				return true;
			}

			else {
				cout << "Move was invalid." << endl;
				return false;
			}
		}
		else {
			templr = leftOrRight(pawnfile);
			if (templr < realcols && board[realrows][realcols] != ' ' && board[realrows - rowconst][realcols - colconst] == 'P') {
				//capture to the right
				//move is valid
				board[realrows - rowconst][realcols - colconst] = ' ';
				board[realrows][realcols] = piece;
				cout << "Move was valid." << endl;
				return true;

			}
			else if (templr > realcols && board[realrows][realcols] != ' ' && board[realrows - rowconst][realcols + colconst] == 'P') {
				//capture to the left
				//move is valid
				board[realrows - rowconst][realcols + colconst] = ' ';
				board[realrows][realcols] = piece;
				cout << "Move was valid." << endl;
				return true;
			}
			else {
				cout << "Move was invalid." << endl;
				return false;
			}
		}
	case 'n':
		//white knight
		//if (board[realrows][realcols] == ' ') {
			//operation find the knight
		for (c = -12; c < 13; c++) {
			for (r = -8; r < 9; r++) {
				found = board[realrows + r][realcols + c];
				if (found == 'n') {
					howmanyfound++;
					cout << "r1 is= " << r << endl;
					cout << "c1 is= " << c << endl;
					rowsofnight = realrows + r;
					colsofnight = realcols + c;
					continue;
				}
			}
		}
		cout << "howmany found = " << howmanyfound << endl;
		cout << "r2 is= " << r << endl;
		cout << "c2 is= " << c << endl;
		if (howmanyfound > 0 && capture == false) {
			//valid move, no capture
			board[realrows][realcols] = 'n';
			board[rowsofnight][colsofnight] = ' ';
			rowsofnight = 0;
			colsofnight = 0;
			return true;
		}
		else if (howmanyfound > 0 && capture == true) {
			//valid move, there is a capture
			board[realrows][realcols] = 'n';
			board[rowsofnight][colsofnight] = ' ';
			rowsofnight = 0;
			colsofnight = 0;
			return true;
		}
		else {
			cout << "move was invalid." << endl;
			rowsofnight = 0;
			colsofnight = 0;
			return false;
		}
	case 'N':
		//black knight
		//if (board[realrows][realcols] == ' ') {
			//operation find the knight
		for (c = -12; c < 13; c++) {
			for (r = -8; r < 9; r++) {
				found = board[realrows + r][realcols + c];
				if (found == 'N') {
					howmanyfound++;
					cout << "r1 is= " << r << endl;
					cout << "c1 is= " << c << endl;
					rowsofnight = realrows + r;
					colsofnight = realcols + c;
					continue;
				}
			}
		}
		cout << "howmany found = " << howmanyfound << endl;
		cout << "r2 is= " << r << endl;
		cout << "c2 is= " << c << endl;
		if (howmanyfound > 0 && capture == false) {
			//valid move, no capture
			board[realrows][realcols] = 'N';
			board[rowsofnight][colsofnight] = ' ';
			rowsofnight = 0;
			colsofnight = 0;
			return true;
		}
		else if (howmanyfound > 0 && capture == true) {
			//valid move, there is a capture
			board[realrows][realcols] = 'N';
			board[rowsofnight][colsofnight] = ' ';
			rowsofnight = 0;
			colsofnight = 0;
			return true;
		}
		else {
			cout << "move was invalid." << endl;
			rowsofnight = 0;
			colsofnight = 0;
			return false;
		}

	case 'r':
		//white rook
		//if (board[realrows][realcols] == ' ') {
			//operation: find the rook
			//check right left up down max cols 49
		for (i = 0; i + realrows < 31; i++) {
			temprook = board[realrows + i][realcols];
			if (temprook == 'r') {
				howmanyfoundr++;
				rowsofrook = realrows + i;
				colsofrook = realcols;
				direction = 1;
			}
		}
		for (i = 0; i + realrows > 1; i--) {
			temprook = board[realrows + i][realcols];
			if (temprook == 'r') {
				howmanyfoundr++;
				rowsofrook = realrows + i;
				colsofrook = realcols;
				direction = 5;
			}
		}
		for (i = 0; i + realcols < 46; i++) {
			temprook = board[realrows][realcols + i];
			if (temprook == 'r') {
				howmanyfoundr++;
				rowsofrook = realrows;
				colsofrook = realcols + i;
				direction = 7;
			}
		}

		for (i = 0; i + realcols > 2; i--) {
			temprook = board[realrows][realcols + i];
			if (temprook == 'r') {
				howmanyfoundr++;
				rowsofrook = realrows;
				colsofrook = realcols + i;
				direction = 3;
			}
		}
		//find how many squares rook has to move
		coldiff = realcols - colsofrook;
		rowdiff = realrows - rowsofrook;
		cout << "row diff:" << rowdiff << endl;
		cout << "col diff:" << coldiff << endl;
		cout << "howmany rooks found = " << howmanyfoundr << endl;
		cout << "rook found at= " << rowsofrook << "," << colsofrook << endl;
		cout << "direction is: " << direction << endl;
		if (howmanyfoundr > 0 && checkIfAnything(direction, rowsofrook, colsofrook) == true && capture == false) {
			//valid move
			board[realrows][realcols] = 'r';
			board[rowsofrook][colsofrook] = ' ';
			cout << "move was valid." << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return true;
		}
		else if (howmanyfoundr > 0 && checkIfAnything(direction, rowsofrook, colsofrook) == true && capture == true) {
			//valid move
			board[realrows][realcols] = 'r';
			board[rowsofrook][colsofrook] = ' ';
			cout << "move was valid." << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return true;
		}
		else {
			cout << "move was invalid" << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return false;
		}
	case 'R':
		//black rook
		//if (board[realrows][realcols] == ' ') {
			//operation: find the rook
			//check right left up down max cols 49
		for (i = 0; i + realrows < 31; i++) {
			temprook = board[realrows + i][realcols];
			if (temprook == 'R') {
				howmanyfoundr++;
				rowsofrook = realrows + i;
				colsofrook = realcols;
				direction = 1;
			}
		}
		for (i = 0; i + realrows > 1; i--) {
			temprook = board[realrows + i][realcols];
			if (temprook == 'R') {
				howmanyfoundr++;
				rowsofrook = realrows + i;
				colsofrook = realcols;
				direction = 5;
			}
		}
		for (i = 0; i + realcols < 46; i++) {
			temprook = board[realrows][realcols + i];
			if (temprook == 'R') {
				howmanyfoundr++;
				rowsofrook = realrows;
				colsofrook = realcols + i;
				direction = 7;
			}
		}

		for (i = 0; i + realcols > 2; i--) {
			temprook = board[realrows][realcols + i];
			if (temprook == 'R') {
				howmanyfoundr++;
				rowsofrook = realrows;
				colsofrook = realcols + i;
				direction = 3;
			}
		}
		coldiff = realcols - colsofrook;
		rowdiff = realrows - rowsofrook;
		cout << "row diff:" << rowdiff << endl;
		cout << "col diff:" << coldiff << endl;
		cout << "howmany rooks found = " << howmanyfoundr << endl;
		cout << "rook found at= " << rowsofrook << "," << colsofrook << endl;
		cout << "direction is: " << direction << endl;
		//check if there are any pieces in that direction.

		if (howmanyfoundr > 0 && checkIfAnything(direction, rowsofrook, colsofrook) == true && capture == false) {
			//valid move, no capture
			board[realrows][realcols] = 'R';
			board[rowsofrook][colsofrook] = ' ';
			cout << "move was valid." << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return true;
		}
		else if (howmanyfoundr > 0 && checkIfAnything(direction, rowsofrook, colsofrook) == true && capture == true) {
			//valid move, there is a capture
			board[realrows][realcols] = 'R';
			board[rowsofrook][colsofrook] = ' ';
			cout << "move was valid." << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return true;
		}
		else {
			cout << "move was invalid" << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return false;
		}
		//}
	case 'z':
		//white bishop
		//operation: find the bishop

		i = 0;
		//if (board[realrows][realcols] == ' ') {
			//to the right top
		for (i = 0; i < 8; i++) {
			if ((board[realrows - i*rowconst][realcols + i*colconst] == 'z') && (realrows - i*rowconst > 1) && (realcols + i*colconst < 46)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows - i*rowconst;
				colsofbishop = realcols + i*colconst;
				direction = 6;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i1 is " << i << endl;
		i = 0;
		//to the left top
		for (i = 0; i < 8; i++) {
			if ((board[realrows - i*rowconst][realcols - i*colconst] == 'z') && (realrows - i*rowconst > 1) && (realcols - i*colconst > 2)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows - i*rowconst;
				colsofbishop = realcols - i*colconst;
				direction = 4;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i2 is " << i << endl;
		i = 0;
		//to the right bottom corner
		for (i = 0; i < 8; i++) {
			if ((board[realrows + i*rowconst][realcols + i*colconst] == 'z') && (realrows + i*rowconst < 31) && (realcols + i*colconst < 46)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows + i*rowconst;
				colsofbishop = realcols + i*colconst;
				direction = 8;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i3 is " << i << endl;
		i = 0;
		//to the left bottom corner
		for (i = 0; i < 8; i++) {
			if ((board[realrows + i*rowconst][realcols - i*colconst] == 'z') && (realrows + i*rowconst < 31) && (realcols - i*colconst > 2)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows + i*rowconst;
				colsofbishop = realcols - i*colconst;
				direction = 2;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i4 is " << i << endl;
		i = 0;
		coldiff = realcols - colsofbishop;
		rowdiff = realrows - rowsofbishop;
		cout << "row diff:" << rowdiff << endl;
		cout << "col diff:" << coldiff << endl;
		cout << "direction is:" << direction << endl;
		cout << "howmanybishop = " << howmanyfoundbishop << endl;
		cout << "bishop is at= " << rowsofbishop << "," << colsofbishop << endl;
		if (howmanyfoundbishop > 0 && checkIfAnything(direction, rowsofbishop, colsofbishop) == true && capture == false) {
			//valid move
			board[realrows][realcols] = 'z';
			board[rowsofbishop][colsofbishop] = ' ';
			cout << "Move was valid." << endl;
			rowsofbishop = 0;
			colsofbishop = 0;
			return true;
		}
		else if (howmanyfoundbishop > 0 && checkIfAnything(direction, rowsofbishop, colsofbishop) == true && capture == true) {
			//valid move, there is a capture
			board[realrows][realcols] = 'z';
			board[rowsofbishop][colsofbishop] = ' ';
			cout << "move was valid." << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return true;
		}
		else {
			cout << "Move was invalid." << endl;
			rowsofbishop = 0;
			colsofbishop = 0;
			return false;
		}

	case 'Z':
		i = 0;
		//if (board[realrows][realcols] == ' ') {
			//to the right top
		for (i = 0; i < 8; i++) {
			if ((board[realrows - i*rowconst][realcols + i*colconst] == 'Z') && (realrows - i*rowconst > 1) && (realcols + i*colconst < 46)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows - i*rowconst;
				colsofbishop = realcols + i*colconst;
				direction = 6;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i1 is " << i << endl;
		i = 0;
		//to the left top
		for (i = 0; i < 8; i++) {
			if ((board[realrows - i*rowconst][realcols - i*colconst] == 'Z') && (realrows - i*rowconst > 1) && (realcols - i*colconst > 2)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows - i*rowconst;
				colsofbishop = realcols - i*colconst;
				direction = 4;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i2 is " << i << endl;
		i = 0;
		//to the right bottom corner
		for (i = 0; i < 8; i++) {
			if ((board[realrows + i*rowconst][realcols + i*colconst] == 'Z') && (realrows + i*rowconst < 31) && (realcols + i*colconst < 46)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows + i*rowconst;
				colsofbishop = realcols + i*colconst;
				direction = 8;
				break;
			}
			else
			{
				continue;
			}
		}
		cout << "i3 is " << i << endl;
		i = 0;
		//to the left bottom corner
		for (i = 0; i < 8; i++) {
			if ((board[realrows + i*rowconst][realcols - i*colconst] == 'Z') && (realrows + i*rowconst < 31) && (realcols - i*colconst > 2)) {
				howmanyfoundbishop++;
				rowsofbishop = realrows + i*rowconst;
				colsofbishop = realcols - i*colconst;
				direction = 2;
				break;
			}
			else
			{
				continue;
			}
		}
		coldiff = realcols - colsofbishop;
		rowdiff = realrows - rowsofbishop;
		cout << "row diff:" << rowdiff << endl;
		cout << "col diff:" << coldiff << endl;
		cout << "i4 is " << i << endl;
		i = 0;
		cout << "direction is:" << direction << endl;
		cout << "howmanybishop = " << howmanyfoundbishop << endl;
		cout << "bishop is at= " << rowsofbishop << "," << colsofbishop << endl;
		if (howmanyfoundbishop > 0 && checkIfAnything(direction, rowsofbishop, colsofbishop) == true && capture == false) {
			//valid move
			board[realrows][realcols] = 'Z';
			board[rowsofbishop][colsofbishop] = ' ';
			rowsofbishop = 0;
			colsofbishop = 0;
			cout << "Move was valid." << endl;
			return true;
		}
		else if (howmanyfoundbishop > 0 && checkIfAnything(direction, rowsofbishop, colsofbishop) == true && capture == true) {
			//valid move, there is a capture
			board[realrows][realcols] = 'Z';
			board[rowsofbishop][colsofbishop] = ' ';
			cout << "move was valid." << endl;
			rowsofrook = 0;
			colsofrook = 0;
			direction = 0;
			return true;
		}
		else {
			cout << "Move was invalid." << endl;
			rowsofbishop = 0;
			colsofbishop = 0;
			return false;
		}
	case 'q':

		//if (board[realrows][realcols] == ' ') {
			//operation: find the queen, god save her.
		i = 3;
		o = 2;
		for (o = 2; o < 31; o++) {
			for (i = 3; i < 46; i++) {
				if (board[o][i] == 'q') {
					rowsofqueen = o;
					colsofqueen = i;
				}
			}
		}
		cout << "queen is at: " << rowsofqueen << "," << colsofqueen << endl;
		//find the direction queen wants to go
		coldiff = realcols - colsofqueen;
		rowdiff = realrows - rowsofqueen;
		direction = findDirection();
		checktemp = checkIfAnything(direction, rowsofqueen, colsofqueen);
		cout << "direction of the queen is: " << direction << endl;
		if ((capture == false) && (checktemp == true) && (direction != 0)) {
			//valid move, no capture
			board[realrows][realcols] = 'q';
			board[rowsofqueen][colsofqueen] = ' ';
			rowsofqueen = 0;
			colsofqueen = 0;
			cout << "Move was valid." << endl;
			direction = 0;
			return true;
		}
		else if ((capture == true) && (checktemp == false) && (direction != 0)) {
			//valid move with a capture
			board[realrows][realcols] = 'q';
			board[rowsofqueen][colsofqueen] = ' ';
			rowsofqueen = 0;
			colsofqueen = 0;
			cout << "Move was valid." << endl;
			direction = 0;
			return true;
		}
		else {
			cout << "Move was invalid." << endl;
			rowsofqueen = 0;
			colsofqueen = 0;
			direction = 0;
			return false;
		}

	case 'Q':
		//operation: find the queen, god save her.
		i = 3;
		o = 2;
		for (o = 2; o < 31; o++) {
			for (i = 3; i < 46; i++) {
				if (board[o][i] == 'Q') {
					rowsofqueen = o;
					colsofqueen = i;
				}
			}
		}
		cout << "queen is at: " << rowsofqueen << "," << colsofqueen << endl;
		coldiff = realcols - colsofqueen;
		rowdiff = realrows - rowsofqueen;
		direction = findDirection();
		checktemp = checkIfAnything(direction, rowsofqueen, colsofqueen);
		cout << "direction of the queen is: " << direction << endl;
		if ((capture == false) && (checktemp == true) && (direction != 0)) {
			//valid move, no capture
			board[realrows][realcols] = 'Q';
			board[rowsofqueen][colsofqueen] = ' ';
			rowsofqueen = 0;
			colsofqueen = 0;
			cout << "Move was valid." << endl;
			direction = 0;
			return true;
		}
		else if ((capture == true) && (checktemp == false) && (direction != 0)) {
			//valid move with a capture
			board[realrows][realcols] = 'Q';
			board[rowsofqueen][colsofqueen] = ' ';
			rowsofqueen = 0;
			colsofqueen = 0;
			cout << "Move was valid." << endl;
			direction = 0;
			return true;
		}
		else {
			cout << "Move was invalid." << endl;
			rowsofqueen = 0;
			colsofqueen = 0;
			direction = 0;
			return false;
		}

	case 'k':
		//operation: find the king.
		i = 3;
		o = 2;
		for (o = 2; o < 31; o++) {
			for (i = 3; i < 46; i++) {
				if (board[o][i] == 'k') {
					rowsofking = o;
					colsofking = i;
				}
			}
		}
		cout << "king is at: " << rowsofking << "," << colsofking << endl;
		coldiff = realcols - colsofking;
		rowdiff = realrows - rowsofking;
		direction = findDirection();
		checktemp = checkIfAnything(direction, rowsofking, colsofking);
		cout << "direction of the king is: " << direction << endl;
		if ((capture == false) && (checktemp == true) && (direction != 0)) {
			//valid move, no capture
			board[realrows][realcols] = 'k';
			board[rowsofking][colsofking] = ' ';
			rowsofking = 0;
			colsofking = 0;
			cout << "Move was valid." << endl;
			direction = 0;
			return true;
		}
		else if ((capture == true) && (checktemp == false) && (direction != 0)) {
			//valid move with a capture
			board[realrows][realcols] = 'k';
			board[rowsofking][colsofking] = ' ';
			rowsofking = 0;
			colsofking = 0;
			cout << "Move was valid." << endl;
			direction = 0;
			return true;
		}
		else {
			cout << "Move was invalid." << endl;
			rowsofqueen = 0;
			colsofqueen = 0;
			direction = 0;
			return false;
		}


	case 'K':
		if (board[realrows][realcols] == ' ') {
			//operation: find the king.
			i = 3;
			o = 2;
			for (o = 2; o < 31; o++) {
				for (i = 3; i < 46; i++) {
					if (board[o][i] == 'K') {
						rowsofking = o;
						colsofking = i;
					}
				}
			}
			cout << "king is at: " << rowsofking << "," << colsofking << endl;
			coldiff = realcols - colsofking;
			rowdiff = realrows - rowsofking;
			direction = findDirection();
			checktemp = checkIfAnything(direction, rowsofking, colsofking);
			cout << "direction of the king is: " << direction << endl;
			if ((capture == false) && (checktemp == true) && (direction != 0)) {
				//valid move, no capture
				board[realrows][realcols] = 'K';
				board[rowsofking][colsofking] = ' ';
				rowsofking = 0;
				colsofking = 0;
				cout << "Move was valid." << endl;
				direction = 0;
				return true;
			}
			else if ((capture == true) && (checktemp == false) && (direction != 0)) {
				//valid move with a capture
				board[realrows][realcols] = 'K';
				board[rowsofking][colsofking] = ' ';
				rowsofqueen = 0;
				colsofqueen = 0;
				cout << "Move was valid." << endl;
				direction = 0;
				return true;
			}
			else {
				cout << "Move was invalid." << endl;
				rowsofqueen = 0;
				colsofqueen = 0;
				direction = 0;
				return false;
			}
		}
	default:
		return false;
	}
}//function ending
		


void Board::toRealcols(char colz) {
	char tempcolumns = colz;

	if (tempcolumns == 'a') {
		realcols = 3;
	}
	if (tempcolumns == 'b') {
		realcols = 9;
	}
	if (tempcolumns == 'c') {
		realcols = 15;
	}
	if (tempcolumns == 'd') {
		realcols = 21;
	}
	if (tempcolumns == 'e') {
		realcols = 27;
	}
	if (tempcolumns == 'f') {
		realcols = 33;
	}
	if (tempcolumns == 'g') {
		realcols = 39;
	}
	if (tempcolumns == 'h') {
		realcols = 45;
	}


}

void Board::toRealrowz(char rowz) {

	char temprowz = rowz;

	if (temprowz == '1') {
		realrows = 30;
	}
	if (temprowz == '2') {
		realrows = 26;
	}
	if (temprowz == '3') {
		realrows = 22;
	}
	if (temprowz == '4') {
		realrows = 18;
	}
	if (temprowz == '5') {
		realrows = 14;
	}
	if (temprowz == '6') {
		realrows = 10;
	}
	if (temprowz == '7') {
		realrows = 6;
	}
	if (temprowz == '8') {
		realrows = 2;
	}

}


bool Board::checkIfAnything(int direction, int rowsofpiece, int colsofpiece) {
	int i = 0;
	int amountofsquares = 0;
	switch (direction) {
	case 1:
		//-4, 0
		rowdiff = -1 * rowdiff;
		amountofsquares = rowdiff / 4;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece - i*rowconst][colsofpiece] != ' ') {
				rowdiff = 0;
				coldiff = 0;
				return false;
			}
		}
		rowdiff = 0;
		coldiff = 0;
		return true;
	case 3:
		//0, +6
		amountofsquares = coldiff / colconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece][colsofpiece + i*colconst] != ' ') {
				rowdiff = 0;
				coldiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;
	case 5:
		//+4,0
		amountofsquares = rowdiff / rowconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece + i*rowconst][colsofpiece] != ' ') {
				coldiff = 0;
				rowdiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;
	case 7:
		//0, -6
		coldiff = -1 * coldiff;
		amountofsquares = coldiff / colconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece][colsofpiece - i*colconst] != ' ') {
				coldiff = 0;
				rowdiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;

	case 2:
		amountofsquares = coldiff / colconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece - i*rowconst][colsofpiece + i*colconst] != ' ') {
				coldiff = 0;
				rowdiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;
	case 6:
		amountofsquares = rowdiff / rowconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece + i*rowconst][colsofpiece - i*colconst] != ' ') {
				coldiff = 0;
				rowdiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;

	case 4:
		amountofsquares = rowdiff / rowconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece + i*rowconst][colsofpiece + i*colconst] != ' ') {
				coldiff = 0;
				rowdiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;

	case 8:
		rowdiff = -1 * rowdiff;
		amountofsquares = rowdiff / rowconst;
		for (i = 1; i <= amountofsquares; i++) {
			if (board[rowsofpiece - i*rowconst][colsofpiece - i*colconst] != ' ') {
				coldiff = 0;
				rowdiff = 0;
				return false;
			}
		}
		coldiff = 0;
		rowdiff = 0;
		return true;

	}
}

bool Board::isKingDead() {
	//search the board, return true if there is less than 2 kings.
	int i = 0;
	int o = 0;
	int kingamount = 0;
	for (o = 2; o < 31; o++) {
		for (i = 3; i < 46; i++) {
			if (board[o][i] == 'k' || board[o][i] == 'K') {
				kingamount++;
			}
		}
	}
	if (kingamount < 2) {
		//a king is dead
		return true;
	}
	else
		return false;


}

int Board::findDirection() {
	//-4,0
	if ((rowdiff < 0 && rowdiff%rowconst == 0) && coldiff == 0) {
		return 1;
	}
	//case 3 0,+6
	else if (rowdiff == 0 && (coldiff > 0 && coldiff%colconst == 0)) {
		return 3;
	}
	//case 5, +4,0
	else if ((rowdiff > 0 && rowdiff%rowconst == 0) && coldiff == 0) {
		return 5;
	}
	//case 7 0,-6
	else if (rowdiff == 0 && (coldiff < 0 && coldiff%colconst == 0)) {
		return 7;
	}
	//case 2
	else if ((rowdiff < 0 && rowdiff%rowconst == 0)&&(coldiff > 0 && coldiff%colconst == 0)) {
		if (((-1 * rowdiff) + coldiff) % 10 == 0) {
			return 2;
		}
		else
			return 0;
	}
	//case 4
	else if ((rowdiff > 0 && rowdiff%rowconst == 0) && (coldiff > 0 && coldiff%colconst == 0)) {
		if ((rowdiff + coldiff) % 10 == 0) {
			return 4;
		}
		else
			return 0;
	}
	//case 6
	else if ((rowdiff > 0 && rowdiff%rowconst == 0) && (coldiff < 0 && coldiff%colconst == 0)) {
		if ((rowdiff - coldiff) % 10 == 0) {
			return 6;
		}
		else
			return 0;
	}
	//case 8
	else if ((rowdiff < 0 && rowdiff%rowconst == 0) && (coldiff < 0 && coldiff%colconst == 0)){
		if ((-1 * rowdiff + -1 * coldiff) % 10 == 0) {
			return 8;
		}
		else
			return 0;
	}
	else {
		return 0;
	}

}

//function to check if pawn capture to the left or right
int Board::leftOrRight(char pawnfile){

	char tempfile = pawnfile;

	if (tempfile == 'a') {
		 return 3;
	}
	if (tempfile == 'b') {
		return 9;
	}
	if (tempfile == 'c') {
		return 15;
	}
	if (tempfile == 'd') {
		return 21;
	}
	if (tempfile == 'e') {
		return 27;
	}
	if (tempfile == 'f') {
		return 33;
	}
	if (tempfile == 'g') {
		return 39;
	}
	if (tempfile == 'h') {
		return 45;
	}
}


void Board::outro(bool player) {
	//false = white playing
	cout << "---------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "A king has been killed. GAME OVER." << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------" << endl;
	if (player == false) {
		cout << "Winner is BLACK player." << endl;
		cout << "Congratulations." << endl;
		cout << "Do you want to play again?" << endl;
		cout << "y for Yes, n for termination." << endl;
	}
	else {
		cout << "Winner is WHITE player." << endl;
		cout << "Congratulations." << endl;
		cout << "Do you want to play again?" << endl;
		cout << "y for Yes, n for termination." << endl;
	}


}

void Board::theVeryEnd() {
	cout << "#######################################################" << endl;
	cout << "#                      .::.                           #" << endl;
	cout << "#                      _::_                           #" << endl;
	cout << "#                    _/____\_                         #" << endl;
	cout << "#                    \      /                         #" << endl;
	cout << "#                     \____/                          #" << endl;
	cout << "#                     (____)                          #" << endl;
	cout << "#                      |  |                           #" << endl;
	cout << "#                      |  |                           #" << endl;
	cout << "#                     /    \                          #" << endl;
	cout << "#                    (______)                         #" << endl;
	cout << "#                   (________)                        #" << endl;
	cout << "#                   /________\        King            #" << endl;
	cout << "#######################################################" << endl;
	cout << "Thanks for playing. ###################################" << endl;
	cout << "#######################################################" << endl;


}