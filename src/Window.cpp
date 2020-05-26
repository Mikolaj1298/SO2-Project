#include "../headers/Window.hpp"

int rows = 0;
int columns = 0;
bool runningLoop = true;
int xPosTunelFromPlace;
int yPosTunelFromPlace;
int trolleyLoad = 0;
int sourcesLeft = 880;
bool isThisPlaceOccupied[6];
std::vector<Miner*> miners;
int x;

Window::Window()
{
	if (has_colors() == TRUE)
	{
		start_color();
		attron(A_BOLD);
		minerLabel[0] = "Dr Oetker";
		minerLabel[1] = "Dr Dre";
		minerLabel[2] = "Dr House";
		minerLabel[3] = "Dr Dolittle";
		minerLabel[4] = "Dr Wit";
		minerLabel[5] = "Dr Lecter ";

		leftSourcesLabel = "Pozostale zloza:\t";
		trolleyLoadLabel = "Ladunek kolejki: ";
		getmaxyx(stdscr, rows, columns);
		xPosTunelFromPlace = columns / 2;
		yPosTunelFromPlace = rows / 2 + 1;
		MakeQueueEmpty();
		initscr();
		curs_set(0);
	}
}

Window::~Window()
{
	endwin();
}

void Window::DrawCoal()
{

}

// void Window::DrawBorders()
// {
// 	for (int i = 0; i < columns / 2 - 2; i++)
// 	{
// 		mvprintw(rows / 4, i, "_");
// 	}

// 	for (int i = 0; i < 5; i++)
// 	{
// 		mvprintw(rows / 4 + i + 1, columns / 2 - 3, "|");
// 	}
// 	for (int i = 0; i < 5; i++)
// 	{
// 		mvprintw(rows / 4 + i + 1, columns / 2 + 3, "|");
// 	}

// 	for (int i = columns; i > columns / 2 + 2; i--)
// 	{
// 		mvprintw(rows / 4, i, "_");
// 	}
// }

void Window::DrawBorders()
{
	//prawa pionowa ściana
	for (int i = 0; i < rows; i++)
	{
		int door1 = 2;
		int door2 = 10;
		int door3 = 18;
		if(MakeDoor(door1, door2, door3, i)) {
			mvprintw(rows - i -1, columns - 21 , "");
		} else {
			mvprintw(rows - i -1, columns - 21 , "|");
		}
	}

	DrawLab(rows -18, 4);
	DrawLab(rows -10, 4);
	DrawLab(rows -2, 4);
	
	DrawLab(rows -18, columns-9);
	DrawLab(rows -10, columns-9);
	DrawLab(rows -2, columns-9);

	//lewa pionowa ściana
	for (int i = 0; i < rows; i++)
	{
		
		int door1 = 2;
		int door2 = 10;
		int door3 = 18;
		if(MakeDoor(door1, door2, door3, i)) {
			mvprintw(rows - i -1, 20 , "");
		} else {
			mvprintw(rows - i -1, 20 , "|");
		}
	}

	//prawa ściana dolna
	for (int i = columns; i > columns -21; i--)
	{
		mvprintw(rows -9 , i, "_");
	}

	//prawa ściana górna
	for (int i = columns; i > columns -21; i--)
	{
		mvprintw(rows -17 , i, "_");
	}

	//lewa ściana dolna
	for (int i = 0; i < 20; i++)
	{
		mvprintw(rows -9 , i, "_");
	}

	// lewa ściana górna
	for (int i = 0; i < 20; i++)
	{
		mvprintw(rows -17 , i, "_");
	}

	// for (int i = columns; i > columns / 2 + 2; i--)
	// {
	// 	mvprintw(4 , i, "_");
	// }
}

bool Window::MakeDoor(int door1, int door2, int door3, int i){
	if((i == door1) || (i == door1+1) || (i == door1+2)     || (i == door2) || (i == door2+1) || (i == door2+2)     || (i == door3) || (i == door3+1) || (i == door3+2)){
		return true;
	} else {
		return false;
	}
}

void Window::DrawLab(int y, int x){
	mvprintw(y , x, "X");
	mvprintw(y-1 , x-1, "_");
	mvprintw(y-1, x, "_");
	mvprintw(y-1, x+1, "_");
	mvprintw(y-1, x+2, "_");
	mvprintw(y-1, x+3, "_");
	mvprintw(y , x+2, "X");
	//mvprintw(y-1 , x+2, "U");

	// mvprintw(y , x, "X");
	// mvprintw(y , x+1, "X");
	// mvprintw(y-1 , x, "_");
	// mvprintw(y-1 , x+1, "_");
	// mvprintw(y-1 , x-1, "_");
	// mvprintw(y-1 , x+2, "_");

}

void Window::MakeThermocycler(){
	mvprintw(rows/2-2, columns/2-4, "|");
	mvprintw(rows/2-1, columns/2-4, "|");
	mvprintw(rows/2-0, columns/2-4, "|");
	mvprintw(rows/2+1, columns/2-4, "|");
	mvprintw(rows/2+2, columns/2-4, "|");
	
	mvprintw(rows/2-2, columns/2+4, "|");
	mvprintw(rows/2-1, columns/2+4, "|");
	mvprintw(rows/2-0, columns/2+4, "|");
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
	mvprintw(rows/2-2, columns/2-1, "-");
	mvprintw(rows/2-2, columns/2-2, "-");
	mvprintw(rows/2-2, columns/2-3, "-");

	mvprintw(rows/2, columns/2, "O");

	// mvprintw(rows/2+2, columns/2-2, "_");
	// mvprintw(rows/2+2, columns/2+2, "|");
	// mvprintw(rows/2-2, columns/2+2, "|");
}

void Window::DrawPlaces() {

}


// void Window::DrawPlaces()
// {
// 	for (int i = 0; i < 3; i++)
// 	{
// 		mvprintw(rows / 4 - 2, columns / 8 - 5 + 12 * i, "|");
// 		mvprintw(rows / 4 - 2, columns / 8 - 4 + 12 * i, "_");
// 		mvprintw(rows / 4 - 2, columns / 8 - 3 + 12 * i, "|");
// 	}

// 	for (int i = 0; i < 3; i++)
// 	{
// 		mvprintw(rows / 4 - 2, columns / 8 + 40 + 12 * i, "|");
// 		mvprintw(rows / 4 - 2, columns / 8 + 41 + 12 * i, "_");
// 		mvprintw(rows / 4 - 2, columns / 8 + 42 + 12 * i, "|");
// 	}
// }

void Window::DrawMiners()
{
	// init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);

	for (int i = 0; i < miners.size(); i++)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(miners[i]->GetposX(), miners[i]->GetposY(), "O");
		mvprintw(miners[i]->GetposX()+1, miners[i]->GetposY(), "|");
		mvprintw(miners[i]->GetposX()+1, miners[i]->GetposY()+1, "-");
		mvprintw(miners[i]->GetposX()+1, miners[i]->GetposY()-1, "-");
		mvprintw(miners[i]->GetposX()+1, miners[i]->GetposY()-2, "U");
		mvprintw(miners[i]->GetposX()+2, miners[i]->GetposY(), "^");
		attroff(COLOR_PAIR(i + 1));
	}
}

char *Window::MinersLabel(int indexOfMiner, Miner* miner)
{
	std::stringstream bufferLabel;
	std::string temporaryLabelInString;
	bufferLabel << minerLabel[indexOfMiner] <<  ": " << miner->GetdugCoal() << "/" << miners[indexOfMiner]->GetbasketCapacity();
	temporaryLabelInString = bufferLabel.str();
	strcpy(charArrayMinersLabel, temporaryLabelInString.c_str());
	return charArrayMinersLabel;
}

char *Window::CoalLabel()
{
	// std::stringstream bufferLabel;
	// std::string temporaryLabelInString;
	// bufferLabel << leftSourcesLabel << sourcesLeft << "/880";
	// temporaryLabelInString = bufferLabel.str();
	// strcpy(charArrayCoalLabel, temporaryLabelInString.c_str());
	// return charArrayCoalLabel;
}

char *Window::TrolleyLabel()
{
	std::stringstream bufferLabel;
	std::string temporaryLabelInString;
	bufferLabel << trolleyLoadLabel << trolleyLoad << "/300";
	temporaryLabelInString = bufferLabel.str();
	strcpy(charArrayTrolleyLabel, temporaryLabelInString.c_str());
	return charArrayTrolleyLabel;
}

void Window::DrawTables()
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);

	for (int i = 0; i < miners.size()/2; i++)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(1 + 8 * i, 1, MinersLabel(i, miners[i]));
		attroff(COLOR_PAIR(i));
	}

	for (int i = miners.size()/2; i < miners.size(); i++)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(1 + 8 * i - 24, columns - 18, MinersLabel(i, miners[i]));
		attroff(COLOR_PAIR(i));
	}
}

void Window::DisplayGlobalData()
{
	// mvprintw(rows / 3, columns - 30, CoalLabel());
	mvprintw( 1, columns / 2 - 11, TrolleyLabel());
}

void Window::DrawScene()
{
	DrawBorders();
	DrawPlaces();
	MakeThermocycler();
	DrawMiners();
	DrawTables();
	DisplayGlobalData();
}

void Window::DrawQueueOfMiners()
{
	
}

void Window::MakeQueueEmpty()
{
	for (int i = 0; i < 6; i++)
	{
		isThisPlaceOccupied[i] = false;
	}
}