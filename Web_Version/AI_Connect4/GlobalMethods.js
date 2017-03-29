function GetPlayableRow(colSelected){
	var rowSelected = -1;
	var i;
	
	for(i = 0; i < 6 && board[i][colSelected] == SlotType.EMPTY; i++){}
	
	if(i > 0 && i <= 6){
		rowSelected = i-1;
	}
	return rowSelected;
}


function PerformMove(playerType, colSelected){
	var rowSelected = GetPlayableRow(colSelected);
	
	if(rowSelected >= 0 && rowSelected < 6){
		board[rowSelected][colSelected] = playerType;
		return rowSelected;
	}
	else
		return -1;
}




function CheckWin(){
	var player = SlotType.BLACK;
	winner = SlotType.EMPTY;
	var currCost = 0;
	var otherCount = 0;
	for (var i = 0; !winner && i < 69; i++){
		currCost = 0;
		otherCount = 0;
		for (var j = 0; j < 4; j++){
			if (board[P_CHECK[i][j][0]][P_CHECK[i][j][1]] != player){
				if (board[P_CHECK[i][j][0]][P_CHECK[i][j][1]] == SlotType.EMPTY)
					currCost++;
				else{
					//currCost += 2;
					otherCount++;
				}
			}
			else{ // This is the computer player -- decrease cost
				//currCost--;
			}
		}
		// Computer wins here
		if (currCost == 0 && otherCount == 0){
			winner = player;
		}
		else if (otherCount == 4){ // User wins
			if (player == SlotType.RED)
				winner = SlotType.BLACK;
			else
				winner = SlotType.RED;
		}
		if(winner != SlotType.EMPTY)
			gameOver = true;
		
		if(winner == SlotType.BLACK)
			alert("You Lose! Press the reset button to try again.");
		else if(winner == SlotType.RED)
			alert("You Win! Press the reset button to play again.");
	}
}