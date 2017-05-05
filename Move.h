#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Move {

public:
	Move(char *str = "");
	~Move();
	void readMove();
	void displayMove();
	char checkPiece(bool whoseturn);
	void checkSquare();
	void checkCapture();
	char getCols();
	char getRows();
	char getPiece();
	bool getCapture();
	bool searchString();
	char getPawnFile();
private:
	char *move_string;
	char piece;
	char cols;
	char rows;
	bool capture;
	char pawnfile;
};

Move::Move(char *str) {
	move_string = new char[strlen(str) + 1];
	strcpy(move_string, str);
	capture = false;
	pawnfile = 'o';
}

Move::~Move() {
	delete move_string;
}

void Move::readMove() {

	cin >> move_string;
	return;
}
void Move::displayMove() {
	cout << move_string << endl;
	return;
}

void Move::checkCapture(){

	if (move_string[1] == 'x') {
		capture = true;
	}
	else
		capture = false;
	return;
}


char Move::checkPiece(bool whoseturn) {
	int len;
	char temp;
	bool tempcap;
	len = strlen(move_string);
	checkCapture();
	if (len == 2) {
		capture = false;
		cols = move_string[0];
		rows = move_string[1];
		if (whoseturn == false) {
			temp = 'p';
			piece = temp;
			cout << temp << endl;
			return temp;
		}
		else {
			temp = 'P';
			piece = temp;
			cout << temp << endl;
			return temp;
		}
	}
	if (len == 3){
		capture = false;
		cols = move_string[1];
		rows = move_string[2];
		if (whoseturn == false) {
			temp = move_string[0];
			piece = temp;
			cout << temp << endl;
			return temp;
		}
		else {
			temp = move_string[0];
			temp = temp - 32;
			piece = temp;
			cout << temp << endl;
			return temp;
		}

	}

	if (len == 4) {
		tempcap = searchString();
		if (tempcap == true) {
			temp = move_string[0];
			pawnfile = move_string[0];
			cols = move_string[2];
			rows = move_string[3];
			if (temp == 'a' || temp == 'b' || temp == 'c' || temp == 'd' || temp == 'e' || temp == 'f' || temp == 'g' || temp == 'h') {
				//pawn capture
				if (whoseturn == false) {
					temp = 'p';
					piece = temp;
					cout << temp << endl;
					return temp;
				}
				else {
					temp = 'P';
					piece = temp;
					cout << temp << endl;
					return temp;
				}

			}
			else {
				//capture by other pieces
				if (whoseturn == false) {
					temp = move_string[0];
					piece = temp;
					cout << temp << endl;
					return temp;
				}
				else {
					temp = move_string[0];
					temp = temp - 32;
					piece = temp;
					cout << temp << endl;
					return temp;
				}
			}
		}
	
	}	
}

void Move::checkSquare() {

	if (capture) {
		rows = move_string[2];
		cols = move_string[3];
	}
	else {

		rows = move_string[1];
		cols = move_string[2];
	}
	return;
}

char Move::getRows() {
	return rows;
}

char Move::getCols() {
	return cols;
}

char Move::getPiece() {
	return piece;
}

bool Move::getCapture() {
	return capture;
}

//true means there is an x in the string
bool Move::searchString() {
	char temp;
	int i = 0;
	while (i < strlen(move_string)) {
		temp = move_string[i];
		if (temp == 'x') {
			return true;
		}
		i++;
	}
	return false;
}

char Move::getPawnFile() {
	return pawnfile;
}