#ifndef SHIPMENT_H
#define SHIPMENT_H

class Shipment
{
    private:
        string cargoType;
        string planetOne;
        string planetTwo;
        long int speed;     //miles per hour
        long long int travelDistance;   //miles (or millions of miles)
        double planetOneWeight;    //pounds
        double planetTwoWeight;    //pounds
        double earthWeight;        //pounds
        long double hours;
        //We don't have days or years here because they would become stale

    protected:

    public:
        //Mutators
        void setCargoType(string);
        void setPlanetOne(string);
        void setPlanetTwo(string);
        void setSpeed(long int);
        void setTravelDistance(const Planet *, int, int); //This is going to need information from the Planet structs to find distance
        void setPlanetOneWeight(int);
        void setPlanetTwoWeight(const Planet*, int, int);
        void setEarthWeight(int, const Planet *, int);
        void setHours(long double h = 0);
        //Accessors
        string getCargoType() const;
        string getPlanetOne() const;
        string getPlanetTwo() const;
        long int getSpeed()const;
        long long int getTravelDistance() const;
        double getPlanetOneWeight() const;
        double getPlanetTwoWeight() const;
        double getEarthWeight() const;
        long double getHours() const;
        long long int getDays() const;
        int getYears() const;

        Shipment();
        ~Shipment();
};

#endif // SHIPMENT_H
