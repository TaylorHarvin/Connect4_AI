#include "GameBoardAI.h"


using namespace std;

GameBoardAI::GameBoardAI(){
  srand(time(NULL));
  mainNN = NeuralNetwork(42,0,7,0.5,0.5);
}
GameBoardAI::~GameBoardAI(){

}

void GameBoardAI::ExpandNode(BoardNode parentNode){
  SlotType currBoardState[6][7];
  vector<vector<SlotType>> genBoardState;
  vector<Board> genNodes;
  int userMoveGuess = 0;
  vector<int> moves;
  BoardNode newNode;

  SlotType tmp;

  visited[string(parentNode)] = parentNode;

  if(parentNode.winner == EMPTY){
    for(int col = 0; col < 7; col++){
      if(GetNextRow(col,parentNode.board) > -1){
        genNodes.push_back(Board(parentNode.board.GetBoardState()));
        genNodes.back().PlayMove(col,AI);
        moves.push_back(col);

        //genBoardState = genNodes.back().GetBoardState();
        //printf("HCOST: %d\n",GetHCost(genBoardState,tmp));
        //genNodes.back().PrintBoard(AI,false);
      }
    }
    //printf("NODE SIZE:%d\n",(int)genNodes.size());
    //printf("NEW NODE PACK--------------\n");
    // Add nodes to the openMap
    for(int genNodeIndex = 0; genNodeIndex  < genNodes.size(); genNodeIndex++){
      genBoardState = genNodes[genNodeIndex].GetBoardState();
      if(visited.find(string(genNodes[genNodeIndex])) == visited.end()){

        newNode.ID = nextNodeId;
        nextNodeId++;


        //userMoveGuess = GuessPlayerAction_Random(genNodes[genNodeIndex],USER);
        userMoveGuess = GuessPlayerAction_NN(genNodes[genNodeIndex],USER);
        genNodes[genNodeIndex].PlayMove(userMoveGuess,USER);
        newNode.board.SetBoardState(genNodes[genNodeIndex].GetBoardState());

        /*printf("HCOST: %d\n",GetHCost(newNode.boardState));
        genNodes[genNodeIndex].PrintBoard(AI,false);*/

        newNode.hCost = GetHCost(newNode.board,newNode.winner);
        newNode.stepCost = parentNode.stepCost + 1;
        newNode.totalCost = newNode.hCost + newNode.stepCost;
        newNode.parentNode = &visited[string(parentNode)];
        newNode.movePlayed = moves[genNodeIndex];
        openList.push(newNode);
        //printf("HCOST: %d, step: %d\n",newNode.hCost,newNode.stepCost);
        //genNodes[genNodeIndex].PrintBoard(tmp,false);

      }
    }
  }
  //printf("BEST COST: %d, ID: %d, total Open size: %d\n",openList.top().hCost,openList.top().ID,(int)openList.size());
}

int GameBoardAI::GuessPlayerAction_Random(Board currBoard, SlotType otherPlayer){
  int slotGuess = rand() % 7;
  vector<vector<SlotType>> currBoardState;
	vector<int> guessList;
  currBoardState = currBoard.GetBoardState();
	int selectedRow = GetNextRow(slotGuess, currBoardState);

	if (selectedRow >= 0 && selectedRow < 6)
		currBoardState[selectedRow][slotGuess] = otherPlayer;
	else{
		guessList.push_back(slotGuess);
		do{
			do{
				slotGuess = rand() % 7;
			} while (find(guessList.begin(), guessList.end(), slotGuess) != guessList.end());
			selectedRow = GetNextRow(slotGuess, currBoardState);
		} while (selectedRow < 0 || selectedRow >= 6);
		currBoardState[selectedRow][slotGuess] = otherPlayer;
	}
	return slotGuess;
}


int GameBoardAI::GetNextRow(int col, Board currBoard){
  vector<vector<SlotType>> currBoardState = currBoard.GetBoardState();
	int i;
	for (i = 0; i < 6 && currBoardState[i][col] == EMPTY; i++){}

	if ((i < 6 && i > 0 && currBoardState[i-1][col] == EMPTY) || i == 6){
		return i-1;
	}
	else
		return -1;
}

int GameBoardAI::GenBestMove(Board currBoard){
  BoardNode currNode;
  int expandCount = 0;

  nextNodeId = 1;
  currNode.board.SetBoardState(currBoard.GetBoardState());
  currNode.stepCost = 0;
  currNode.hCost = GetHCost(currNode.board,currNode.winner);
  currNode.totalCost = currNode.stepCost + currNode.hCost;
  currNode.parentNode = NULL;
  currNode.ID = 0;

  openList.push(currNode);
  while(currNode.winner != AI && expandCount < MAX_EXPAND){
    currNode = openList.top();

    /*printf("TOP-----\n");
    printf("  0 1 2 3 4 5 6\n");
  	for (int row = 0; row < 6; row++){
      printf("%d ",row);
  		for (int col = 0; col < 7;col++){
  			switch (currNode.boardState[row][col]){
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
  	}*/

    ExpandNode(openList.top());
    openList.pop();
    expandCount++;
  }

  //printf("WIN: %d\n",(int)currNode.winner);

  BoardNode* currNodePtr  = &currNode;
  Board tmpBoard = Board(currNodePtr->board.GetBoardState());
  int moveToPlay = 0;

  while(currNodePtr->ID > 0){
    moveToPlay = currNodePtr->movePlayed;
    tmpBoard.PrintBoard(AI,false);
    currNodePtr = currNodePtr->parentNode;
    tmpBoard = Board(currNodePtr->board.GetBoardState());

  }

  //printf("NODE SIZE:%d, ex count: %d, visited size:%d , move: %d\n",(int)openList.size(),expandCount,(int)visited.size(),moveToPlay);


  visited.clear();
  while(openList.size() > 0)
    openList.pop();

  return moveToPlay;
}


int GameBoardAI::GetHCost(Board currBoard,SlotType& winner){
  vector<vector<SlotType>> boardState = currBoard.GetBoardState();
  int hCost = 0;
  int slotCounts[3] = {0,0,0};
  int currCost = 0;

  winner = EMPTY;

  for (int wRow = 0; wRow < 69; wRow++){
    for (int wCol = 0; wCol < 4; wCol++){
      slotCounts[boardState[WinningStates[wRow][wCol].first][WinningStates[wRow][wCol].second]]++;
    }

    if(slotCounts[EMPTY] == 4)
      currCost = 0;
    else if(slotCounts[USER] == 0 || (slotCounts[AI] > 0 && slotCounts[USER] > 0))
      currCost = pow(2, slotCounts[AI]) + slotCounts[EMPTY];
    // player has spots, but computer doesn't
    else
      currCost = slotCounts[EMPTY];

    // Store winner if one found
    if(slotCounts[AI] == 4){
      winner = AI;
      //printf("WINNER\n");
    }
    else if(slotCounts[USER] == 4)
      winner = USER;

    hCost += currCost;
    slotCounts[EMPTY] = 0;
    slotCounts[USER] = 0;
    slotCounts[AI] = 0;
  }
  return hCost;
}


int GameBoardAI::GuessPlayerAction_NN(Board currBoard, SlotType otherPlayer){
  mainNN.ProcInput(currBoard.GetFlatBoardState());
  vector<double> outNodes = mainNN.GetOutputLayer();
  double largestVal = 0;
  int mostLikelyNextMove = 0;

  for(int outNodeIndex = 0; outNodeIndex < outNodes.size(); outNodeIndex++){
    if(outNodes[outNodeIndex] > largestVal){
      largestVal = outNodes[outNodeIndex];
      mostLikelyNextMove = outNodeIndex;
    }
  }
  return mostLikelyNextMove;
}

void GameBoardAI::Learn(int userPlayRow, int userPlayCol, vector<double> currFlatBoard){
  vector<double> userPlay;
  userPlay.resize(7);
  for(int i = 0 ; i < userPlay.size(); i++){
    if(i == userPlayCol)
      userPlay[i] = 1;
    else
      userPlay[i] = 0;
  }

  currFlatBoard[userPlayRow*6 + userPlayCol] = EMPTY; // Remove move temporarily
  mainNN.Train(currFlatBoard,currFlatBoard);

  currFlatBoard[userPlayRow*6 + userPlayCol] = 0.5;  // Restore move after training
}
