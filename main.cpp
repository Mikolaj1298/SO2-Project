#include <thread>
#include <ctime>
#include <mutex>
#include <condition_variable>
#include "./headers/GlobalData.hpp"
#include "./headers/Window.hpp"
#include "./headers/Trolley.hpp"


extern int rows;
extern int columns;
extern bool runningLoop;
extern int sourcesLeft;
extern std::vector<Miner*> miners;
extern int trolleyLoad;
extern bool queuePlace[6];

bool isTheTrolleyOccupied = false;
bool isTrolleyLocked = false;

std::vector<std::thread> minersThreads;
std::vector<std::thread> labThreads;
std::mutex diggingMutex;
std::mutex unloadingCoalMutex;
std::mutex notFinished;
std::mutex trolleyMutex;
std::mutex leaveTrolleyMutex;
std::condition_variable forbidFromUnloadingCoalSignal;
std::condition_variable trolleyNotAvailableSignal;

Window *window;
Trolley *trolley;

void ExitListener()
{
	// zakończ program gdy wciśnięto klawisz 'q'
	while(runningLoop)
	{
		cbreak();
		noecho();
		char key = getch();
		if (key == 'q')
		{
			runningLoop = false;
			forbidFromUnloadingCoalSignal.notify_all();
			trolleyNotAvailableSignal.notify_all();
		} 
		else std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void RenderScene()
{
	while(runningLoop)
	{
		clear();
		window->DrawScene();
		trolley->DrawTrolley();
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}
}

void CreateWindow()
{
	window = new Window();
	trolley = new Trolley();
}

void MoveTrolley()
{
	while(runningLoop)
	{
		std::unique_lock<std::mutex> lockTrolley(trolleyMutex);
		if (trolleyLoad == 100)
		{
			isTrolleyLocked = true;
		}
		lockTrolley.unlock();

		if (isTrolleyLocked)
		{
			// trolley->TakeTrolleyAway();
			trolley->UnloadTheTrolley();
			// trolley->GetTrolleyBack();
			isTrolleyLocked = false;
			trolleyNotAvailableSignal.notify_one();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void MoveMinerToTrolley(int indexOfMiner)
{
	miners[indexOfMiner]->GoToTheTrolley();
}

bool CheckIfMinerDugEnough(int indexOfMiner)
{
	/*if ((miners[indexOfMiner]->GetbasketCapacity() - miners[indexOfMiner]->GetdugCoal()) >= miners[indexOfMiner]->GetspeedOfDigging())
	{
		return true;
	}
	return false;*/
	return (miners[indexOfMiner]->GetbasketCapacity() - miners[indexOfMiner]->GetdugCoal()) >= miners[indexOfMiner]->GetspeedOfDigging();
}

bool RightAmountOfCoalDug(int indexOfMiner)
{
	/*if (sourcesLeft >= miners[indexOfMiner]->GetspeedOfDigging() && miners[indexOfMiner]->GetdugCoal() <= miners[indexOfMiner]->GetbasketCapacity())
	{
		return true;
	}
	return false;*/
	return sourcesLeft >= miners[indexOfMiner]->GetspeedOfDigging() && miners[indexOfMiner]->GetdugCoal() <= miners[indexOfMiner]->GetbasketCapacity();
}

bool IsMinersBasketFull(int indexOfMiner)
{
	/*if (miners[indexOfMiner]->GetdugCoal() == miners[indexOfMiner]->GetbasketCapacity())
	{
		return true;
	}
	return false;*/
	return miners[indexOfMiner]->GetdugCoal() == miners[indexOfMiner]->GetbasketCapacity();
}

void SendMinerToWork(int indexOfMiner)
{
	while(runningLoop && sourcesLeft >= 0 && miners[indexOfMiner]->GetdugCoal() <= miners[indexOfMiner]->GetbasketCapacity())
	{
		std::unique_lock<std::mutex> lockForDigging(diggingMutex);
		miners[indexOfMiner]->SetTube(true);
		if (RightAmountOfCoalDug(indexOfMiner))
		{
			if (CheckIfMinerDugEnough(indexOfMiner))
			{
				miners[indexOfMiner]->Dig(miners[indexOfMiner]->GetspeedOfDigging());
			}
			else {
				miners[indexOfMiner]->Dig(miners[indexOfMiner]->GetbasketCapacity() - miners[indexOfMiner]->GetdugCoal());
				miners[indexOfMiner]->StartExperiment();
			} 
			
		}
		lockForDigging.unlock();

		if (IsMinersBasketFull(indexOfMiner) /* || sourcesLeft == 0*/)
		{
			miners[indexOfMiner]->GoToTheTrolley(); // górnik musi dochodzić prędzej
			miners[indexOfMiner]->StopExperiment();
			std::unique_lock<std::mutex> lockForUnloadingCoal(unloadingCoalMutex);
			if (!isTheTrolleyOccupied)
			{
				miners[indexOfMiner]->LockTheTrolley();
			}
		  	else
		  	{
		  		/*for (int i = 0; i < count; ++i)
		  		{
		  		}*/
		  		forbidFromUnloadingCoalSignal.wait(lockForUnloadingCoal);
		  	}
		  	lockForUnloadingCoal.unlock();

		  	std::unique_lock<std::mutex> lockIfNotFinished(notFinished);
		  	if (miners[indexOfMiner]->GetdugCoal() != 0)
		  	{
		  		while(miners[indexOfMiner]->GetdugCoal() != 0)
				{
					if (trolleyLoad != 100 && !isTrolleyLocked)
					{
						miners[indexOfMiner]->FillTheTrolleyWithCoal();
						trolley->SetWorkingScientist(indexOfMiner+1);
						std::this_thread::sleep_for(std::chrono::milliseconds(400));
					}
				}
		  	}
		  	else trolleyNotAvailableSignal.wait(lockIfNotFinished);
			lockIfNotFinished.unlock();

			miners[indexOfMiner]->ReleaseTheTrolley();
			forbidFromUnloadingCoalSignal.notify_one();
			miners[indexOfMiner]->GoBackToWork();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}


void CreateMiners()
{
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		miners.push_back(new Miner(4 + i*8, columns / 4 - 8 , rand() % 300 + 100, i, true));
		minersThreads.push_back(std::thread(SendMinerToWork, i));
		// labThreads.push_back(std::thread(StartExperiment, i));
	}

	for (int i = 3; i < 6; i++)
	{
		miners.push_back(new Miner(-20 + i*8, columns  - 13, rand() % 300 + 100, i-3, true));
		minersThreads.push_back(std::thread(SendMinerToWork, i));
	}
}

void SendMinersOnHoliday()
{
	for (int i = 0; i < minersThreads.size(); i++)
	{
		minersThreads[i].join();
	}
}

int main(int argc, char const *argv[])
{
	initscr();
	CreateWindow();
	std::thread scene(RenderScene);
	std::thread trolleyThread(MoveTrolley);
	std::thread summonMiners(CreateMiners);
	std::thread exitProgram(ExitListener);
	trolleyThread.join();
	scene.join();
	summonMiners.join();
	exitProgram.join();
	SendMinersOnHoliday();
	
	delete trolley;
	delete window;
	return 0;
}