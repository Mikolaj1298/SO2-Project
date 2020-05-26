all:
	g++ -o minersAnimation main.cpp ./src/Miner.cpp ./src/Window.cpp ./src/Trolley.cpp ./headers/Miner.hpp ./headers/Window.hpp ./headers/Trolley.hpp -lncurses -lpthread
