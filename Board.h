#include "SlotType.h"
#include "WinningStates.h"

#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

class Board{
  public:
    Board();
    Board(std::vector<std::vector<SlotType>> boardStateCpy);
    ~Board();
    void Clear();
    int PlayMove(int col, SlotType playerType);
    void PrintBoard(SlotType player, bool gameOver);
    operator string() const{
      string boardKey = "";

      for (int row = 0; row < 6; row++){
    		for (int col = 0; col < 7; col++){
          boardKey += to_string(boardState[row][col]);
        }
      }
      return boardKey;
    }
    std::vector<std::vector<SlotType>> GetBoardState();
    std::vector<double> GetFlatBoardState();

    void SetBoardState(std::vector<std::vector<SlotType>> boardStateCpy);

  private:
    std::vector<std::vector<SlotType>> boardState;
    SlotType winner;
    bool SlotEmpty(int row, int col);
    bool CheckWin(SlotType player);

};
