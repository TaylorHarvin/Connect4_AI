function GetCost(col, row, player, currBoard){
	winner = SlotType.EMPTY;
	currCost = 0;
	costToGoal = 0;
	otherCount = 0;
	playerCount = 0;
	chancePenalty = 0;
	emptyCount = 0;
	//currBoard[row][col] = player;

	for (var i = 0; /*!winner &&*/ i < 69; i++){
		currCost = 0;
		otherCount = 0;
		playerCount = 0;
		emptyCount = 0;

		for (var j = 0; j < 4; j++){
			if (currBoard[P_CHECK[i][j][0]][P_CHECK[i][j][1]] != player){
				if (currBoard[P_CHECK[i][j][0]][P_CHECK[i][j][1]] == SlotType.EMPTY)
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
			if (player == SlotType.RED)
				winner = SlotType.BLACK;
			else
				winner = SlotType.RED;
		}
		if (emptyCount == 4)
			currCost = 0;
		else if (playerCount == 0 || (otherCount > 0 && playerCount > 0))
			currCost =Math.pow(2, otherCount) + emptyCount;
		else // player has spots, but computer doesn't 
			currCost = emptyCount;

		costToGoal += currCost;
	}

	//currBoard[row][col] = EMPTY;
	if (costToGoal < 0)
		costToGoal = 0;
	return costToGoal;
}



function GuessPlayerAction_Random(currBoard, otherPlayer){
	var slotGuess = Math.floor((Math.random() * 7));
	var guessList = [];
	var selectedRow = GetPlayableRow(slotGuess, currBoard);
	if (selectedRow >= 0 && selectedRow < 6)
		currBoard[selectedRow][slotGuess] = otherPlayer;
	else{
		guessList.push(slotGuess);
		do{
			do{
				slotGuess = rand() % 7;
			} while (guessList.indexOf(slotGuess) < 0);
			selectedRow = GetPlayableRow(slotGuess, currBoard);
		} while (selectedRow < 0 || selectedRow >= 6);
		currBoard[selectedRow][slotGuess] = otherPlayer;
	}
	return slotGuess;
}



function GuessPlayerAction_NN(currBoard, otherPlayer){
	ProcessNNInput(currBoard);
	var slotGuess = -1;
	var tieIndex = 0;
	var selectedRow = -1;
	// Generate the output nodes based on the given board
	ProcessNNInput(currBoard);
	var tieList = [];
	var highestOut = 0;

	// Go through all output nodes and decide the guessed player action
	for (var outIndex = 0; outIndex < NUM_OUTPUT; outIndex++){
		if (nnOutputLayer[outIndex] == highestOut){
			tieList.push(outIndex);
		}
		else if (nnOutputLayer[outIndex] > highestOut){
			highestOut = nnOutputLayer[outIndex];
			tieList = [];
			tieList.push(outIndex);
		}
		//alert(nnOutputLayer[outIndex]);
	}

	tieIndex = Math.floor(Math.random()* tieList.length);
	
	slotGuess = tieList[tieIndex];
	selectedRow = GetPlayableRow(slotGuess, currBoard);
	
	currBoard[selectedRow][slotGuess] = otherPlayer;
	tieList = [];
	return slotGuess;
}



function GuessPlayerAction(currBoard, otherPlayer){
	var playerGuess = -1;
	//playerGuess = GuessPlayerAction_Random(currBoard, otherPlayer);
	playerGuess = GuessPlayerAction_NN(currBoard, otherPlayer);

	return playerGuess;
}


function boardPlayable(currBoard){
	var numAvailiable = 0;
	for (var i = 0; i < 6; i++){
		if (currBoard[0][i] == SlotType.EMPTY)
			numAvailiable++;
	}
	if (numAvailiable > 0)
		return true;
	else
		return false;
}


function AddToOpenAndGlobalList(currNode){
	globalNodeList[currNode.ID] = currNode;
	var openIndex = 0;
	for(openIndex = 0; openIndex < openList.length; openIndex++){
		if(currNode.fullCost <= openList[openIndex].fullCost){
			openList.splice(openIndex,0,currNode);
			break;
		}
	}
	if(openList.length == 0 || openIndex == openList.length){
		openList.push(currNode);
	}
	//alert(openList.length);
	console.log("OPEN AFTER:");
	console.log(openList);
}



function NodeVisited(currNode){
	var closedIndex = 0;
	var matchCount = 0;

	for (closedIndex = 0; closedIndex  < closedList.length; closedIndex++, matchCount = 0){
		for (var i = 0; i < 6; i++){
			for (var j = 0; j < 7; j++){
				if (currNode.nodeBoard[i][j] == closedList[closedIndex].nodeBoard[i][j])
					matchCount++;
			}
		}
		if (matchCount >= 42){
			return true;
		}
	}
}



function Expand(parentNode, player){
	/*if (parentNode == NULL){
		cerr << "ERROR" << endl;
	}*/

	var emptyRow = 0;
	var bestCol = 0;
	var bestRow = 0;
	var highestVal = 0;
	var goalCost = [0,SlotType.EMPTY];
	var currNode;
	var otherPlayer;
	var slotGuess = -1;

	if (player == SlotType.BLACK){
		otherPlayer = SlotType.RED;
	}
	else
		otherPlayer = SlotType.BLACK;

	var numNodesGenerated = 0;

	closedList.push(parentNode);

	for (var i = 0; i < 7; i++){
		emptyRow = GetPlayableRow(i, parentNode.nodeBoard);
		
		// If the row is not full -- create the new board
		if (emptyRow >= 0 && emptyRow < 6){
			currNode = new PathNode();
			currNode.Init(nextNodeId, parentNode.stepCost + 1, i, false, parentNode.ID);
			nextNodeId++;
			currNode.copyBoard(parentNode.nodeBoard);
			currNode.nodeBoard[emptyRow][i] = player;
			slotGuess = GuessPlayerAction(currNode.nodeBoard, otherPlayer);
			// For some reason, the above function clears parent pointer this fixes that
			//currNode.parentID = parentNode.ID;

			if (!NodeVisited(currNode)){
				console.log("NODE NOT VISITED");
				goalCost[0] = GetCost(i, emptyRow, player, currNode.nodeBoard);
				currNode.hCost = goalCost[0];
				goalCost[1] = winner;
				currNode.fullCost = currNode.hCost + currNode.stepCost;
				if (goalCost[1] == player || goalCost[1] == SlotType.EMPTY){
					currNode.winningNode = goalCost[1];
					currNode.moveCol_guess = slotGuess;
					console.log("CURR NODE:");
					console.log(currNode);
					AddToOpenAndGlobalList(currNode);
					numNodesGenerated++;
					console.log(i + " NEW OPEN:");
					console.log(openList);
				}
				else{
					currNode = [];
					nextNodeId--;
				}
			}
			else{ // node already visited
				currNode = [];
				nextNodeId--;
			}
		}
		else{ // Deadend node with no win -- all slots filled
			//delete currNode;
		}
	}

	if (numNodesGenerated > 0)
		return true;
	else
		return false;
}





function PerformSearch(player){
	var currNode;
	var prevNode;
	var nextMove = [0,0];

	currNode = new PathNode();
	currNode.Init(0, 0, -1, false, -1);
	nextNodeId++;
	currNode.copyBoard(board);
	//openList.push(currNode);
	//const int cutoff = 1;
	var count = 0;

	closedList = Array();
	openList = Array();
	globalNodeList = Array();
	globalNodeList.push(currNode);
	while (!currNode.winningNode && count < EXPAND_CUTOFF){
		Expand(currNode, player);
		console.log("OPEN:");
		console.log(openList);
		if (openList.length > 0){
			currNode = openList.shift();
			count++;
		}
		else{
			break;
		}
	}
	//alert(openList.length);
	var bestCol = -1;
	if (currNode.ID >= 0){
		while (currNode.parentID > -1){
			prevNode = currNode;
			currNode = globalNodeList[currNode.parentID];
		}
		if(prevNode.ID >= 0 && prevNode.ID < globalNodeList.length){
			bestCol = globalNodeList[prevNode.ID].moveCol;
			currentMoveGuess = globalNodeList[prevNode.ID].moveCol_guess;
		}
		else{
			alert("ERROR: "+ prevNode.ID);
			bestCol = globalNodeList[currNode.ID].moveCol;
			currentMoveGuess = globalNodeList[currNode.ID].moveCol_guess;
		}
		// Calculate the NN output for the current state -- error checking on comp next move
		//ProcessNNInput(prevNode->nodeBoard);

		
		closedList = [];
		openList = [];
		globalNodeList = [];
		nextNodeId = 0;
		return bestCol;
	}
	else{
		//ClearOpenAndClosedLists();
		closedList = [];
		openList = [];
		globalNodeList = [];
		 nextNodeId = 0;
		currentMoveGuess = -1;
		return -1;
	}
}