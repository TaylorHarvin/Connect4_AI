#include <map>
#include <queue>
#include <string>
#include "SlotType.h"
#include "Board.h"
#include <random>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include "NeuralNetwork.h"


#define MAX_EXPAND 500



struct BoardNode{
  //SlotType boardState[6][7];
  Board board = Board();
  int ID;
  int stepCost;
  int hCost;
  int totalCost;
  SlotType winner = EMPTY;
  int movePlayed = 0;


  BoardNode* parentNode;

  void CopyBoardState(std::vector<std::vector<SlotType>> otherBoardState){
    board.SetBoardState(otherBoardState);
  }

  operator string() const{
    return string(board);
  }
};


// Compare for the priority queue
struct compLessThan{
	// Compare for the priority queue
	bool operator()(BoardNode n1, BoardNode n2) {
		//int fVal1 = n1.hCost + n1.stepCost;	// first node f value
		//int fVal2 = n2.hCost + n2.stepCost;	// second node f value
		// compare the two nodes' f values
		// if they are equal -- check the ID values
		if (n1.totalCost > n2.totalCost)
			return true;
		else if (n1.totalCost == n2.totalCost) {
			if (n1.ID > n2.ID)
				return true;
		}
		else
			return false;
		return false;
	}
};


class GameBoardAI{
  public:
    GameBoardAI();
    ~GameBoardAI();
    int GenBestMove(Board currBoard);
    void ExpandNode(BoardNode currNode);
    int GuessPlayerAction_Random(Board currBoard, SlotType otherPlayer);
    int GuessPlayerAction_NN(Board currBoard, SlotType otherPlayer);
    void Learn(int userPlayRow, int userPlayCol, std::vector<double> currFlatBoard);
  private:
    int GetNextRow(int col, Board currBoard);
    int GetHCost(Board currBoard,SlotType& winner);
    std::map<std::string,BoardNode> visited;
    std::priority_queue<BoardNode,std::vector<BoardNode>,compLessThan> openList;
    int nextNodeId = 0;
    NeuralNetwork mainNN;


};
