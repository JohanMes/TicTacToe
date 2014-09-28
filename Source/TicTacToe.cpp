#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	currentplayer = bsCross;
	ResetField();
	crossscore = 0;
	circlescore = 0;
}

TicTacToe::~TicTacToe() {
	
}

ButtonState TicTacToe::GetWinner() {
	
	gamewon = true;
	
	// Check straight wins, horizontal
	for(int i = 0;i < 3;i++) {
		
		// Horizontal
		if(field[i][0] != bsNone && field[i][0] == field[i][1] && field[i][1] == field[i][2]) {
			return field[i][0];
		}
		
		// Vertical
		if(field[0][i] != bsNone && field[0][i] == field[1][i] && field[1][i] == field[2][i]) {
			return field[0][i];
		}
	}
	
	// Check diagonals
	if(field[0][0] != bsNone && field[0][0] == field[1][1] && field[1][1] == field[2][2]) {
		return field[0][0];
	}
	if(field[0][2] != bsNone && field[0][2] == field[1][1] && field[1][1] == field[2][0]) {
		return field[0][2];
	}
	
	// Check if everything is set
	for(int i = 0;i < 3;i++) {
		for(int j = 0;j < 3;j++) {
			if(field[i][j] == bsNone) { // nope
				gamewon = false;
				return bsNone;
			}
		}
	}
	
	return bsDraw;
}

void TicTacToe::NextPlayer() {
	switch(currentplayer) {
		case bsCross: {
			currentplayer = bsCircle;
			break;
		}
		case bsCircle: {
			currentplayer = bsCross;
			break;
		}
		default: {
			currentplayer = bsCross; // default player
			return;
		}
	}
}

void TicTacToe::ResetField() {
	for(int i = 0;i < 3;i++) {
		for(int j = 0;j < 3;j++) {
			field[i][j] = bsNone;
		}
	}
	gamewon = false;
}
