//#pragma once
#include <ncurses.h>
#include <string>
#include <string.h>
#include <sstream>
#include "Miner.hpp"
#include "GlobalData.hpp"

#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window
{
	int rows;
	int columns;
	int trolleyDisplacement;
	std::string minerLabel[6];
	std::string leftSourcesLabel;
	std::string thermocyclerRunLabel;
	std::string trolleyLoadLabel;
	char charArrayMinersLabel[20];
	char charArrayCoalLabel[20];
	char charArrayTrolleyLabel[20];
	char charArrayThermocyclerRunLabel[20];

public:
	Window();
	~Window();
	bool MakeDoor(int, int, int, int);
	void DrawLab(int, int);
	void MakeThermocycler();
	void DrawCoal();
	void DrawBorders();
	void DrawPlaces();
	void DrawMiners();
	void DrawTables();
	void DrawScene();
	char *MinersLabel(int indexOfMiner, Miner* miner);
	char *CoalLabel();
	char *TrolleyLabel();
	char *ThermocyclerRunLabel();
	void DisplayGlobalData();
	void DrawQueueOfMiners(); // ogarnąć kolejkowanie czekających górników
	void MakeQueueEmpty();
};

#endif // WINDOW_HPP


