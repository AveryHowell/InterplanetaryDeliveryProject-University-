#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <ctime>
#include <math.h>

using namespace std;

const int MIN_PLANET = 1;
const int NUM_PLANETS = 8;
const int MIN_WEIGHT = 1;
const int MAX_WEIGHT = 53000;
const int MAX_EARTH_WEIGHT = 20000;
const int MIN_SPEED = 1;
const int MAX_SPEED = 670616629;

struct Planet
{
    string name;
    long long int distance; //This is a long long in case we turn it from x million miles into just miles
    double gravity;
};

void readInput(fstream &, Planet *, int);
bool userContinue();
int enterAmount(int &, const int, const int);
void enterCargo(string &);
void enterPlanet(string &, const Planet *, int &);

#endif // HEADER_H_INCLUDED
