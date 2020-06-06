//#pragma once

#ifndef MINER_HPP
#define MINER_HPP

class Miner
{
	int dugCoal;
	int basketCapacity;
	int posX;
	int posY;
	int floor;
	int speedOfDigging;
	int xPosOfWorkingPlace;
	int yPosOfWorkingPlace;
	bool activeExperiment;
	bool hasTube;

public:
	Miner(int posX, int posY, int speedOfDiggingChoice, int floor, bool hasTube);
	~Miner();
	int GetdugCoal();
	void DecreasedugCoal(int decreasementValue);
	int GetspeedOfDigging();
	int GetbasketCapacity();
	int GetposX();
	void SetposX(int posX);
	int GetposY();
	void SetposY(int posY);
	void MoveToAnotherPlace();
	void Dig(int value);
	void InitializeSpeedOfDigging(int choice);
	void InitializeBasketCapacity(int choice);
	void CollectCoalToBasket(int collectedCoal);
	void GoToTheTrolley();
	void FillTheTrolleyWithCoal();
	void IncreaseXPosition();
	void DecreaseXPosition();
	void IncreaseYPosition();
	void DecreaseYPosition();
	int GetFloor();
	void GoFurther();
	void GoBackToWork();
	void GoToWorkingPlace();
	void LockTheTrolley();
	void ReleaseTheTrolley();
	void LockThePlaceInQueue(int nrOfPlace);
	void StopExperiment();
	void StartExperiment();
	bool CheckTube();
	void SetTube(bool tube);
};

#endif // MINER_HPP


