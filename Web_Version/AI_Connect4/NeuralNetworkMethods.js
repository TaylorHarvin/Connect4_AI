
// Neural network variables
var LEARNING_RATE = 0.8;
var MOMENT_RATE = 0;

var NUM_OUTPUT = 7;
var NUM_HIDDEN = 41;
var NUM_INPUT = 42;

//double nnInToOutWeight[42][NUM_OUTPUT];	// Just for the no hidden layer test
var nnInToHiddenWeights =[]/*[NUM_INPUT][NUM_HIDDEN]*/; // Rows --> input nodes, Cols --> hidden nodes
var nnHiddelLayer = Array()/*[NUM_HIDDEN]*/;
var nnHiddenDeltas = []/*[NUM_HIDDEN]*/;
var nnHiddenToOutWeights= []/*[NUM_HIDDEN][NUM_OUTPUT]*/;
var nnOutputLayer = []/*[NUM_OUTPUT]*/;
var nnOutDeltas = []/*[NUM_OUTPUT]*/;
// ^^^Neural network variables


// Init in to hidden
	for (var row = 0; row < NUM_INPUT; row++){
		nnInToHiddenWeights[row] = [];
		for (var col = 0; col < NUM_HIDDEN; col++){
			nnInToHiddenWeights[row][col] = Math.random();
		}
	}
	
	// Init hidden to out
	for (var row = 0; row < NUM_HIDDEN; row++){
		nnHiddenToOutWeights[row] = Array();
		for (var col = 0; col < NUM_OUTPUT; col++){
			nnHiddenToOutWeights[row][col] = Math.random();
		}
	}

alert(nnInToHiddenWeights[0][0]);

// Basic sigmoid activation function
function Activation(nodeVal){
	return (1 / (1 + Math.pow(Math.exp(1.0), -nodeVal)));
}

// Dervivative of the sigmoid activation function
function ActivationPrime(actVal){
	return Activation(actVal)*(1.0 - Activation(actVal));
}


// Set the random weights of the 
function InitNeuralNetwork(){
	// Init in to hidden
	/*for (var row = 0; row < NUM_INPUT; row++){
		nnInToHiddenWeights[row] = [];
		for (var col = 0; col < NUM_HIDDEN; col++){
			nnInToHiddenWeights[row][col] = Math.random();
		}
	}
	
	// Init hidden to out
	for (var row = 0; row < NUM_HIDDEN; row++){
		nnHiddenToOutWeights[row] = Array();
		for (var col = 0; col < NUM_OUTPUT; col++){
			nnHiddenToOutWeights[row][col] = Math.random();
		}
	}*/
}

// Scale the input values
function Normalize(val, low, high, targetLow, targetHigh){
	var numer = (val - low)*(targetHigh - targetLow);
	var denom = (high - low);
	return (numer / denom);
}


function ProcessNNInput(currBoard){
	var boardRow = 0;
	var boardCol = 0;


	// Calculate hidden layer vals from input
	for (var hid = 0; hid < NUM_HIDDEN; hid++){
		nnHiddelLayer[hid] = 0;
		// Sum up all connections from all input to an individual hidden node
		for (var inIndex = 0; inIndex < NUM_INPUT; inIndex++){
			boardRow = Math.floor(inIndex / 7);
			boardCol = Math.floor(inIndex % 7);
			//console.log(boardRow +" , "+boardCol);
			nnHiddelLayer[hid] += Normalize(currBoard[boardRow][boardCol], 0, 2, 0, 1) * nnInToHiddenWeights[inIndex][hid];
			
				
		}
		
	}


	// Calculate hidden to output
	for (var out = 0; out < NUM_OUTPUT; out++){
		nnOutputLayer[out] = 0;
		// Sum up all connections from all hidden to an individual out node
		for (var hid = 0; hid < NUM_HIDDEN; hid++){
			nnOutputLayer[out] += nnHiddelLayer[hid] * nnHiddenToOutWeights[hid][out];
		}
	}
	//alert(nnOutputLayer[out]);
}

function MeanSquaredError(userSelectedSlot){
	var finalError = 0;

	for (var outIndex = 0; outIndex < 7; outIndex++){
		if (outIndex != userSelectedSlot)
			finalError += (0 - nnOutputLayer[outIndex]);
		else
			finalError += (1 - nnOutputLayer[outIndex]);
	}
	finalError *= (1.0 / 7.0);
	return finalError;
}


function ApplyWeightChange(){
	// Apply the weight change for hidden to output
	for (var hid = 0; hid < NUM_HIDDEN; hid++){
		for (var out = 0; out < NUM_OUTPUT; out++){
			nnHiddenToOutWeights[hid][out] = LEARNING_RATE*nnOutDeltas[out] /*+ MOMENT_RATE*prevWeightChange[nodeIndex]*/;
		}
	}

	// Apply the weight change for input to hidden
	for (var inIndex = 0; inIndex < NUM_INPUT; inIndex++){
		for (var hid = 0; hid < NUM_HIDDEN; hid++){
			nnInToHiddenWeights[inIndex][hid] = LEARNING_RATE*nnHiddenDeltas[hid] /*+ MOMENT_RATE*prevWeightChange[nodeIndex]*/;
		}
	}
}

function TrainNeuralNet(userSelectedSlot){

	// Calculate output deltas
	for (var outIndex = 0; outIndex < 7; outIndex++){
		if (outIndex != userSelectedSlot)
			nnOutDeltas[outIndex] = (0 - nnOutputLayer[outIndex])*ActivationPrime(nnOutputLayer[outIndex]);
		else
			nnOutDeltas[outIndex] = (1 - nnOutputLayer[outIndex])*ActivationPrime(nnOutputLayer[outIndex]);
	}

	// Calculate hidden deltas
	for (var hid = 0; hid < NUM_HIDDEN; hid++){
		nnHiddenDeltas[hid] = 0;
		for (var out = 0; out < NUM_OUTPUT; out++){
			nnHiddenDeltas[hid] += nnHiddenToOutWeights[hid][out]*nnOutDeltas[out];
		}
		nnHiddenDeltas[hid] *= ActivationPrime(nnHiddelLayer[hid]);
	}

	ApplyWeightChange();
}



