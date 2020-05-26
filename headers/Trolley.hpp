//#pragma once
#include <ncurses.h>
#include <thread>
#include <ctime>
#include "GlobalData.hpp"

class Trolley
{
	int trolleyDisplacement;

public:
	Trolley();
	~Trolley();
	void GetTrolleyBack();
	void TakeTrolleyAway();
	void StopTrolley();
	void DrawTrolley();
	void UnloadTheTrolley();
	void DecreaseTrolleyLoad(int valueOfDecreasement);
};