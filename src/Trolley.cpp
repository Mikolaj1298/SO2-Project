#include "../headers/Trolley.hpp"

extern int trolleyLoad;

Trolley::Trolley()
{
	getmaxyx(stdscr, rows, columns);
}

Trolley::~Trolley() { }

void Trolley::GetTrolleyBack()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	trolleyDisplacement = 50;
	for (int i = 0; i < 50; i++)
	{
		if (runningLoop)
		{
			trolleyDisplacement--;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}
}

void Trolley::TakeTrolleyAway()
{
	trolleyDisplacement = 1;
	for (int i = 0; i < 50; i++)
	{
		if (runningLoop)
		{
			trolleyDisplacement++;
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
		}
	}

	//GetTrolleyBack();
}

void Trolley::StopTrolley()
{
	trolleyDisplacement = 0;
}

void Trolley::DrawTrolley()
{
	// for (int i = 0; i < 50; i++)
	// {
	// 	mvprintw(rows / 2 + 5, columns / 2 - 9 + i, "_");
	// }

	// for (int i = 0; i < 2; i++)
	// {
	// 	mvprintw(rows / 2 + 3 + i, columns / 2 - 10 + trolleyDisplacement, "|");
	// 	mvprintw(rows / 2 + 3 + i, columns / 2 + trolleyDisplacement, "|");
	// }

	// mvprintw(rows / 2 + 5, columns / 2 - 10 + trolleyDisplacement, "o");
	// mvprintw(rows / 2 + 5, columns / 2 + trolleyDisplacement, "o");
}

void Trolley::UnloadTheTrolley()
{
	srand(time(NULL));
	int partOfCoal;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	while(trolleyLoad != 0 && runningLoop) // TUTAJ
	{
	    partOfCoal = rand() % 20 + 10;

		if (partOfCoal >= trolleyLoad)
		{
			partOfCoal = trolleyLoad;
		}

		DecreaseTrolleyLoad(partOfCoal);
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
	}
}

void Trolley::DecreaseTrolleyLoad(int valueOfDecreasement)
{
	trolleyLoad -= valueOfDecreasement;
}