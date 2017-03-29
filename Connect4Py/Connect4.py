from Connect4Tools.BoardNode import BoardNode
from Connect4Tools.BoardTools import BoardTools
from Connect4Tools.States.SlotState import SlotState
from Connect4Tools.GameAI import GameBoardAI

node = BoardNode(0,6,7)
bt = BoardTools()
boardAI = GameBoardAI(5000)
userMove = 0

'''print(bt.GetNextEmpyRow(node.boardState,0))





bt.PlayMove(node.boardState,0,SlotState.USER)
#bt.ExpandNode(node)
#bt.ExpandNode(node2)
boardAI.PlayAIMove(node)
#print(bt.priorityHeap)
#print(bt.GetNormalFlatBoard(node.boardState))

print(node)

print(boardAI.GuessPlayerMove_NN(node.boardState))

bt.PlayMove(node.boardState,0,SlotState.USER)
boardAI.PlayAIMove(node)
print(node)'''

keepPlaying = True
status = []
finalStat = False

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
    

while(keepPlaying):
    print(node)
    userMove = input("Enter your move (0-6): ")
    boardAI.Learn(node.boardState,userMove)
    bt.PlayMove(node.boardState,int(userMove),SlotState.USER)
    keepPlaying = Continue()
    if keepPlaying:
        boardAI.PlayAIMove(node)
        keepPlaying = Continue()
        



    
