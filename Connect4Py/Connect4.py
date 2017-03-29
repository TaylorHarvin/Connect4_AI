'''
	Developer: Taylor Harvin
	Date: 3/29/2017
	Purpose: Utilizes Connect4 classes: BoardNode, BoardTools, SlotState, and GameAI
			 to play Connect4 with a user.
'''

from Connect4Tools.BoardNode import BoardNode
from Connect4Tools.BoardTools import BoardTools
from Connect4Tools.States.SlotState import SlotState
from Connect4Tools.GameAI import GameBoardAI

node = BoardNode(0,6,7)			# Primary game board
bt = BoardTools()			# Primary board tools
boardAI = GameBoardAI(5000)		# Primary game AI
userMove = 0				# Current move by user
keepPlaying = True			# Game iteration flag
status = []				# Game status flag (for who won if any winners)


# Checks for the current game status
# NOTE: 
def GameOver():
    global status
    global keepPlaying
    global node
    global bt

    status = bt.GetWinner(node.boardState)
    if status[0] != SlotState.EMPTY:
        print("GAME OVER -- Winner: ",status[0])
        return True
    elif status[1] == True:
        print("GAME OVER -- Tie")
        return False

def Continue():
    global node
	
	
    if GameOver():
        print(node)
        node = BoardNode(0,6,7)
        res = input("Play Again? (y/n): ")
        if res == 'y':
            return True
        return False
    return True
    
if __name__ == "__main__":
	while(keepPlaying):
		print(node)
		userMove = input("Enter your move (0-6): ")
		boardAI.Learn(node.boardState,userMove)
		bt.PlayMove(node.boardState,int(userMove),SlotState.USER)
		keepPlaying = Continue()
		if keepPlaying:
			boardAI.PlayAIMove(node)
			keepPlaying = Continue()
        



    
