//cjlutterloh
//CS/CE 1337.505
//Project #5

/*
PROJECT NOTES
1. "Ensure that your program will not crash if a string is entered for a numeric value and vice versa."
    a. The program does not crash, but to be clear, I just made sure the user must continue to give input until it is valid
2. "The program must use a structure for the planets and the shuttle."
    a. I was approved to create a class, which is just an advanced structure
3. "Your program should create an array of planet structures initialized by reading data from a file."
    a. No input format was given, but I have ensured there is file validation, as well as a user opportunity to check the data
4. "At a minimum, the program should use a function for each of the following tasks..."
    a. Some of the functions are in the .cpp, but all have been verified as functions

    THANK YOU!
*/

#include "header.h"
#include "Shipment.h"

int main()
{
    try {
        Planet planetList[NUM_PLANETS];
        string planetName;
        int count = 0;

        //ESTABLISH NECESSARY FILES
        fstream fout("Delivery_Report.txt", ios::app);
        fstream fin("PlanetInfo.txt", ios::in);

        //EXTRACT THE NAME, DISTANCE, AND GRAVITY FROM THE INPUT FILE
        while (fin >> planetName && count < NUM_PLANETS) {    //This ensures any extra line after all of the planets is not counted
            //Ensures the file opens successfully
            if (!fin) {
                cout << "The program is unable to open the input file" << endl;
                return -1;
            }
            else {
                //Validates that the planet name only contains letters
                for (unsigned int i = 0; i < planetName.length(); i++) {
                    if (!isalpha(planetName[i])) {
                        cout << "The planet " << planetName << " contains input other than letters" << endl;    //Checks for valid planet name in input
                        return -1;
                    }
                }
                planetList[count].name = planetName;
                readInput(fin, planetList, count);
                count++;
                fin.ignore(512, '\n'); //Skips anything on the file line after the name
            }
        }

        //PRINT OUT THE FILE INPUT
        for (int i = 0; i < 8; i++) {
            cout << "Planet " << planetList[i].name << " has a distance of " << planetList[i].distance << fixed << setprecision(2) <<
            " million miles away from the sun and also has a gravity factor of " << planetList[i].gravity << endl;
        }
        //Let the user double check the information
        cout << "\nDoes the above information look correct? (Y/N)" << endl;
        if (!userContinue()) {
            cout << "Please review your input file and restart the program" << endl;
            exit (EXIT_FAILURE);
        }

        do {
            //LET THE USER ENTER INFORMATION
            Shipment *shipPtr = nullptr;
            shipPtr = new Shipment;

            //Type of cargo
            string cargo;
            cout << "What type of cargo would you like transported today?" << endl;
            enterCargo(cargo);
            shipPtr->setCargoType(cargo);

            //Planet to and from
            string planetChoice;
            int identifier1 = 0;
            int identifier2 = 0;
            while (identifier1 == identifier2) {    //Make sure both planets aren't the same
                cout << "Which planet are you shipping FROM?" << endl;
                enterPlanet(planetChoice, planetList, identifier1);
                shipPtr->setPlanetOne(planetChoice);
                cout << "Which planet are you shipping TO?" << endl;
                enterPlanet(planetChoice, planetList, identifier2);
                shipPtr->setPlanetTwo(planetChoice);
                if (identifier1 == identifier2) {
                    cout << "\nNOTE: You cannot ship to the same planet\n" << endl;
                }
            }

            //Weight of cargo
            int weightAmount;
            do {
            cout << "What is the weight of the cargo? (In lbs from the planet " << shipPtr->getPlanetOne() << ")" << endl;
            enterAmount(weightAmount, MIN_WEIGHT, MAX_WEIGHT);
            cout << fixed << setprecision(2);
            shipPtr->setPlanetOneWeight(weightAmount);
            shipPtr->setEarthWeight(weightAmount, planetList, identifier1);
            shipPtr->setPlanetTwoWeight(planetList, identifier1, identifier2);
            cout << shipPtr->getEarthWeight() << " LBS IS THE EARTH WEIGHT" << endl;
                if (shipPtr->getEarthWeight() > MAX_EARTH_WEIGHT) {
                    cout << "\nNOTE: You cannot ship more than 10 Earth tons (20,000 Earth lbs = " << (MAX_EARTH_WEIGHT) * planetList[identifier1].gravity
                    << " " << shipPtr->getPlanetOne() << " lbs" << ")\n\n";
                }
            }
            while (shipPtr->getEarthWeight() > MAX_EARTH_WEIGHT);    //While the weight is above 10 tons, keep asking for it

            //Shuttle Speed
            int shuttleSpeed;
            cout << "How fast should the shuttle go? (In MPH)" << endl;
            enterAmount(shuttleSpeed, MIN_SPEED, MAX_SPEED);
            shipPtr->setSpeed(shuttleSpeed);

            //Leftover Information
            shipPtr->setTravelDistance(planetList, identifier1, identifier2);   //Because it requires
            shipPtr->setHours();

            cout << "\nYou are shipping " << shipPtr->getCargoType() << " from " << shipPtr->getPlanetOne() << " to " << shipPtr->getPlanetTwo() << endl;
            cout << "The shipment has a weight of " << shipPtr->getPlanetOneWeight() << " lbs (or " << shipPtr->getEarthWeight()
            << " earth lbs) and a speed of " << shipPtr->getSpeed() << " mph\n";

            cout << "You must travel " << shipPtr->getTravelDistance() << " million miles and it will take you approximately " << shipPtr->getHours()
            << " hour(s), " << shipPtr->getDays() << " day(s), and " << shipPtr->getYears() << " year(s)\n\n";

            time_t t = time(0);   //Get the current time
            char* dt = ctime(&t);

            //Print the results to the output file
            fout << "Shipping information entered on " << dt;
            fout << "------------------------------------------------------\n";
            fout << "Cargo: " << shipPtr->getCargoType() << endl;
            fout << fixed << setprecision(2);
            fout << "Earth weight: " << shipPtr->getEarthWeight() << " lbs.\n";
            fout << "Weight on " << shipPtr->getPlanetOne() << " (pick-up): " << shipPtr->getPlanetOneWeight() << " lbs.\n";
            fout << "Weight on " << shipPtr->getPlanetTwo() << " (drop-off): " << shipPtr->getPlanetTwoWeight() << " lbs.\n";
            fout << "Distance traveled: " << shipPtr->getTravelDistance() << " million miles\n";
            fout << "Time in transit: " << shipPtr->getYears() << " year(s), " << shipPtr->getDays() << " day(s), and " << shipPtr->getHours() << " hour(s)"
                << "(at a speed of " << shipPtr->getSpeed() << " mph)\n\n";

            cout << "Your shipping information has been written to the logs!\n\n";

            delete shipPtr;

            cout << "\nWould you like to enter another shipment? (Y/N)\n";
        }
        while (userContinue());

        cout << "Thank you for using the program!" << endl;
        fout.close();

    }
    catch (...) {
        cout << "There was an error running the program" << endl;
        return -1;
    }
    return 0;
}

void readInput (fstream &fileInput, Planet *array, int iteration) {
        long long int number1;  //This is a long long in case we turn it from x million miles into just miles
        double number2;
        fileInput >> number1;
        //Validate the distance in the input file
        if (fileInput.fail() || number1 < 0) {
            cout << "Something is wrong with the distance for planet " << array[iteration].name << endl;
            exit (EXIT_FAILURE);
        }
        else {
            array[iteration].distance = number1;
        }
        fileInput >> number2;
        //Validate the gravity in the input file
        if (fileInput.fail() || number2 < 0) {
            cout << "Something is wrong with the gravity for planet " << array[iteration].name << endl;
            exit (EXIT_FAILURE);
        }
        else {
            array[iteration].gravity = number2;
        }
}

bool userContinue() {
    char inputAgain;
    cin >> inputAgain;
    while (cin.fail() || (toupper(inputAgain) != 'Y' && toupper(inputAgain) != 'N')) {
        cout << "Invalid input. Please try again! (Y/N)?" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> inputAgain;
    }
    if (inputAgain == 'Y' || inputAgain =='y') {
        return true;
    }
    else {
        return false;
    }
}

int enterAmount(int &amount, const int min, const int max) {
    cin.clear();
    cin >> amount;
    while (cin.fail() || amount < min || amount > max) {
        cout << "You must enter a number between " << min << " and " << max << " " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> amount;
    }
    return amount;
}

void enterCargo(string &stringInput) {
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, stringInput);
    while (cin.fail()) {
        cout << "You must enter a string" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        getline(cin, stringInput);
    }
}

void enterPlanet(string &input, const Planet *p, int &num) {
    cout
        << "1. Mercury\n"
        << "2. Venus\n"
        << "3. Earth\n"
        << "4. Mars\n"
        << "5. Jupiter\n"
        << "6. Saturn\n"
        << "7. Uranus\n"
        << "8. Neptune\n";
    int choice;
    enterAmount(choice, MIN_PLANET, NUM_PLANETS);
    switch (choice) {
    case 1:
        num = 0;
        input = p->name;
        break;
    case 2:
        num = 1;
        input = (p+1)->name;
        break;
    case 3:
        num = 2;
        input = (p+2)->name;
        break;
    case 4:
        num = 3;
        input = (p+3)->name;
        break;
    case 5:
        num = 4;
        input = (p+4)->name;
        break;
    case 6:
        num = 5;
        input = (p+5)->name;
        break;
    case 7:
        num = 6;
        input = (p+6)->name;
        break;
    case 8:
        num = 7;
        input = (p+7)->name;
        break;
    }
}
