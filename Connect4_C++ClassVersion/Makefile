all : clean connect4
clean:
	rm -rf connect4
	rm -rf *.o
connect4: main.o board.o gameboardai.o neuralnetwork.o
	g++ -std=c++11 main.o Board.o GameBoardAI.o NeuralNetwork.o -o connect4
	
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
	
board.o: Board.cpp Board.h
	g++ -std=c++11 -c Board.cpp
	
gameboardai.o: GameBoardAI.cpp GameBoardAI.h
	g++ -std=c++11 -c GameBoardAI.cpp

neuralnetwork.o: NeuralNetwork.cpp NeuralNetwork.h
	g++ -std=c++11 -c NeuralNetwork.cpp
