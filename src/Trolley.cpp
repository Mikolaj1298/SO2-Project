#include "../headers/Trolley.hpp"

extern int trolleyLoad;

Trolley::Trolley()
{
	getmaxyx(stdscr, rows, columns);
	actual = 6;
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
	actual = 1;
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
	
	
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-2, columns/2-4, "|");
	mvprintw(rows/2-1, columns/2-4, "|");
	attron(COLOR_PAIR(1));
	mvprintw(rows/2-1, columns/2-1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-0, columns/2-4, "|");
	attron(COLOR_PAIR(2));
	mvprintw(rows/2-0, columns/2-2, "o");
	attron(COLOR_PAIR(actual));
	
	mvprintw(rows/2+1, columns/2-4, "|");
	attron(COLOR_PAIR(3));
	mvprintw(rows/2+1, columns/2-1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2+2, columns/2-4, "|");
	
	mvprintw(rows/2-2, columns/2+4, "|");
	attron(COLOR_PAIR(4));
	mvprintw(rows/2-1, columns/2+1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-1, columns/2+4, "|");
	attron(COLOR_PAIR(5));
	mvprintw(rows/2-0, columns/2+2, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-0, columns/2+4, "|");
	attron(COLOR_PAIR(6));
	mvprintw(rows/2+1, columns/2+1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2+1, columns/2+4, "|");
	mvprintw(rows/2+2, columns/2+4, "|");

	mvprintw(rows/2+2, columns/2+3, "-");
	mvprintw(rows/2+2, columns/2+2, "-");
	mvprintw(rows/2+2, columns/2+1, "-");
	mvprintw(rows/2+2, columns/2, "-");
	mvprintw(rows/2+2, columns/2-1, "-");
	mvprintw(rows/2+2, columns/2-2, "-");
	mvprintw(rows/2+2, columns/2-3, "-");
	
	mvprintw(rows/2-2, columns/2+3, "-");
	mvprintw(rows/2-2, columns/2+2, "-");
	mvprintw(rows/2-2, columns/2+1, "-");
	mvprintw(rows/2-2, columns/2, "-");
	// mvprintw(rows/2-1, columns/2, "o");
	mvprintw(rows/2-2, columns/2-1, "-");
	mvprintw(rows/2-2, columns/2-2, "-");
	mvprintw(rows/2-2, columns/2-3, "-");

	
	mvprintw(rows/2, columns/2, "X");
	attron(COLOR_PAIR(6));
}

void Trolley::UnloadTheTrolley()
{
	srand(time(NULL));
	int partOfCoal;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	actual = 6;
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

void Trolley::SetWorkingScientist(int slot)
{
	actual = slot;
}