#!\usr\bin\python3
import random
import math
import time


class NeuralNetwork:
    #inNodes = []
    inToHidWeights =[]
    hidNodes = []
    hidToOutWeights = []
    outNodes = []
    outDeltas = []
    hidDeltas = []
    prevInToHidChange = []
    prevHidToOutChange = []
    inputNodeSize = 0


    inToOutWeights = [] # ONLY WHEN 0 HID NODES
    prevInToOutChange = [] # ONLY WHEN 0 HID NODES

    def __init__(self, inputNodeSize, hiddenNodeSize,outputNodeSize, prevInToOtherWeights, prevHidToOutWeights):
        #self.inNodes =[0.0]*inputNodeSize;
        self.hidNodes =[0.0]*hiddenNodeSize
        self.outNodes =[0.0]*outputNodeSize
        self.outDeltas = [0.0]*outputNodeSize
        self.hidDeltas = [0.0]*hiddenNodeSize
        self.prevInToHidChange = [0.0]*inputNodeSize*hiddenNodeSize
        self.prevHidToOutChange = [0.0]*hiddenNodeSize*outputNodeSize
        self.inputNodeSize = inputNodeSize

        if(hiddenNodeSize <= 0):
            if(len(prevInToOtherWeights) > 0):
               self.inToOutWeights = list(prevInToOtherWeights)
            else:
                self.inToOutWeights = [0.0]*inputNodeSize*outputNodeSize

            self.prevInToOutChange = [0.0]*inputNodeSize*outputNodeSize
        else:
           if(len(prevInToOtherWeights) > 0 and len(prevHidToOutWeights) > 0):
               self.inToHidWeights = list(prevInToOtherWeights)
               self.hidToOutWeights = list(prevHidToOutWeights)

           else:
               self.hidToOutWeights =[0.0]*hiddenNodeSize*outputNodeSize
               self.inToHidWeights =[0.0]*inputNodeSize*hiddenNodeSize

        if(len(prevInToOtherWeights) <= 0 and len(prevHidToOutWeights) <= 0):
            self.refresh()

    def refresh(self):
        random.seed(0)
        for index in range(len(self.inToHidWeights)):
            self.inToHidWeights[index] = random.random()
            #self.inToHidWeights[index] = 0.1
        for index in range(len(self.hidToOutWeights)):
            self.hidToOutWeights[index] = random.random()
            '''if(index == 1):
                self.hidToOutWeights[index] = 0.1
            else:
                self.hidToOutWeights[index] = 0.2'''

    def activate(self,val):
        return 1.0/(1.0+math.pow(math.e,(-1.0)*val))

    def activateDeriv(self,val):
        return self.activate(val)*(1.0 - self.activate(val))

    def normalize(self, val, low, high, targetLow, targetHigh):
        numer = (val-low)*(targetHigh - targetLow)
        denom = (high - low)
        return (numer/denom)
    def deNormalize(self, normVal, low, high):
        return normVal * (high-low) + low


    # Calculate the output of the neural network given the normalized input set
    def processInput(self, newInputNodes):
        #Normal FFNN calculation -- with at least 1 hidden node
        if(len(self.hidNodes) > 0):
            # calculate the values of the hidden nodes
            for hidNodeIndex in range(len(self.hidNodes)):
                self.hidNodes[hidNodeIndex] = 0
                for inNodeIndex in range(len(newInputNodes)):
                    #print((hidNodeIndex*inNodeIndex) + inNodeIndex%len(newInputNodes))
                    self.hidNodes[hidNodeIndex] += newInputNodes[inNodeIndex] * self.inToHidWeights[(hidNodeIndex*len(newInputNodes)) + inNodeIndex]
                self.hidNodes[hidNodeIndex] = self.activate(self.hidNodes[hidNodeIndex]);

            # calculate the value of the
            for outNodeIndex in range(len(self.outNodes)):
                self.outNodes[outNodeIndex] = 0
                for hidNodeIndex in range(len(self.hidNodes)):
                    #print((outNodeIndex*len(self.hidNodes)) + hidNodeIndex)
                    self.outNodes[outNodeIndex] += self.hidNodes[hidNodeIndex] * self.hidToOutWeights[(outNodeIndex*len(self.hidNodes)) + hidNodeIndex]
                self.outNodes[outNodeIndex] = self.activate(self.outNodes[outNodeIndex]);
        else:
            for outNodeIndex in range(len(self.outNodes)):
                self.outNodes[outNodeIndex] = 0
                for inNodeIndex in range(len(newInputNodes)):
                    #print (outNodeIndex*len(newInputNodes)) + inNodeIndex
                    #print (len(self.inToOutWeights))
                    self.outNodes[outNodeIndex] += newInputNodes[inNodeIndex] * self.inToOutWeights[(outNodeIndex*len(newInputNodes)) + inNodeIndex]
                self.outNodes[outNodeIndex] = self.activate(self.outNodes[outNodeIndex]);


    # Applies the new weight changes for the nueral network
    #NOTE: Assumes that train(...) is called when using this
    def ApplyWeightChange(self, learningRate, momentumRate):
        inToHidIndex = 0
        hidToOutIndex = 0

        if(len(self.hidNodes) > 0):
            for hidNodeIndex in range(len(self.hidNodes)):
                for outNodeIndex in range(len(self.outNodes)):
                    hidToInIndex = hidNodeIndex + (outNodeIndex*len(self.hidNodes))
                    self.prevHidToOutChange[hidToOutIndex] = learningRate*self.outDeltas[outNodeIndex] + momentumRate*self.prevHidToOutChange[hidToOutIndex]
                    self.hidToOutWeights[hidToOutIndex] += self.prevHidToOutChange[hidToOutIndex]

            for inNodeIndex in range(self.inputNodeSize):
                for hidNodeIndex in range(len(self.hidNodes)):
                    inToHidIndex = inNodeIndex + (hidNodeIndex*self.inputNodeSize)
                    self.prevInToHidChange[inToHidIndex] = learningRate*self.hidDeltas[hidNodeIndex] + momentumRate*self.prevInToHidChange[inToHidIndex]
                    self.inToHidWeights[inToHidIndex] += self.prevInToHidChange[inToHidIndex]
        else:
            for inNodeIndex in range(self.inputNodeSize):
                for outNodeIndex in range(len(self.outNodes)):
                    inToOutIndex = inNodeIndex + (outNodeIndex*self.inputNodeSize)
                    self.prevInToOutChange[inToOutIndex] = learningRate*self.outDeltas[outNodeIndex] + momentumRate*self.prevInToOutChange[inToOutIndex]
                    self.inToOutWeights[inToOutIndex] += self.prevInToOutChange[inToOutIndex]


    def getError(self, inputNodes,expectedOutputNodes):
        nn.processInput(inputNodes);
        self.trainError = 0;
        for outNodeIndex in range(len(self.outNodes)):
            self.trainError += math.pow(expectedOutputNodes[outNodeIndex] - self.outNodes[outNodeIndex],2)

        self.trainError = self.trainError / len(self.outNodes)
        return self.trainError

    # Pass in one given normalized input set along with expected output for training
    # Give leaning rate and momentum rate to control how much the new input affects the weight update
    # NOTE: also performs the weight change.
    def train(self, inputNodes, expectedOutputNodes, learningRate, momentumRate):
        self.processInput(inputNodes);
        #Calculate output deltas
        for outNodeIndex in range(len(self.outDeltas)):
            self.outDeltas[outNodeIndex] = (expectedOutputNodes[outNodeIndex] - self.outNodes[outNodeIndex])*self.activateDeriv(self.outNodes[outNodeIndex])

        if(len(self.hidNodes) > 0):
            for hidNodeIndex in range(len(self.hidNodes)):
                self.hidDeltas[hidNodeIndex] = 0
                for outNodeIndex in range(len(self.outNodes)):
                    #print(hidNodeIndex + (outNodeIndex*len(self.hidNodes)))
                    self.hidDeltas[hidNodeIndex] += self.outDeltas[outNodeIndex] * self.hidToOutWeights[hidNodeIndex + (outNodeIndex*len(self.hidNodes))]
                #print("\n")

        self.ApplyWeightChange(learningRate,momentumRate);


#print(str(sys.argv))

#nn = NeuralNetwork(4,3,1)
'''nn = '';



nn = NeuralNetwork(4,0,2,[],[])
nn.refresh()
for i in range(1000):
    nn.train([0.5,0.4,0.5,0.6],[0.1,0.8],0.2,0.8)
    #time.sleep(0.5)
    nn.processInput([0.5,0.4,0.5,0.6]);
    print(nn.outNodes,nn.getError([0.5,0.4,0.5,0.6],[0.1,0.8]))

nn2 = NeuralNetwork(4,3,2,nn.inToHidWeights,nn.hidToOutWeights)
nn2.processInput([0.5,0.4,0.5,0.6]);
print(nn2.outNodes)'''
