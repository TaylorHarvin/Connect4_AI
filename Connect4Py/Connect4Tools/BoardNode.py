from .States.SlotState import SlotState
class BoardNode:
    parentId = -1
    boardState = []
    hCost = 0
    stepCost = 0
    totalCost = 0
    id = 0
    winner = SlotState.EMPTY
    isTie = False
    aiMove = 0
    userMoveGuess = 0


    def __init__(self, newId, newNumRows=None, newNumCols=None, otherBoardState = None):
        self.id = newId

        if(otherBoardState == None):
            self.boardState = [[SlotState.EMPTY for x in range(newNumCols)] for y in range(newNumRows)]
        else:
            self.boardState = [[SlotState.EMPTY for x in range(len(otherBoardState[0]))] for y in range(len(otherBoardState))]
            for row in range(0,len(otherBoardState)):
                for col in range(len(otherBoardState[row])):
                    self.boardState[row][col] = otherBoardState[row][col]

    def __str__(self):
        currRow = 0
        strVers = "  0 1 2 3 4 5 6\n"
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

    def GetFlatString(self):
        strVers = ""
        for boardRow in self.boardState:
            for boardCol in boardRow:
                if(boardCol == SlotState.AI):
                    strVers += "2"
                elif(boardCol == SlotState.USER):
                    strVers += "1"
                else:
                    strVers += "0"
        return strVers
