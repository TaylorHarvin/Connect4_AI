from .States.SlotState import SlotState
class BoardNode:
    boardState = []
    
    def __init__(self, newNumRows, newNumCols):
        self.boardState = [[SlotState.EMPTY for x in range(newNumRows)] for y in range(newNumCols)]
        print(self.boardState[0][0] is SlotState.EMPTY)
        


