INC=-I./

default: all

all:
	g++ -std=c++0x -Wall $(INC) main.cpp Split.cpp Spolygon.cpp -o main.exe

test:
	g++ -std=c++0x -Wall $(INC) main2.cpp Split.cpp Spolygon.cpp -o main.exe
