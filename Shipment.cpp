#ifndef SHIPMENT_CPP
#define SHIPMENT_CPP

#include "header.h"
#include "Shipment.h"

void Shipment::setCargoType(string type) {
    cargoType = type;
}
void Shipment::setPlanetOne(string planet) {
    planetOne = planet;
}
void Shipment::setPlanetTwo(string planet) {
    planetTwo = planet;
}
void Shipment::setSpeed(long int s) {
    speed = s;
}
void Shipment::setTravelDistance(const Planet *p, int i, int j) {
    int a, b;
    a = (p + i)->distance;
    b = (p + j)->distance;
    if (a > b) {    //This will keep the distance positive
        travelDistance = a - b;
    }
    else {
        travelDistance = b - a;
    }
}
void Shipment::setPlanetOneWeight(int w) {
    planetOneWeight = w;
}
void Shipment::setPlanetTwoWeight(const Planet *p, int i, int j) {     //Planet p is the second planet
    planetTwoWeight = (planetOneWeight / (p + i)->gravity) * (p + j)->gravity;
}
void Shipment::setEarthWeight(int w, const Planet *p, int i) { //Planet p is the first planet
    earthWeight = (w / (p + i)->gravity);
}
void Shipment::setHours(long double h) {
    h = ((travelDistance * 1000000) / static_cast<double>(speed));   //This is to account for million miles. X million miles / speed equals hours
    hours = h;
}

string Shipment::getCargoType() const {
    return cargoType;
}
string Shipment::getPlanetOne() const {
    return planetOne;
}
string Shipment::getPlanetTwo() const {
    return planetTwo;
}
long int Shipment::getSpeed()const {
    return speed;
}
long long int Shipment::getTravelDistance() const {
    return travelDistance;
}
double Shipment::getPlanetOneWeight() const {
    return planetOneWeight;
}
double Shipment::getPlanetTwoWeight() const {
    return planetTwoWeight;
}
double Shipment::getEarthWeight() const {
    return earthWeight;
}
long double Shipment::getHours() const {
    if (hours < 24) {
        return hours;
    }
    else {
        return fmod(hours, 24);
    }
}
long long int Shipment::getDays() const {   //We do this calculation here to avoid stale data
    return fmod((hours / 24), 365);
}
int Shipment::getYears() const {
    return (hours / 24) / 365;
}

Shipment::Shipment()
{
    cargoType = "";
    planetOne = "";
    planetTwo= "";
    speed = 0;
    travelDistance = 0;
    planetOneWeight = 0;
    planetTwoWeight = 0;
    earthWeight = 0;
    hours = 0;
}

Shipment::~Shipment()
{
    //Open for use...
}

#endif // SHIPMENT_CPP
