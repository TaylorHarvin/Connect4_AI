from .WinningStates import WINNING_STATES
from .States.SlotState import SlotState
from .BoardNode import BoardNode
from .BoardTools import BoardTools
from .NeuralNetwork import NeuralNetwork
import math
import random
import copy
from heapq import *
#from queue import PriorityQueue
#from .heapdict import *

class GameBoardAI:
    openList = {}
    visited = dict()
    priorityHeap = []
    nextNodeId = 0
    MAX_EXPAND = 0
    boardTools = -1
    mainNN = NeuralNetwork(42,0,7,[],[])
    lastPlayerMoveGuess = -1
    tmp = ""

    def __init__(self,maxExpand):
        self.openList = {}
        self.visited = dict()
        self.priorityHeap = []
        self.nextNodeId = 0
        self.MAX_EXPAND = maxExpand
        self.boardTools = BoardTools()
        self.mainNN.refresh()
        return

    def GuessPlayerMove_Random(self, boardState):
        colTryFlags = [False,False,False,False,False,False,False]
        guessRow = -1
        guessCol = 0

        while guessRow < 0 and colTryFlags.count(False) > 0:
            guessCol = random.randint(0,6)
            colTryFlags[guessCol] = True
            guessRow = self.boardTools.GetNextEmpyRow(boardState,guessCol)
        if guessRow > 0:
            return guessCol
        else:
            return -1

    def GuessPlayerMove_NN(self, boardState):
        guessCol = -1
        highestVal = 0
        self.mainNN.processInput(self.boardTools.GetNormalFlatBoard(boardState))
        for nnNode in range(len(self.mainNN.outNodes)):
            if self.mainNN.outNodes[nnNode] > highestVal:
                if self.boardTools.GetNextEmpyRow(boardState,nnNode) >= 0:
                    highestVal = self.mainNN.outNodes[nnNode]
                    guessCol = nnNode
        return guessCol


    def ExpandNode(self, parentNode):
        #heappush(self.priorityHeap,(parentNode.totalCost,parentNode.id))
        #self.openList[parentNode.id] = parentNode
        currGuessCol = 0
        newNodeList = [None,None,None,None,None,None,None]
        hCostRes = []
        aiRowRes = -1


        for col in range(7):
            newNodeList[col] = BoardNode(self.nextNodeId,0,0,parentNode.boardState)
            self.nextNodeId += 1
            aiRowRes = self.boardTools.PlayMove(newNodeList[col].boardState,col,SlotState.AI)
            #currGuessCol = self.GuessPlayerMove_Random(newNodeList[col].boardState)
            currGuessCol = self.GuessPlayerMove_NN(newNodeList[col].boardState)


            if currGuessCol >= 0 and aiRowRes > 0:
                self.boardTools.PlayMove(newNodeList[col].boardState,currGuessCol,SlotState.USER)
                if(newNodeList[col].GetFlatString() not in self.visited.keys()):
                    newNodeList[col].parentId = parentNode.id
                    newNodeList[col].userMoveGuess = currGuessCol
                    hCostRes = self.boardTools.GetHCost(newNodeList[col].boardState)
                    newNodeList[col].hCost = hCostRes[0]

                    newNodeList[col].winner = hCostRes[1]
                    newNodeList[col].aiMove = col

                    newNodeList[col].stepCost = parentNode.stepCost + 1
                    newNodeList[col].totalCost = newNodeList[col].hCost + newNodeList[col].stepCost

                    # Node is either AI win or none, so push it onto the open list
                    if(newNodeList[col].winner != SlotState.USER):
                        self.openList[newNodeList[col].id] = newNodeList[col]
                        heappush(self.priorityHeap,(newNodeList[col].totalCost,newNodeList[col].id))
    def Learn(self, boardState, userMove):
        expectedOut = [0.0]*len(boardState[0])
        if self.lastPlayerMoveGuess > -1:
            for i in range(len(boardState[0])):
                if i == self.lastPlayerMoveGuess:
                    expectedOut[i] = 1.0
                    break
        self.mainNN.train(self.boardTools.GetNormalFlatBoard(boardState),expectedOut,0.8,0)

    def PlayAIMove(self, rootNode):
        self.openList = {}
        self.visited = dict()
        self.priorityHeap = []
        self.nextNodeId = 1
        aiMove = 0

        currNode = rootNode
        self.currNodeId = 0
        expandCount = 0
        nodeId = 0

        self.visited[rootNode.GetFlatString()] = rootNode
        while currNode.winner != SlotState.AI and expandCount < self.MAX_EXPAND:
            self.ExpandNode(currNode)
            #print(self.priorityHeap)
            nodeId = heappop(self.priorityHeap)[1]
            currNode = copy.deepcopy(self.openList[nodeId])
            if currNode.GetFlatString() not in self.visited.keys():
                self.visited[currNode.GetFlatString()] = copy.deepcopy(currNode)
                del self.openList[currNode.id]
            #else:
                #print("ERROR", currNode.id)



            expandCount += 1
        print("Expand:",expandCount)
        expandCount = 0

        while currNode.id != 0 and expandCount < self.MAX_EXPAND:
            expandCount += 1
            #print(currNode.parentId)
            for key in self.visited.keys():
                if self.visited[key].id == currNode.parentId:
                    currNode = self.visited[key]
                    break
                aiMove = currNode.aiMove
                self.lastPlayerMoveGuess = currNode.userMoveGuess
        #print(currNode)

        self.boardTools.PlayMove(rootNode.boardState,aiMove,SlotState.AI)
        return aiMove
