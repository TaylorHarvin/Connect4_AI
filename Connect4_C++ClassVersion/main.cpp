#include "GameBoardAI.h"



using namespace std;

int main(int argc, char* argv[]){
  Board mainBoard = Board();
  GameBoardAI mainBoardAI = GameBoardAI();
  int userColChoice = 0;
  int rowRes = 0;

  /*rowRes = mainBoard.PlayMove(3,USER);
  mainBoardAI.GenBestMove(mainBoard);*/
  while(true){
    printf("ENTER CHOICE: ");
    scanf("%d",&userColChoice);
    if(userColChoice > 6){
      mainBoard.Clear();
    }
    else{
      rowRes = mainBoard.PlayMove(userColChoice,USER);
      mainBoardAI.Learn(rowRes,userColChoice,mainBoard.GetFlatBoardState());
      mainBoard.PlayMove(mainBoardAI.GenBestMove(mainBoard),AI);
      mainBoard.PrintBoard(USER,false);
    }
  }


  //printf("BEST: %d\n",mainBoardAI.GuessPlayerAction_NN(mainBoard,USER));

  /*for(int i = 0; i < 10; i++){
    mainBoardAI.Learn(rowRes,3,mainBoard.GetFlatBoardState());
  }*/

  /*rowRes = mainBoard.PlayMove(3,USER);
  mainBoard.GetFlatBoardState(tmpFlatBoardState);
  mainBoardAI.Learn(rowRes,3,tmpFlatBoardState);

  rowRes = mainBoard.PlayMove(3,USER);
  mainBoard.GetFlatBoardState(tmpFlatBoardState);
  mainBoardAI.Learn(rowRes,3,tmpFlatBoardState);*/


  /*mainBoard.PrintBoard(USER,false);
  //mainBoardAI.GuessPlayerAction_Random(mainBoard,USER);
  printf("%s\n",string(mainBoard).c_str());
  printf("%d\n",mainBoardAI.GuessPlayerAction_Random(mainBoard,USER));
  printf("%d\n",mainBoardAI.GenBestMove(mainBoard));*/

  /*NeuralNetwork mainNet = NeuralNetwork(5,2,3,0.8,0.2);
  vector<double> expectedOut;
  expectedOut.resize(3);
  expectedOut[0] = 1.0;
  expectedOut[1] = 0.0;
  expectedOut[2] = 1.0;


  vector<double> tmpIn;
  tmpIn.resize(5);
  tmpIn[0] = 0.0;
  tmpIn[1] = 1.0;
  tmpIn[2] = 0.0;
  tmpIn[3] = 1.0;
  tmpIn[4] = 1.0;


  for(int i = 0; i < 100; i++){
    mainNet.Train(tmpIn,expectedOut);
    mainNet.ProcInput(tmpIn);
    mainNet.PrintOutNodes();
  }*/

  return 0;
}
