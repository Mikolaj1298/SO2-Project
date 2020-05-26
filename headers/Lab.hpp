#include <ncurses.h>
#include <string>
#include <string.h>
#include <sstream>
#include "Miner.hpp"
#include "GlobalData.hpp"

class Lab
{
    bool experiment;

    public:
        Lab();
        ~Lab();
        bool isExperimentActive();
};