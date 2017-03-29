#include "Board.h"


using namespace std;

Board::Board(){
  boardState.resize(6);
  for(int row = 0 ; row < 6; row++){
    boardState[row].resize(7);
  }
  Clear();
  winner = EMPTY;

}
Board::~Board(){

}

Board::Board(vector<vector<SlotType>> boardStateCpy){
  boardState.resize(6);
  for(int row = 0 ; row < 6; row++){
    boardState[row].resize(7);
  }

  for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
      boardState[row][col] = boardStateCpy[row][col];
    }
  }
}

void Board::SetBoardState(vector<vector<SlotType>> boardStateCpy){
  for (int row = 0; row < 6; row++){
    for (int col = 0; col < 7; col++){
      boardState[row][col] = boardStateCpy[row][col];
    }
  }
}


void Board::Clear(){
  for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
      boardState[row][col] = EMPTY;
    }
  }
}


int Board::PlayMove(int col, SlotType playerType){
  int currRow = 0;


  // Check if valid column
  if(col < 0 || col > 6)
    return false;

  // Find the next possible row for play in the given col
  for (currRow = 0; currRow < 6; currRow++){
    if(!SlotEmpty(currRow, col)){
      currRow--;
      break;
    }
  }

  // Col empty -- set row as bottom
  if(currRow >= 6)
    currRow = 5;

  // If the column has an empty/valid spot, play the move
  // else return error
  if(currRow >= 0){
    //printf("ROW: %d, COL: %d\n\n",currRow, col);
    boardState[currRow][col] = playerType;
    return currRow;
  }
  return -1;
}

void Board::PrintBoard(SlotType player, bool gameOver){
	if (!gameOver)
		printf("Player: %d\n", player);
	printf("  0 1 2 3 4 5 6\n");
	for (int row = 0; row < 6; row++){
    printf("%d ",row);
		for (int col = 0; col < 7;col++){
			switch (boardState[row][col]){
				case EMPTY:
					printf("  ");
					break;
				case USER:
					printf("* ");
					break;
				case AI:
					printf("# ");
					break;
			}
		}
		printf("\n");
	}
}


bool Board::SlotEmpty(int row, int col){
  if(boardState[row][col] == EMPTY)
    return true;
  else
    return false;
}

bool Board::CheckWin(SlotType player){
	bool currWinner = false;
	int j = 0;

	for (int i = 0; !winner && i < 69; i++){
		for (j = 0; j < 4; j++){
			if (boardState[WinningStates[i][j].first][WinningStates[i][j].second] != player){
				break;
			}
		}
		if (j >= 4){
			return true;
		}
	}
	//return currWinner;
	return false;
}


vector<vector<SlotType>> Board::GetBoardState(){
  return boardState;
}


vector<double> Board::GetFlatBoardState(){
  vector<double> flatBoard;
  flatBoard.resize(42);

  for(int row = 0; row < boardState.size(); row++){
    for(int col = 0; col < boardState[row].size(); col++){
      flatBoard[row*boardState[row].size()+col] = boardState[row][col];
    }
  }

  return flatBoard;
}
