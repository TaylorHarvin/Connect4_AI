
function ComputerPlay(player, otherPlayerAction){
	// Calculate the error associated with the neural net based on the main player's last move
	//var nnTotalError = MeanSquaredError(otherPlayerAction);
	TrainNeuralNet(otherPlayerAction);
	//ProcessNNInput(board);
	
	var bestCol = PerformSearch(player);
	var bestRow = GetPlayableRow(bestCol, board);
	console.log(bestRow);
	console.log(bestCol);
	board[bestRow][bestCol] = player;
	$("#slot_"+bestRow+"_"+bestCol).css("background-color","black");
	CheckWin();
}