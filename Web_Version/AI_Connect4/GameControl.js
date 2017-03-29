



function PerformMainUserMove(SlotSelected){
	var colSelected = SlotSelected.split("_")[2];
	var rowSelected = PerformMove(SlotType.RED, colSelected);
	if(rowSelected >= 0 && rowSelected <  6){
		$("#slot_"+rowSelected+"_"+colSelected).css("background-color","red");
		CheckWin();
		if(!gameOver)
			ComputerPlay(SlotType.BLACK,colSelected);
	}
	else{
		alert("Invalid Move! -- Please try again.");
	}
	console.log(board);
	
}



function ResetGame(){
	gameOver = false;
	currentMoveGuess = -1;
	board = [[SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY]
			];
			
			for(var i = 0; i <NUM_BOARD_ROWS; i++ ){
				for(var j = 0; j <NUM_BOARD_COLS; j++ ){
					$("#slot_"+i+"_"+j).css("background-color","white");
				}
			}
}