#include <iostream>
using namespace std;

class Player {
public:
	Player(bool x);
	void showPlayer();
	void togglePlayer();
	bool getPlayer();
	bool getPlayAgain();
	void setPlayAgain();
private:
	bool whoisplaying;
	bool playagain;
	char value;
};


//false means white is playing, true means black is playing. initial value of the
//whoisplaying will be false.
Player::Player(bool x) {
	whoisplaying = x;
	playagain = true;
}

void Player::showPlayer() {
	if (whoisplaying == false) {
		cout << "White is playing. Type in move." << endl;
	}
	else if (whoisplaying == true) {
		cout << "Black is playing. Type in move." << endl;
	}
	return;
}

void Player::togglePlayer() {
	whoisplaying = !whoisplaying;
}

bool Player::getPlayer() {
	return whoisplaying;
}

bool Player::getPlayAgain() {
	return playagain;
}

void Player::setPlayAgain() {
	cin >> value;
	if (value == 'y' || value == 'Y') {
		playagain = true;
	}
	else
		playagain = false;

}