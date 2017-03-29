'''
	Developer: Taylor Harvin
	Date: 3/29/2017
	Purpose: BoardNode provides a way to save the state of a current board configuration
             along with the various state properties such as player moves, cost, and parent node id.
             This is intended for use with the A* search for the GameBoardAI and as the primary/base board.
'''
from .States.SlotState import SlotState

class BoardNode:
    parentId = -1               # ID of the node that this node was generated from
                                # Links to the visited listing search when goal node is found
    boardState = []             # the 6*7 board to store the states of each slot
    hCost = 0                   # heuristic cost of the current board state
    stepCost = 0                # step cost during A* (1 added per AI move)
    totalCost = 0               # combined stepCost and hCost
    id = 0                      # the integer ID of the node generated (root is 0)
    winner = SlotState.EMPTY    # the current winner if any of the given state
    isTie = False               # tie flag if the state is a tie
    aiMove = 0                  # AI player's move to make this state
    userMoveGuess = 0           # AI player's guess of user move after AI move


    '''
        Constructor of board node
        Params:
            newId => needed, must be a valid integer
            newNumRows => needed only if otherBoardState not given
                          this is the number of rows to make in a new board
            newNumCols => needed only if otherBoardState not given
                          this is the number of columns to make in a new board
            otherBoardState => used essentially as a copy constructor of another board state
                               Must be a valid board config
        Result:
            Board node setup with all configs (id/board state)
    '''
    def __init__(self, newId, newNumRows=None, newNumCols=None, otherBoardState = None):
        self.id = newId

        # If no board state given, create a new board
        # otherwise, copy the other board config
        if(otherBoardState == None):
            self.boardState = [[SlotState.EMPTY for x in range(newNumCols)] for y in range(newNumRows)]
        else:
            self.boardState = [[SlotState.EMPTY for x in range(len(otherBoardState[0]))] for y in range(len(otherBoardState))]
            for row in range(0,len(otherBoardState)):
                for col in range(len(otherBoardState[row])):
                    self.boardState[row][col] = otherBoardState[row][col]

    '''
        String generator of the node to show current board state
        ex. print(currNode)
        Params:
            None
        Result:
            Board node string is returned in the standard game layout
    '''
    def __str__(self):
        currRow = 0                     # row counter for vertical header print
        strVers = "  0 1 2 3 4 5 6\n"   # the entire string of the board

        for boardRow in self.boardState:
            strVers += str(currRow) + " "
            for boardCol in boardRow:
                if(boardCol == SlotState.AI):
                    strVers += "# "
                elif(boardCol == SlotState.USER):
                    strVers += "* "
                else:
                    strVers += "  "
            strVers += "\n"
            currRow += 1
        return strVers


    '''
        Generates a unique identifier associated with the board state for
        faster lookups in the visited dictionary.

        Params:
            None
        Result:
            Returns a string of 0s,1s,2s based on the state of the board
    '''
    def GetFlatString(self):
        strVers = ""        # the container of the generated key
        for boardRow in self.boardState:
            for boardCol in boardRow:
                if(boardCol == SlotState.AI):
                    strVers += "2"
                elif(boardCol == SlotState.USER):
                    strVers += "1"
                else:
                    strVers += "0"
        return strVers
