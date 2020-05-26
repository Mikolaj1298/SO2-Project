#include "../headers/Miner.hpp"
#include <thread>
#include <ctime>

extern int runningLoop;
extern int xPosTunelFromPlace;
extern int yPosTunelFromPlace;
extern int sourcesLeft;
extern bool isTheTrolleyOccupied;
extern int trolleyLoad;
extern int rows;
extern int floor;
extern int columns;
extern bool isThisPlaceOccupied[6];

Miner::Miner(int posX, int posY, int speedOfDiggingChoice, int floor)
{
	this->posX = posX;
	this->posY = posY;
	this->floor = floor;
	xPosOfWorkingPlace = posX;
	yPosOfWorkingPlace = posY;
	InitializeSpeedOfDigging(speedOfDiggingChoice);
	dugCoal = 0;
	InitializeBasketCapacity(rand() % 300 + 100);
}

Miner::~Miner() { }

void Miner::InitializeSpeedOfDigging(int choice)
{

	if (choice % 4 == 0) speedOfDigging = 1;
	else if (choice % 4 == 1) speedOfDigging = 2;
	else if (choice % 4 == 2) speedOfDigging = 4;
	else speedOfDigging = 5;
}

void Miner::InitializeBasketCapacity(int choice)
{
	if (choice % 3 == 0) basketCapacity = 35;
	else if (choice % 3 == 1) basketCapacity = 40;
	else basketCapacity = 50;
}

int Miner::GetspeedOfDigging()
{
	return speedOfDigging;
}

int Miner::GetbasketCapacity()
{
	return basketCapacity;
}

int Miner::GetdugCoal()
{
	return dugCoal;
}

void Miner::DecreasedugCoal(int decreasementValue)
{
	dugCoal -= decreasementValue;
}

int Miner::GetposX()
{
	return posX;
}

void Miner::SetposX(int posX)
{
	this->posX = posX;
}

int Miner::GetposY()
{
	return posY;
}

void Miner::SetposY(int posY)
{
	this->posY = posY;
}

void Miner::MoveToAnotherPlace()
{
	
}

void Miner::Dig(int value)
{
	sourcesLeft -= value;
	CollectCoalToBasket(value);
}

void Miner::CollectCoalToBasket(int collectedCoal)
{
	dugCoal += collectedCoal;
}

void Miner::IncreaseXPosition()
{
	posY++;
}

void Miner::DecreaseXPosition()
{
	posY--;
}

void Miner::IncreaseYPosition()
{
	posX++;
}

void Miner::DecreaseYPosition()
{
	posX--;
}

int Miner::GetFloor()
{
	return floor;
}

//ze środka na dół i do wózka
void Miner::GoFurther()
{
	
	for (int i = 0; i < 4; i++)
	{
		if (runningLoop)
		{
			if(Miner::GetFloor() == 0){
				IncreaseYPosition();
				std::this_thread::sleep_for(std::chrono::milliseconds(350));
			}
			if(Miner::GetFloor() == 2){
				DecreaseYPosition();
				std::this_thread::sleep_for(std::chrono::milliseconds(350));
			}
			
		}
		else break; // TUTAJ
	}

	// for (int i = 0; i < 2; i++)
	// {
	// 	if (runningLoop)
	// 	{
	// 		DecreaseXPosition();
	// 		std::this_thread::sleep_for(std::chrono::milliseconds(350));
	// 	}
	// 	else break; // TUTAJ
	// }

	//GoBackToWork();
}

// Z laboratorium do środka (lewi i prawi)
void Miner::GoToTheTrolley()
{
	DecreaseYPosition();
	std::this_thread::sleep_for(std::chrono::milliseconds(350));

	if(GetposY() < xPosTunelFromPlace)
	{
		while(GetposY() < xPosTunelFromPlace-9 && runningLoop)
		{
			IncreaseXPosition();
			std::this_thread::sleep_for(std::chrono::milliseconds(350));
		}
	}
	else if (GetposY() > xPosTunelFromPlace)
	{
		while(GetposY() > xPosTunelFromPlace+9 && runningLoop)
		{
			DecreaseXPosition();
			std::this_thread::sleep_for(std::chrono::milliseconds(350));
		}
	}

	GoFurther();
}


// Ze środka do laboratorium
void Miner::GoToWorkingPlace()
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));

	if(GetposY() > yPosOfWorkingPlace)
	{
		while(GetposY() > yPosOfWorkingPlace && runningLoop)
		{
			DecreaseXPosition();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}
	else if (GetposY() < yPosOfWorkingPlace)
	{
		while(GetposY() < yPosOfWorkingPlace && runningLoop)
		{
			IncreaseXPosition();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}

	IncreaseYPosition();
}


void Miner::FillTheTrolleyWithCoal()
{
	// górnik jednorazowo może wyrzucić od 1 do 5 jednostek węgla
	srand(time(NULL));
	int randomCoalDecreasement = rand() % 5 + 1;

	if (randomCoalDecreasement >= (300 - trolleyLoad))
	{
		randomCoalDecreasement = 300 - trolleyLoad;
	}
	else if (randomCoalDecreasement >= GetdugCoal())
	{
		randomCoalDecreasement = GetdugCoal();
	}

	trolleyLoad += randomCoalDecreasement;
	DecreasedugCoal(randomCoalDecreasement);
}

 // z dołu do środka i do góry
void Miner::GoBackToWork()
{
	// for (int i = 0; i < 7; i++)
	// {
	// 	if (runningLoop)
	// 	{
	// 		IncreaseXPosition();
	// 		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	// 	}
	// 	else break; // TUTAJ
	// }

	for (int i = 0; i < 4; i++)
	{
		if (runningLoop)
		{
			if(Miner::GetFloor() == 0)
			{
				DecreaseYPosition();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}
			if(Miner::GetFloor() == 2)
			{
				IncreaseYPosition();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}
		}
		else break; // TUTAJ
	}
	GoToWorkingPlace();
}

void Miner::LockTheTrolley()
{
	isTheTrolleyOccupied = true;
}

void Miner::ReleaseTheTrolley()
{
	isTheTrolleyOccupied = false;
}

void Miner::LockThePlaceInQueue(int nrOfPlace)
{
	isThisPlaceOccupied[nrOfPlace] = true;
}

void Miner::StartExperiment()
{
	activeExperiment = true;
}

void Miner::StopExperiment()
{
	activeExperiment = false;
}