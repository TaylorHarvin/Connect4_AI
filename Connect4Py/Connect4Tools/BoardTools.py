from .WinningStates import WinningStates
from .States.SlotState import SlotState

class BoardTools:

    def __init__(self):
        print("init")

    def GetNextEmpyRow(self,boardState,col):
        for row,boardRow in boardState:
            if boardState[row][col] is SlotState.EMPTY:
                return row
        return -1


bt = BoardTools()
