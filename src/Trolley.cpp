#include "../headers/Trolley.hpp"
#include "../headers/Lab.hpp"

extern int trolleyLoad;
extern int thermocyclerRun;


Trolley::Trolley()
{
	getmaxyx(stdscr, rows, columns);
	actual = 6;
	offset = 0;
	runCounter = 0;
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
	attron(COLOR_PAIR(((offset + 0)%6)+1));
	mvprintw(rows/2-1, columns/2-1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-0, columns/2-4, "|");
	attron(COLOR_PAIR(((offset + 1)%6)+1));
	mvprintw(rows/2-0, columns/2-2, "o");
	attron(COLOR_PAIR(actual));
	
	mvprintw(rows/2+1, columns/2-4, "|");
	attron(COLOR_PAIR(((offset + 2)%6)+1));
	mvprintw(rows/2+1, columns/2-1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2+2, columns/2-4, "|");
	
	mvprintw(rows/2-2, columns/2+4, "|");
	attron(COLOR_PAIR(((offset + 3)%6)+1));
	mvprintw(rows/2-1, columns/2+1, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-1, columns/2+4, "|");
	attron(COLOR_PAIR(((offset + 4)%6)+1));
	mvprintw(rows/2-0, columns/2+2, "o");
	attron(COLOR_PAIR(actual));
	mvprintw(rows/2-0, columns/2+4, "|");
	attron(COLOR_PAIR(((offset + 5)%6)+1));
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
	thermocyclerRun++;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	actual = 6;
	offset = 0;
	while(trolleyLoad != 0 && runningLoop) // TUTAJ
	{
	    partOfCoal = rand() % 20 + 10;

		if (partOfCoal >= trolleyLoad)
		{
			partOfCoal = trolleyLoad;
		}

		DecreaseTrolleyLoad(partOfCoal);
		offset++;
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
	}
	offset = 0;
}

void Trolley::DecreaseTrolleyLoad(int valueOfDecreasement)
{
	trolleyLoad -= valueOfDecreasement;
}

void Trolley::SetWorkingScientist(int slot)
{
	actual = slot;
}

int Trolley::GetRunCounter()
{
	return runCounter;
}