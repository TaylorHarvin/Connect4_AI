#include<vector>
#include<random>

class NeuralNetwork{
  public:
    NeuralNetwork();
    NeuralNetwork(int inputLayerSize, int hiddenLayerSize, int outputLayerSize,double newLearningRate,double newMomentumRate);
    ~NeuralNetwork();
    void ResetWeights();
    void ProcInput(std::vector<double> newInputLayer);
    double Normalize(double val, double low, double high, double targetLow, double targetHigh);
    void Train(std::vector<double> newInputLayer,std::vector<double> expectedNormallizedOutNodes);
    void PrintOutNodes();
    std::vector<double> GetOutputLayer();
  private:
    std::vector<double> inputLayer;
    std::vector<double> hiddenLayer;
    std::vector<double> outputLayer;
    std::vector<double> inToHiddenWeights;
    std::vector<double> inToHiddenWeightChanges;
    std::vector<double> hiddenToOutWeights;
    std::vector<double> hiddenToOutWeightChanges;
    std::vector<double> inToOutWeights;
    std::vector<double> inToOutWeightChanges;
    std::vector<double> hiddenDeltas;
    std::vector<double> outputDeltas;
    double learningRate;
    double momentumRate;


    double Activation(double nodeVal);
    double ActivationPrime(double actVal);
    void ApplyWeightChange();


};
