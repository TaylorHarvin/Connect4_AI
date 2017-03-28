#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <math.h>
#include <random>
#include <algorithm>

using namespace std;


enum SlotType {EMPTY, RED, BLACK};
SlotType board[6][7];
const pair<int, int> P_CHECK[69][4] = { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
{ { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 } },
{ { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 } },
{ { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 } },
{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 } },
{ { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 } },
{ { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 } },
{ { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 } },
{ { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 } },
{ { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 } },
{ { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 } },
{ { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 } },
{ { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } },
{ { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 } },
{ { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } },
{ { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 } },
{ { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } },
{ { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 } },
{ { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } },
{ { 4, 3 }, { 4, 4 }, { 4, 5 }, { 4, 6 } },
{ { 5, 0 }, { 5, 1 }, { 5, 2 }, { 5, 3 } },
{ { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 } },
{ { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 } },
{ { 5, 3 }, { 5, 4 }, { 5, 5 }, { 5, 6 } },
{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
{ { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 } },
{ { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 } },
{ { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } },
{ { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 } },
{ { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 } },
{ { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 } },
{ { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 } },
{ { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 2 } },
{ { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } },
{ { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 } },
{ { 2, 3 }, { 3, 3 }, { 4, 3 }, { 5, 3 } },
{ { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 } },
{ { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 } },
{ { 2, 4 }, { 3, 4 }, { 4, 4 }, { 5, 4 } },
{ { 0, 5 }, { 1, 5 }, { 2, 5 }, { 3, 5 } },
{ { 1, 5 }, { 2, 5 }, { 3, 5 }, { 4, 5 } },
{ { 2, 5 }, { 3, 5 }, { 4, 5 }, { 5, 5 } },
{ { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 } },
{ { 1, 6 }, { 2, 6 }, { 3, 6 }, { 4, 6 } },
{ { 2, 6 }, { 3, 6 }, { 4, 6 }, { 5, 6 } },
{ { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } },
{ { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } },
{ { 0, 2 }, { 1, 3 }, { 2, 4 }, { 3, 5 } },
{ { 0, 3 }, { 1, 4 }, { 2, 5 }, { 3, 6 } },
{ { 1, 0 }, { 2, 1 }, { 3, 2 }, { 4, 3 } },
{ { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } },
{ { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 } },
{ { 1, 3 }, { 2, 4 }, { 3, 5 }, { 4, 6 } },
{ { 2, 0 }, { 3, 1 }, { 4, 2 }, { 5, 3 } },
{ { 2, 1 }, { 3, 2 }, { 4, 3 }, { 5, 4 } },
{ { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 } },
{ { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 } },
{ { 0, 6 }, { 1, 5 }, { 2, 4 }, { 3, 3 } },
{ { 0, 5 }, { 1, 4 }, { 2, 3 }, { 3, 2 } },
{ { 0, 4 }, { 1, 3 }, { 2, 2 }, { 3, 1 } },
{ { 0, 3 }, { 1, 2 }, { 2, 1 }, { 3, 0 } },
{ { 1, 6 }, { 2, 5 }, { 3, 4 }, { 4, 3 } },
{ { 1, 5 }, { 2, 4 }, { 3, 3 }, { 4, 2 } },
{ { 1, 4 }, { 2, 3 }, { 3, 2 }, { 4, 1 } },
{ { 1, 3 }, { 2, 2 }, { 3, 1 }, { 4, 0 } },
{ { 2, 6 }, { 3, 5 }, { 4, 4 }, { 5, 3 } },
{ { 2, 5 }, { 3, 4 }, { 4, 3 }, { 5, 2 } },
{ { 2, 4 }, { 3, 3 }, { 4, 2 }, { 5, 1 } },
{ { 2, 3 }, { 3, 2 }, { 4, 1 }, { 5, 0 } } };






struct PathNode{
	int ID;
	int hCost;
	int stepCost;
	int fullCost;
	int moveCol;
	bool winningNode;
	PathNode* parent;
	SlotType nodeBoard[6][7];
	int moveCol_guess;
	
	
	
	PathNode(int newID, int newstepCost, int newmoveCol, bool newwinningNode, PathNode* newparent){
		ID = newID;
		stepCost = newstepCost;
		moveCol = newmoveCol;
		winningNode = newwinningNode;
		parent = newparent;
	}

	void copyBoard(SlotType currBoard[6][7]){
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 7; j++){
				nodeBoard[i][j] = currBoard[i][j];
			}
		}
	}
};



const int EXPAND_CUTOFF = 500;
int currentMoveGuess = -1;
// Neural network variables
double LEARNING_RATE = 0.8;
double MOMENT_RATE = 0;

const int NUM_OUTPUT = 7;
const int NUM_HIDDEN = 41;
const int NUM_INPUT = 42;

double nnInToOutWeight[NUM_INPUT][NUM_OUTPUT];	// Just for the no hidden layer test
//double nnInToHiddenWeights[NUM_INPUT][NUM_HIDDEN]; // Rows --> input nodes, Cols --> hidden nodes
//double nnHiddelLayer[NUM_HIDDEN];
//double nnHiddenDeltas[NUM_HIDDEN];
//double nnHiddenToOutWeights[NUM_HIDDEN][NUM_OUTPUT];
double nnOutputLayer[NUM_OUTPUT];
double nnOutDeltas[NUM_OUTPUT];
// ^^^Neural network variables


default_random_engine gen;
uniform_real_distribution<double> distribution(0,1);


// Basic sigmoid activation function
double Activation(double nodeVal){
	return (1 / (1 + pow(exp(1.0), -nodeVal)));
}

// Dervivative of the sigmoid activation function
double ActivationPrime(double actVal){
	return Activation(actVal)*(1.0 - Activation(actVal));
}


// Set the random weights of the 
void InitNeuralNetwork(){
	// Init in to hidden
	for (int row = 0; row < NUM_INPUT; row++){
		for (int col = 0; col < NUM_OUTPUT; col++){
			nnInToOutWeight[row][col] = distribution(gen);
		}
	}
}

// Scale the input values
double Normalize(double val, double low, double high, double targetLow, double targetHigh){
	double numer = (val - low)*(targetHigh - targetLow);
	double denom = (high - low);
	return (numer / denom);
}


void ProcessNNInput(SlotType currBoard[6][7]){
	int boardRow = 0;
	int boardCol = 0;


	// Calculate hidden layer vals from input
	/*for (int hid = 0; hid < NUM_HIDDEN; hid++){
		nnHiddelLayer[hid] = 0;
		// Sum up all connections from all input to an individual hidden node
		for (int in = 0; in < NUM_INPUT; in++){
			boardRow = in / 7;
			boardCol = in % 7;
			nnHiddelLayer[hid] += Normalize(currBoard[boardRow][boardCol], 0, 2, 0, 1) * nnInToHiddenWeights[in][hid];
		}
	}*/


	// Calculate input to output
	for (int out = 0; out < NUM_OUTPUT; out++){
		nnOutputLayer[out] = 0;
		// Sum up all connections from all input to an individual out node
		for (int in = 0; in < NUM_INPUT; in++){
			boardRow = in / 7;
			boardCol = in % 7;
			nnOutputLayer[out]  += Normalize(currBoard[boardRow][boardCol], 0, 2, 0, 1) * nnInToOutWeight[in][out];
		}
	}
}

double MeanSquaredError(int userSelectedSlot){
	double finalError = 0;

	for (int outIndex = 0; outIndex < 7; outIndex++){
		if (outIndex != userSelectedSlot)
			finalError += (0 - nnOutputLayer[outIndex]);
		else
			finalError += (1 - nnOutputLayer[outIndex]);
	}
	finalError *= (1.0 / 7.0);
	return finalError;
}


void ApplyWeightChange(){
	// Apply the weight change for hidden to output
	for (int in = 0; in < NUM_INPUT; in++){
		for (int out = 0; out < NUM_OUTPUT; out++){
			nnInToOutWeight[in][out] = LEARNING_RATE*nnOutDeltas[out] /*+ MOMENT_RATE*prevWeightChange[nodeIndex]*/;
		}
	}

	// Apply the weight change for input to hidden
	/*for (int in = 0; in < NUM_INPUT; in++){
		for (int hid = 0; hid < NUM_HIDDEN; hid++){
			nnInToHiddenWeights[in][hid] = LEARNING_RATE*nnHiddenDeltas[hid] + MOMENT_RATE*prevWeightChange[nodeIndex];
		}
	}*/
}

void TrainNeuralNet(int userSelectedSlot){

	// Calculate output deltas
	for (int outIndex = 0; outIndex < 7; outIndex++){
		if (outIndex != userSelectedSlot)
			nnOutDeltas[outIndex] = (0 - nnOutputLayer[outIndex])*ActivationPrime(nnOutputLayer[outIndex]);
		else
			nnOutDeltas[outIndex] = (1 - nnOutputLayer[outIndex])*ActivationPrime(nnOutputLayer[outIndex]);
	}

	// Calculate hidden deltas
	/*for (int hid = 0; hid < NUM_HIDDEN; hid++){
		nnHiddenDeltas[hid] = 0;
		for (int out = 0; out < NUM_OUTPUT; out++){
			nnHiddenDeltas[hid] += nnHiddenToOutWeights[hid][out]*nnOutDeltas[out];
		}
		nnHiddenDeltas[hid] *= ActivationPrime(nnHiddelLayer[hid]);
	}*/

	ApplyWeightChange();
}




// Compare for the priority queue
struct compLessThan{
	// Compare for the priority queue
	bool operator()(PathNode* n1, PathNode* n2) {
		int fVal1 = n1->hCost + n1->stepCost;	// first node f value
		int fVal2 = n2->hCost + n2->stepCost;	// second node f value
		// compare the two nodes' f values
		// if they are equal -- check the ID values
		if (fVal1 > fVal2)
			return true;
		else if (fVal1 == fVal2) {
			if (n1->ID > n2->ID)
				return true;
		}
		else
			return false;
		return false;
	}
};




priority_queue<PathNode*, vector<PathNode*>, compLessThan> openList;
vector<PathNode*> closedList;



void ClearOpenAndClosedLists(){
	PathNode* currNode;
	for (int i=0; i < closedList.size(); i++){
		currNode = closedList[i];
		delete currNode;
	}
	closedList.clear();

	while(openList.size() > 0){
		currNode = openList.top();
		openList.pop();
		delete currNode;
	}
}


void ClearBoard(){
	for (int i = 0; i < 6;i++){
		for (int j = 0; j < 7; j++){
			board[i][j] = EMPTY;
		}
	}
}

void PrintBoard(SlotType player, bool gameOver){
	if (!gameOver)
		cout << "Player: " << player << endl;
	cout << "0 1 2 3 4 5 6" << endl;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 7; j++){
			switch (board[i][j]){
				case EMPTY:
					cout << "  ";
					break;
				case RED:
					cout << "* ";
					break;
				case BLACK:
					cout << "# ";
					break;
			}
		}
		cout << endl;
	}
}

int GetNextRow(int col, SlotType currBoard[6][7]){
	int i;
	for (i = 0; i < 6 && currBoard[i][col] == EMPTY; i++){}

	if ((i < 6 && i > 0 && currBoard[i-1][col] == EMPTY) || i == 6){
		return i-1;
	}
	else
		return -1;
}





bool CheckWin(SlotType player){
	bool winner = false;
	int j = 0;

	for (int i = 0; !winner && i < 69; i++){
		for (j = 0; j < 4; j++){
			if (board[P_CHECK[i][j].first][P_CHECK[i][j].second] != player){
				break;
			}
		}
		if (j >= 4){
			winner = true;
		}
	}
	

	return winner;
}

double GetNumUsedSpots(SlotType currBoard[6][7]){
	int usedCount = 0;

	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
			if (currBoard[row][col] != EMPTY)
				usedCount++;
		}
	}
	return usedCount;
}



int GetCost(int col, int row, const SlotType player, SlotType& winner, SlotType currBoard[6][7]){
	winner = EMPTY;
	int currCost = 0;
	int costToGoal = 0;
	int otherCount = 0;
	int playerCount = 0;
	int chancePenalty = 0;
	int emptyCount = 0;
	//currBoard[row][col] = player;

	for (int i = 0; !winner && i < 69; i++){
		currCost = 0;
		otherCount = 0;
		playerCount = 0;
		emptyCount = 0;

		for (int j = 0; j < 4; j++){
			if (currBoard[P_CHECK[i][j].first][P_CHECK[i][j].second] != player){
				if (currBoard[P_CHECK[i][j].first][P_CHECK[i][j].second] == EMPTY)
					emptyCount++;
				else{
					//currCost += 2;
					otherCount++;
				}
			}
			else{ // This is the computer player
				//currCost--;
				playerCount++;
			}
		}
		// Computer wins here
		if (playerCount == 4){
			winner = player;
		}
		else if (otherCount == 4){ // User wins
			if (player == RED)
				winner = BLACK;
			else
				winner = RED;
		}
		//currCost += otherCount;
		/*for (int index = 0; index < otherCount; index++){
		//currCost -= rand() % 2;
		//currCost--;
		currCost -= rand() % (int) pow(otherCount,3);
		}*/
		if (emptyCount == 4)
			//currCost = emptyCount;
			currCost = 0;
		else if (playerCount == 0 || (otherCount > 0 && playerCount > 0))
			currCost = pow(2, otherCount) + emptyCount;
			//currCost = otherCount;
		else // player has spots, but computer doesn't 
			currCost = emptyCount;

		costToGoal += currCost;
	}

	//currBoard[row][col] = EMPTY;
	if (costToGoal < 0)
		costToGoal = 0;
	return costToGoal;
}



bool NodeVisited(PathNode* currNode){
	vector<PathNode*>::iterator iter;
	int matchCount = 0;

	for (iter = closedList.begin(); iter != closedList.end(); iter++, matchCount = 0){
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 7; j++){
				if (currNode->nodeBoard[i][j] == (*iter)->nodeBoard[i][j])
					matchCount++;
			}
		}
		if (matchCount >= 42){
			return true;
		}
	}
}


int GuessPlayerAction_NN(SlotType currBoard[6][7], SlotType otherPlayer){
	int slotGuess = -1;
	int tieIndex = 0;
	int selectedRow = -1;
	// Generate the output nodes based on the given board
	ProcessNNInput(currBoard);
	vector<int> tieList;
	double highestOut = 0;

	// Go through all output nodes and decide the guessed player action
	for (int outIndex = 0; outIndex < NUM_OUTPUT; outIndex++){
		if (nnOutputLayer[outIndex] == highestOut){
			tieList.push_back(outIndex);
		}
		else if (nnOutputLayer[outIndex] > highestOut){
			highestOut = nnOutputLayer[outIndex];
			tieList.clear();
			tieList.push_back(outIndex);
		}
	}

	tieIndex = rand() % tieList.size();
	slotGuess = tieList[tieIndex];
	selectedRow = GetNextRow(slotGuess, currBoard);

	currBoard[selectedRow][slotGuess] = otherPlayer;
	tieList.clear();
	return slotGuess;
}


int GuessPlayerAction_Random(SlotType currBoard[6][7], SlotType otherPlayer){
	int slotGuess = rand() % 7;
	vector<int> guessList;
	int selectedRow = GetNextRow(slotGuess, currBoard);
	if (selectedRow >= 0 && selectedRow < 6)
		currBoard[selectedRow][slotGuess] = otherPlayer;
	else{
		guessList.push_back(slotGuess);
		do{
			do{
				slotGuess = rand() % 7;
			} while (find(guessList.begin(), guessList.end(), slotGuess) != guessList.end());
			selectedRow = GetNextRow(slotGuess, currBoard);
		} while (selectedRow < 0 || selectedRow >= 6);
		currBoard[selectedRow][slotGuess] = otherPlayer;
	}
	return slotGuess;
}



int GuessPlayerAction(SlotType currBoard[6][7], SlotType otherPlayer){
	int playerGuess = -1;
	//playerGuess = GuessPlayerAction_Random(currBoard, otherPlayer);
	playerGuess = GuessPlayerAction_NN(currBoard, otherPlayer);

	return playerGuess;
}


bool boardPlayable(SlotType currBoard[6][7]){
	int numAvailiable = 0;
	for (int i = 0; i < 6; i++){
		if (currBoard[0][i] == EMPTY)
			numAvailiable++;
	}
	if (numAvailiable > 0)
		return true;
	else
		return false;
}



bool Expand(PathNode* parentNode, SlotType& player){
	if (parentNode == NULL){
		cerr << "ERROR" << endl;
	}

	priority_queue<PathNode*, vector<PathNode*>, compLessThan> preOpenList;
	int emptyRow = 0;
	int bestCol = 0;
	int bestRow = 0;
	int highestVal = 0;
	pair < int, SlotType > goalCost;
	PathNode* currNode = NULL;
	SlotType otherPlayer;
	int slotGuess = -1;

	if (player == BLACK){
		otherPlayer = RED;
	}
	else
		otherPlayer = BLACK;

	int numNodesGenerated = 0;

	closedList.push_back(parentNode);

	for (int i = 0; i < 7; i++){
		emptyRow = GetNextRow(i, parentNode->nodeBoard);
		
		// If the row is not full -- create the new board
		if (emptyRow >= 0 && emptyRow < 6){
			currNode = new PathNode(parentNode->ID + 1, parentNode->stepCost + 1, i, false, parentNode);
			currNode->copyBoard(parentNode->nodeBoard);
			currNode->nodeBoard[emptyRow][i] = player;
			slotGuess = GuessPlayerAction(currNode->nodeBoard, otherPlayer);
			// For some reason, the above function clears parent pointer this fixes that
			currNode->parent = parentNode;

			if (!NodeVisited(currNode)){
				goalCost.first = GetCost(i, emptyRow, player, goalCost.second, currNode->nodeBoard);
				currNode->hCost = goalCost.first;
				currNode->fullCost = currNode->hCost + currNode->stepCost;
				if (goalCost.second == player || goalCost.second == EMPTY){
					currNode->winningNode = goalCost.second;
					currNode->moveCol_guess = slotGuess;
					preOpenList.push(currNode);
					numNodesGenerated++;
				}
				else{
					delete currNode;
				}
			}
			else{ // node already visited
				delete currNode;
			}
		}
		else{ // Deadend node with no win -- all slots filled
			//delete currNode;
		}
		/*if (goalCost[i].first > highestVal){
			bestCol = i;
			bestRow = emptyRow;
			highestVal = goalCost[i].first;
		}*/

	}


	openList.push(preOpenList.top());
	preOpenList.pop();
	// Clear the temp open list
	while (preOpenList.size() > 0){
		delete preOpenList.top();
		preOpenList.pop();
	}

	if (numNodesGenerated > 0)
		return true;
	else
		return false;
}





int PerformSearch(SlotType& player){
	PathNode* currNode;
	PathNode* prevNode = NULL;
	pair<int, int> nextMove;

	currNode = new PathNode(0, 0, -1, false, NULL);
	currNode->copyBoard(board);
	//openList.push(currNode);
	//const int cutoff = 1;
	int count = 0;

	while (!currNode->winningNode && count < EXPAND_CUTOFF){
		Expand(currNode, player);
		if (openList.size() > 0){
			currNode = openList.top();
			openList.pop();
			count++;
		}
		else{
			break;
		}
	}
	//currNode = openList.top();
	//openList.pop();
	int bestCol = -1;
	if (currNode != NULL){
		while (currNode->parent != NULL){
			prevNode = currNode;
			currNode = currNode->parent;
		}
		bestCol = prevNode->moveCol;

		// Calculate the NN output for the current state -- error checking on comp next move
		ProcessNNInput(prevNode->nodeBoard);

		currentMoveGuess = prevNode->moveCol_guess;
		ClearOpenAndClosedLists();
		return bestCol;
	}
	else{
		ClearOpenAndClosedLists();
		currentMoveGuess = -1;
		return -1;
	}
}



void computerPlay(SlotType& player, int otherPlayerAction){
	// Calculate the error associated with the neural net based on the main player's last move
	double nnTotalError = MeanSquaredError(otherPlayerAction);
	TrainNeuralNet(otherPlayerAction);
	
	
	int bestCol = PerformSearch(player);
	int bestRow = GetNextRow(bestCol, board);
	

	board[bestRow][bestCol] = player;
	ProcessNNInput(board);
	
}


int main(){
	int in;
	bool gameOver = false;

	SlotType player;
	int costToGoal = 0;
	
	bool keepPlaying = true;

	ClearBoard();
	InitNeuralNetwork();
	ProcessNNInput(board);
	
	int correctGuessCount = 0;
	int wrongGuessCount = 0;

	char choice = 'y';
	
	player = RED;
	int emptyRow = 0;

	//srand(time(NULL));
	srand(0);

	//board[5][5] = RED;
	//board[4][5] = BLACK;
	PrintBoard(player, gameOver);
	

	while (keepPlaying){
		while (!gameOver && cin >> in && in != -1){
			system("cls");
			if (in >= 0 && in <= 6){
				// Count correct guess from computer
				if (currentMoveGuess == in)
					correctGuessCount++;
				else if (currentMoveGuess != -1)
					wrongGuessCount++;

				emptyRow = GetNextRow(in, board);
				if (emptyRow > -1){
					board[emptyRow][in] = player;
					if (CheckWin(player)){
						gameOver = true;
						PrintBoard(player, gameOver);
						cout << "player: " << player << " wins" << endl;
						continue;
					}
					if (player == RED)
						player = BLACK;
					else
						player = RED;
					
					// Computer makes it's move 
					computerPlay(player, in);
					

					if (CheckWin(player)){
						gameOver = true;
						PrintBoard(player, gameOver);
						cout << "player: " << player << " wins" << endl;
						continue;
					}

					if (player == RED)
						player = BLACK;
					else
						player = RED;

				}
				else{
					cout << "Full slot, try again!" << endl;
				}
			}
			else{
				cout << "Invalid slot, try again!" << endl;
			}




			PrintBoard(player, gameOver);

		}
		cout << endl << "Keep Playing?: (y or n) -- ";
		cin >> choice;
		if (choice == 'y'){
			ClearBoard();
			gameOver = false;
			player = RED;
			PrintBoard(player, gameOver);
		}
		else{
			keepPlaying = false;
		}
	}
	
	return 0;
}