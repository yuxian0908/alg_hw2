all:
	g++ -std=c++0x main.cpp Split.cpp Functions.cpp Epolygon.cpp Spolygon.cpp -o main.exe

test:
	g++ -std=c++0x main2.cpp Split.cpp Functions.cpp Epolygon.cpp Spolygon.cpp -o main.exe
