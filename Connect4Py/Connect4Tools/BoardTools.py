from .WinningStates import WINNING_STATES
from .States.SlotState import SlotState
from .BoardNode import BoardNode
import math
import random
from heapq import *
#from queue import PriorityQueue
#from .heapdict import *

class BoardTools:


    def __init__(self):
        return

    def GetNextEmpyRow(self,boardState,col):
        for row in reversed(range(len(boardState))):
            if boardState[row][col] is SlotState.EMPTY:
                return row
        return -1

    def PlayMove(self,boardState,col,slotState):
        nextEmptyRow = self.GetNextEmpyRow(boardState,col)

        # if the row is valid, play the move
        if nextEmptyRow >= 0 and nextEmptyRow < len(boardState):
            boardState[nextEmptyRow][col] = slotState
            return nextEmptyRow
        else:
            return -1
    def GetWinner(self,boardState):
        res = self.GetHCost(boardState)
        for boardRow in boardState:
            for slot in boardRow:
                if slot == SlotState.EMPTY:
                    return (res[1],False)
        return (res[1],True)

    def GetHCost(self, boardState):
        slotCounts = [0,0,0]
        hCost = 0
        currCost = 0
        winner = SlotState.EMPTY

        for winSec in WINNING_STATES:
            for slot in winSec:
                currRow = slot[0]
                currCol = slot[1]
                currSlotState = boardState[currRow][currCol]

                # Store the count of slot types for the current 4-in-a-row section
                if(currSlotState == SlotState.AI):
                    slotCounts[2] += 1
                elif(currSlotState == SlotState.USER):
                    slotCounts[1] += 1
                else:
                    slotCounts[0] += 1

            # fully empty section --> ignore
            if slotCounts[0] == 4:
                currCost = 0
            elif slotCounts[1] or (slotCounts[2] > 0 and  slotCounts[1] > 0):
                currCost = math.pow(2,slotCounts[1]) + slotCounts[0]
            else:
                currCost = slotCounts[0]

            if slotCounts[1] == 4:
                winner = SlotState.USER
            elif slotCounts[2] == 4:
                winner = SlotState.AI
            #if currCost > 0:
                #print(winSec, currCost,slotCounts)
            hCost += currCost
            slotCounts = [0,0,0]
            currCost = 0
        return (hCost, winner)

    def GetNormalFlatBoard(self, boardState):
        flatNormalBoard = [0.0]*len(boardState)*len(boardState[0])
        for row in range(len(boardState)):
            for col in range(len(boardState[row])):
                if(boardState[row][col] == SlotState.AI):
                    flatNormalBoard[row*len(boardState[row]) + col] = 1.0
                elif(boardState[row][col] == SlotState.USER):
                    flatNormalBoard[row*len(boardState[row]) + col] = 0.5
                else:
                    flatNormalBoard[row*len(boardState[row]) + col] = 0
        return flatNormalBoard;
