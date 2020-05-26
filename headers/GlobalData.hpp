#pragma once
#include "Miner.hpp"
#include <vector>

#ifndef GLOBAL_DATA_HPP
#define GLOBAL_DATA_HPP

extern int rows;
extern int columns;
extern bool runningLoop;
extern int sourcesLeft;
extern int trolleyLoad;
extern bool isTheTrolleyOccupied;
extern bool isTrolleyLocked;
extern std::vector<Miner*> miners;
extern int xPosTunelFromPlace;
extern int yPosTunelFromPlace;
extern bool isThisPlaceOccupied[6]; // dorób kolejkę oczekiwania górników!!!

#endif // GLOBAL_DATA_HPP