'''
	Developer: Taylor Harvin
	Date: 3/29/2017
	Purpose: BoardTools provides various methods to help maniplulate board states,
             get costs, check winner,...
             Essentially, this could have been in BoardNode, but it helps reduce memory
             usage and increases overall performance.

'''

from .WinningStates import WINNING_STATES
from .States.SlotState import SlotState
from .BoardNode import BoardNode
import math
import random
from heapq import *
#from queue import PriorityQueue
#from .heapdict import *

class BoardTools:

    '''
        Constructor of BoardTools
        Params:
            None
        Result:
            Initiallizes BoardTools object
    '''
    def __init__(self):
        return


    '''
        Gets the next empty row in the requested column of the board state
        Params:
            boardState => needed, state of the board node
            col => needed, requested column to check
        Result:
            On success => returns the next empty row in the board state (from the bottom)
            On fail => returns -1 (column full)
    '''
    def GetNextEmpyRow(self,boardState,col):
        for row in reversed(range(len(boardState))):
            if boardState[row][col] is SlotState.EMPTY:
                return row
        return -1


    '''
        Plays the requested move on the given board state
        Params:
            boardState => needed, state of the board node
            col => needed, requested column to play move
            slotState => the player making the move
        Result:
            On success => the boardState is updated with the player's move
                          and the result row is returned
            On fail => returns -1 (column full)
    '''
    def PlayMove(self,boardState,col,slotState):
        nextEmptyRow = self.GetNextEmpyRow(boardState,col)  # the row of the board state to play the move

        # if the row is valid, play the move
        if nextEmptyRow >= 0 and nextEmptyRow < len(boardState):
            boardState[nextEmptyRow][col] = slotState
            return nextEmptyRow
        else:
            return -1


    '''
        Check if there is a winner
        Params:
            boardState => needed, state of the board node
        Result:
            returns the winner (SlotState,boolean flag for tie check)
    '''
    def GetWinner(self,boardState):
        res = self.GetHCost(boardState)     # Check for winner

        # Check for tie
        for boardRow in boardState:
            for slot in boardRow:
                if slot == SlotState.EMPTY:
                    return (res[1],False)
        return (res[1],True)


    '''
        Get the heuristic to the goal of the current board state
        and check for winner
        Params:
            boardState => needed, state of the board node
        Result:
            returns (heuristic,SlotState winner)
    '''
    def GetHCost(self, boardState):
        slotCounts = [0,0,0]        # current 4-in-a-row counter
                                    # index 0: SlotState.EMPTY
                                    # index 1: SlotState.USER
                                    # index 2: SlotState.AI
        hCost = 0                   # overall heuristic cost
        currCost = 0                # current 4-in-a-row hCost
        winner = SlotState.EMPTY    # the winner of the board state

        # Go through all possible 4-in-a-row options and generate overall state cost
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
            # User has 0 moves or both AI and player has at least 1 move
            elif slotCounts[1] == 0 or (slotCounts[2] > 0 and  slotCounts[1] > 0):
                currCost = math.pow(2,slotCounts[1]) + slotCounts[0]
            # player only has moves, just add empty count
            else:
                currCost = slotCounts[0]

            # check for winner
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
