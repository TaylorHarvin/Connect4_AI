var NUM_BOARD_COLS = 7;
var NUM_BOARD_ROWS = 6;
var EXPAND_CUTOFF = 500;
var gameOver = false;
var currentMoveGuess = -1;

var board = [[SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY],
			 [SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY,SlotType.EMPTY]
			];

			
var nextNodeId = 0;
var openList = [];
var closedList = [];
var globalNodeList = [];
var winner;		// Just for cost check


var PathNode = function(){
	this.ID;
	this.hCost;
	this.stepCost;
	this.fullCost;
	this.moveCol;
	this.winningNode;
	this.parentID;
	this.nodeBoard = [[0,0,0,0,0,0,0],
								[0,0,0,0,0,0,0],
								[0,0,0,0,0,0,0],
								[0,0,0,0,0,0,0],
								[0,0,0,0,0,0,0],
								[0,0,0,0,0,0,0]
							   ];
	this.moveCol_guess;
	this.Init = function(newID,newstepCost,newmoveCol,newwinningNode,newparent){
		this.ID = newID;
		this.stepCost = newstepCost;
		this.moveCol = newmoveCol;
		this.winningNode = newwinningNode;
		this.parentID = newparent;
	}

	this.copyBoard = function(currBoard){
		for (var i = 0; i < 6; i++){
			for (var j = 0; j < 7; j++){
				this.nodeBoard[i][j] = currBoard[i][j];
			}
		}
	}
	
}






























var P_CHECK = [ [ [ 0, 0 ], [ 0, 1 ], [ 0, 2 ], [ 0, 3 ] ],
							[ [ 0, 1 ], [ 0, 2 ], [ 0, 3 ], [ 0, 4 ] ],
							[ [ 0, 2 ], [ 0, 3 ], [ 0, 4 ], [ 0, 5 ] ],
							[ [ 0, 3 ], [ 0, 4 ], [ 0, 5 ], [ 0, 6 ] ],
							[ [ 1, 0 ], [ 1, 1 ], [ 1, 2 ], [ 1, 3 ] ],
							[ [ 1, 1 ], [ 1, 2 ], [ 1, 3 ], [ 1, 4 ] ],
							[ [ 1, 2 ], [ 1, 3 ], [ 1, 4 ], [ 1, 5 ] ],
							[ [ 1, 3 ], [ 1, 4 ], [ 1, 5 ], [ 1, 6 ] ],
							[ [ 2, 0 ], [ 2, 1 ], [ 2, 2 ], [ 2, 3 ] ],
							[ [ 2, 1 ], [ 2, 2 ], [ 2, 3 ], [ 2, 4 ] ],
							[ [ 2, 2 ], [ 2, 3 ], [ 2, 4 ], [ 2, 5 ] ],
							[ [ 2, 3 ], [ 2, 4 ], [ 2, 5 ], [ 2, 6 ] ],
							[ [ 3, 0 ], [ 3, 1 ], [ 3, 2 ], [ 3, 3 ] ],
							[ [ 3, 1 ], [ 3, 2 ], [ 3, 3 ], [ 3, 4 ] ],
							[ [ 3, 2 ], [ 3, 3 ], [ 3, 4 ], [ 3, 5 ] ],
							[ [ 3, 3 ], [ 3, 4 ], [ 3, 5 ], [ 3, 6 ] ],
							[ [ 4, 0 ], [ 4, 1 ], [ 4, 2 ], [ 4, 3 ] ],
							[ [ 4, 1 ], [ 4, 2 ], [ 4, 3 ], [ 4, 4 ] ],
							[ [ 4, 2 ], [ 4, 3 ], [ 4, 4 ], [ 4, 5 ] ],
							[ [ 4, 3 ], [ 4, 4 ], [ 4, 5 ], [ 4, 6 ] ],
							[ [ 5, 0 ], [ 5, 1 ], [ 5, 2 ], [ 5, 3 ] ],
							[ [ 5, 1 ], [ 5, 2 ], [ 5, 3 ], [ 5, 4 ] ],
							[ [ 5, 2 ], [ 5, 3 ], [ 5, 4 ], [ 5, 5 ] ],
							[ [ 5, 3 ], [ 5, 4 ], [ 5, 5 ], [ 5, 6 ] ],
							[ [ 0, 0 ], [ 1, 0 ], [ 2, 0 ], [ 3, 0 ] ],
							[ [ 1, 0 ], [ 2, 0 ], [ 3, 0 ], [ 4, 0 ] ],
							[ [ 2, 0 ], [ 3, 0 ], [ 4, 0 ], [ 5, 0 ] ],
							[ [ 0, 1 ], [ 1, 1 ], [ 2, 1 ], [ 3, 1 ] ],
							[ [ 1, 1 ], [ 2, 1 ], [ 3, 1 ], [ 4, 1 ] ],
							[ [ 2, 1 ], [ 3, 1 ], [ 4, 1 ], [ 5, 1 ] ],
							[ [ 0, 2 ], [ 1, 2 ], [ 2, 2 ], [ 3, 2 ] ],
							[ [ 1, 2 ], [ 2, 2 ], [ 3, 2 ], [ 4, 2 ] ],
							[ [ 2, 2 ], [ 3, 2 ], [ 4, 2 ], [ 5, 2 ] ],
							[ [ 0, 3 ], [ 1, 3 ], [ 2, 3 ], [ 3, 3 ] ],
							[ [ 1, 3 ], [ 2, 3 ], [ 3, 3 ], [ 4, 3 ] ],
							[ [ 2, 3 ], [ 3, 3 ], [ 4, 3 ], [ 5, 3 ] ],
							[ [ 0, 4 ], [ 1, 4 ], [ 2, 4 ], [ 3, 4 ] ],
							[ [ 1, 4 ], [ 2, 4 ], [ 3, 4 ], [ 4, 4 ] ],
							[ [ 2, 4 ], [ 3, 4 ], [ 4, 4 ], [ 5, 4 ] ],
							[ [ 0, 5 ], [ 1, 5 ], [ 2, 5 ], [ 3, 5 ] ],
							[ [ 1, 5 ], [ 2, 5 ], [ 3, 5 ], [ 4, 5 ] ],
							[ [ 2, 5 ], [ 3, 5 ], [ 4, 5 ], [ 5, 5 ] ],
							[ [ 0, 6 ], [ 1, 6 ], [ 2, 6 ], [ 3, 6 ] ],
							[ [ 1, 6 ], [ 2, 6 ], [ 3, 6 ], [ 4, 6 ] ],
							[ [ 2, 6 ], [ 3, 6 ], [ 4, 6 ], [ 5, 6 ] ],
							[ [ 0, 0 ], [ 1, 1 ], [ 2, 2 ], [ 3, 3 ] ],
							[ [ 0, 1 ], [ 1, 2 ], [ 2, 3 ], [ 3, 4 ] ],
							[ [ 0, 2 ], [ 1, 3 ], [ 2, 4 ], [ 3, 5 ] ],
							[ [ 0, 3 ], [ 1, 4 ], [ 2, 5 ], [ 3, 6 ] ],
							[ [ 1, 0 ], [ 2, 1 ], [ 3, 2 ], [ 4, 3 ] ],
							[ [ 1, 1 ], [ 2, 2 ], [ 3, 3 ], [ 4, 4 ] ],
							[ [ 1, 2 ], [ 2, 3 ], [ 3, 4 ], [ 4, 5 ] ],
							[ [ 1, 3 ], [ 2, 4 ], [ 3, 5 ], [ 4, 6 ] ],
							[ [ 2, 0 ], [ 3, 1 ], [ 4, 2 ], [ 5, 3 ] ],
							[ [ 2, 1 ], [ 3, 2 ], [ 4, 3 ], [ 5, 4 ] ],
							[ [ 2, 2 ], [ 3, 3 ], [ 4, 4 ], [ 5, 5 ] ],
							[ [ 2, 3 ], [ 3, 4 ], [ 4, 5 ], [ 5, 6 ] ],
							[ [ 0, 6 ], [ 1, 5 ], [ 2, 4 ], [ 3, 3 ] ],
							[ [ 0, 5 ], [ 1, 4 ], [ 2, 3 ], [ 3, 2 ] ],
							[ [ 0, 4 ], [ 1, 3 ], [ 2, 2 ], [ 3, 1 ] ],
							[ [ 0, 3 ], [ 1, 2 ], [ 2, 1 ], [ 3, 0 ] ],
							[ [ 1, 6 ], [ 2, 5 ], [ 3, 4 ], [ 4, 3 ] ],
							[ [ 1, 5 ], [ 2, 4 ], [ 3, 3 ], [ 4, 2 ] ],
							[ [ 1, 4 ], [ 2, 3 ], [ 3, 2 ], [ 4, 1 ] ],
							[ [ 1, 3 ], [ 2, 2 ], [ 3, 1 ], [ 4, 0 ] ],
							[ [ 2, 6 ], [ 3, 5 ], [ 4, 4 ], [ 5, 3 ] ],
							[ [ 2, 5 ], [ 3, 4 ], [ 4, 3 ], [ 5, 2 ] ],
							[ [ 2, 4 ], [ 3, 3 ], [ 4, 2 ], [ 5, 1 ] ],
							[ [ 2, 3 ], [ 3, 2 ], [ 4, 1 ], [ 5, 0 ] ] ];