#ifndef TICTACTOE_H
#define TICTACTOE_H

enum ButtonState {
	bsNone,
	bsCross,
	bsCircle,
	bsDraw,
};

class TicTacToe {
	public:
		TicTacToe();
		~TicTacToe();
		
		ButtonState currentplayer;
		ButtonState field[3][3];
		int crossscore;
		int circlescore;
		bool gamewon;
		
		ButtonState GetWinner();
		void NextPlayer();
		void ResetField();
};

#endif
