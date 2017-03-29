#include "NeuralNetwork.h"

using namespace std;



NeuralNetwork::NeuralNetwork(){

}
NeuralNetwork::NeuralNetwork(int inputLayerSize, int hiddenLayerSize, int outputLayerSize,double newLearningRate,double newMomentumRate){
  inputLayer.resize(inputLayerSize);
  hiddenLayer.resize(hiddenLayerSize);
  outputLayer.resize(outputLayerSize);
  inToHiddenWeights.resize(inputLayerSize*hiddenLayerSize);
  inToHiddenWeightChanges.resize(inputLayerSize*hiddenLayerSize);
  hiddenToOutWeights.resize(hiddenLayerSize*outputLayerSize);
  hiddenToOutWeightChanges.resize(hiddenLayerSize*outputLayerSize);
  inToOutWeights.resize(inputLayerSize*outputLayerSize);
  inToOutWeightChanges.resize(inputLayerSize*outputLayerSize);
  printf("SIZE: %d\n",(int)hiddenToOutWeights.size());
  hiddenDeltas.resize(hiddenLayerSize);
  outputDeltas.resize(outputLayerSize);
  ResetWeights();
  learningRate = newLearningRate;
  momentumRate = newMomentumRate;
}
NeuralNetwork::~NeuralNetwork(){

}

void NeuralNetwork::ResetWeights(){
  default_random_engine gen;
  uniform_real_distribution<double> distribution(0.0,1.0);

  for(int weightIndex = 0; weightIndex < inToHiddenWeights.size();weightIndex++){
    inToHiddenWeights[weightIndex] = distribution(gen);
  }

  for(int weightIndex = 0; weightIndex < hiddenToOutWeights.size();weightIndex++){
    hiddenToOutWeights[weightIndex] = distribution(gen);
  }

  for(int weightIndex = 0; weightIndex < inToOutWeights.size();weightIndex++){
    inToOutWeights[weightIndex] = distribution(gen);
  }

}

void NeuralNetwork::ProcInput(vector<double> newInputLayer){
  // copy new inputLayer to class var
  for(int nodeIndex = 0; nodeIndex < inputLayer.size(); nodeIndex++){
    inputLayer[nodeIndex] = newInputLayer[nodeIndex];
  }

  if(hiddenLayer.size() > 0){
    // Gen hidden node values
    for(int hidNodeIndex = 0; hidNodeIndex < hiddenLayer.size(); hidNodeIndex++){
      hiddenLayer[hidNodeIndex] = 0;
      for(int inNodeIndex = 0; inNodeIndex < inputLayer.size(); inNodeIndex++){
        hiddenLayer[hidNodeIndex] += inputLayer[inNodeIndex]*inToHiddenWeights[((hidNodeIndex*inputLayer.size()) + inNodeIndex)];
        //printf("hid: %d, in: %d\n",hidNodeIndex,inNodeIndex);
        //printf("%d\n",(int)((hidNodeIndex*inputLayer.size()) + inNodeIndex));
      }
      hiddenLayer[hidNodeIndex] = Activation(hiddenLayer[hidNodeIndex]);
      //printf("---\n");
    }

    // Calculate out nodes
    for(int outNodeIndex = 0; outNodeIndex < outputLayer.size(); outNodeIndex++){
      outputLayer[outNodeIndex] = 0;
      for(int hidNodeIndex = 0; hidNodeIndex < hiddenLayer.size(); hidNodeIndex++){
        outputLayer[outNodeIndex] += hiddenLayer[hidNodeIndex]*hiddenToOutWeights[((outNodeIndex*hiddenLayer.size()) + hidNodeIndex)];

        //printf("out: %d, hid: %d\n",outNodeIndex,hidNodeIndex);
        //printf("%d\n",(int)((outNodeIndex*hiddenLayer.size()) + hidNodeIndex));
      }
      outputLayer[outNodeIndex] = Activation(outputLayer[outNodeIndex]);
      //printf("---\n");
    }
  }
  else{ // No Hidden layer
    // Calculate out nodes
    for(int outNodeIndex = 0; outNodeIndex < outputLayer.size(); outNodeIndex++){
      outputLayer[outNodeIndex] = 0;
      for(int inNodeIndex = 0; inNodeIndex < inputLayer.size(); inNodeIndex++){
        outputLayer[outNodeIndex] += inputLayer[inNodeIndex]*inToOutWeights[((outNodeIndex*inputLayer.size()) + inNodeIndex)];

        //printf("out: %d, in: %d\n",outNodeIndex,inNodeIndex);
        //printf("%d\n",(int)((outNodeIndex*inputLayer.size()) + inNodeIndex));
      }
      outputLayer[outNodeIndex] = Activation(outputLayer[outNodeIndex]);
      //printf("---\n");
    }
  }
}

void NeuralNetwork::Train(vector<double> newInputLayer,vector<double> expectedNormallizedOutNodes){
  ProcInput(newInputLayer);
  // Calculate OutNode Deltas
  //printf("out deltas\n");
  for (int outIndex = 0; outIndex < outputLayer.size(); outIndex++){
    outputDeltas[outIndex] = (expectedNormallizedOutNodes[outIndex] - outputLayer[outIndex])*ActivationPrime(outputLayer[outIndex]);
    //printf("%lf\n",outputDeltas[outIndex]);
  }
  //printf("END\n\n");
  PrintOutNodes();
  if(hiddenLayer.size() > 0){
    // Gen hidden layer deltas
    for (int hidNodeIndex = 0; hidNodeIndex < hiddenDeltas.size(); hidNodeIndex++){
      //printf("TEST : %d\n",hidNodeIndex);
  		hiddenDeltas[hidNodeIndex] = 0;
  		for (int outNodeIndex = 0; outNodeIndex < outputDeltas.size(); outNodeIndex++){
  			hiddenDeltas[hidNodeIndex] += hiddenToOutWeights[((hidNodeIndex*outputLayer.size()) + outNodeIndex)]*outputDeltas[outNodeIndex];
        //printf("out: %d, hid: %d\n",outNodeIndex,hidNodeIndex);
        //printf("%d\n",(int)((hidNodeIndex*outputLayer.size()) + outNodeIndex));
  		}
  		hiddenDeltas[hidNodeIndex] = ActivationPrime(hiddenLayer[hidNodeIndex])*hiddenDeltas[hidNodeIndex];
  	}
  }
  ApplyWeightChange();
}

// Scale the input values
double NeuralNetwork::Normalize(double val, double low, double high, double targetLow, double targetHigh){
	double numer = (val - low)*(targetHigh - targetLow);
	double denom = (high - low);
	return (numer / denom);
}



// Basic sigmoid activation function
double NeuralNetwork::Activation(double nodeVal){
	return (1 / (1 + pow(exp(1.0), -nodeVal)));
}

// Dervivative of the sigmoid activation function
double NeuralNetwork::ActivationPrime(double actVal){
	return Activation(actVal)*(1.0 - Activation(actVal));
}

void NeuralNetwork::ApplyWeightChange(){
  double newWeightChange = 0;
  int currWeightIndex = 0;

  if(hiddenLayer.size() > 0){
    // Apply weight change to hiddenToOutWeights
    for (int hidNodeIndex = 0; hidNodeIndex < hiddenDeltas.size(); hidNodeIndex++){
      //printf("TEST : %d\n",hidNodeIndex);
      for (int outNodeIndex = 0; outNodeIndex < outputDeltas.size(); outNodeIndex++){
        currWeightIndex = ((hidNodeIndex*outputLayer.size()) + outNodeIndex);
        newWeightChange = (-1.0*learningRate*outputDeltas[outNodeIndex]) + momentumRate*hiddenToOutWeightChanges[currWeightIndex];
        hiddenToOutWeightChanges[currWeightIndex] = newWeightChange - hiddenToOutWeights[currWeightIndex];
        hiddenToOutWeights[currWeightIndex] += newWeightChange;
      }
    }


    for(int inNodeIndex = 0; inNodeIndex < inputLayer.size(); inNodeIndex++){
      for(int hidNodeIndex = 0; hidNodeIndex < hiddenLayer.size(); hidNodeIndex++){
        currWeightIndex = ((inNodeIndex*hiddenLayer.size()) + hidNodeIndex);
        newWeightChange = (-1.0*learningRate*hiddenDeltas[hidNodeIndex]) + momentumRate*inToHiddenWeightChanges[currWeightIndex];
        inToHiddenWeightChanges[currWeightIndex] = newWeightChange - inToHiddenWeights[currWeightIndex];
        inToHiddenWeights[currWeightIndex] += newWeightChange;
      }
    }
  }
  else{
    // Apply weight change to inToOutWeights
    for (int inNodeIndex = 0; inNodeIndex < inputLayer.size(); inNodeIndex++){
      //printf("TEST : %d\n",hidNodeIndex);
      for (int outNodeIndex = 0; outNodeIndex < outputDeltas.size(); outNodeIndex++){
        currWeightIndex = ((inNodeIndex*outputLayer.size()) + outNodeIndex);
        newWeightChange = (-1.0*learningRate*outputDeltas[outNodeIndex]) + momentumRate*inToOutWeightChanges[currWeightIndex];
        //printf("WEIGHT: %d, %lf\n",currWeightIndex,newWeightChange);
        inToOutWeightChanges[currWeightIndex] = newWeightChange - inToOutWeights[currWeightIndex];
        inToOutWeights[currWeightIndex] += newWeightChange;
      }
    }
  }
}

void NeuralNetwork::PrintOutNodes(){
  printf("OUT NODES:\n");
  for(int outNodeIndex = 0; outNodeIndex < outputLayer.size();outNodeIndex++){
    // NOTE: TMP FIX FOR INVERSE
    if(hiddenLayer.size() > 0)
      printf("%lf\n",(1.0 - outputLayer[outNodeIndex]));
    else
      printf("%lf\n",(outputLayer[outNodeIndex]));
  }
}

vector<double> NeuralNetwork::GetOutputLayer(){
  return outputLayer;
}
