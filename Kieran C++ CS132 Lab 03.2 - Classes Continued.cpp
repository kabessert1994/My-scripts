// This program is used to manage an inventory of vehicles from a file on the local drive.
// Coded by Kieran Bessert	4/26/2020
// Last edited 5/11/2020

#include <iostream>
#include <fstream>                              // File I/O
#include <string>                               // use of Strings
#include <cstdlib>                              // use of exit() function
#include <iomanip>                              // use of setprecision()
using namespace std;

/***********************CLASS***********************/
class Vehicle
{
public:
    bool rdVehicle(istream&);
    void wrtVehicle(ostream&);

    string getVin();                            // Vin Accessor Function
    void updateVin(string);                     // Vin Mutator Function
    double getPrice();                          // Price Accessor Function
    void updatePrice(double);                   // Price Mutator Function
    int getWeeksOnLot();                        // WeeksOnLot Accessor Function
    void updateWeeksOnLot(int);                 // WeeksOnLot Mutator Function

    Vehicle();                                  // Default Constructor
    Vehicle(string newVin);                     // Single Argument Constructor
    Vehicle(string newVin, double newPrice);    // Double Argument Constructor

    friend bool compareModel(Vehicle& car1, Vehicle& car2);// Friend function compare base model
    friend bool operator ==(Vehicle& car1, Vehicle& car2);// Friend function compare base model
    friend void operator ++(Vehicle& car1);     // Friend function increment WEEKS ON LOT
private:
    void getBaseModel(string&);                 // Internal Private Helper Function
    string baseModel;                           // The first 3 characters of the VIN

    string vin;                                 // The vehicle ID number
    double price;                               // The current asking price for the vehicle
    int weeksOnLot;                             // How many weeks the vehicle has been inventoried
};

/***********************CONSTANT VARIABLES***********************/
const string IN_FILE_NAME = "vehicles.txt";     // Constant variable for storing name of the input file
const int MAX_SIZE_INV = 20;                    // The size of array OF objects
const int MAX_SIZE_VIN = 9;                     // the size of array WITHIN each object

/***********************NON-MEMBER FUNCTIONS***********************/
void viewInv1(Vehicle v[], int max);
// This function reads input data from an array and displays it on screen
// PRECONTDITION: An array of objects of type Vehicle
// POSTCONDITION: cout statement of the VIN, PRICE, & WEEKS ON LOT data contained in each object
void addToInv2(Vehicle v[], int& count);
// This function edits the last empty object in an array to fill its data
// PRECONTDITION: An empty object in the array, and New VIN, PRICE, WEEKS ON LOT data required for inputing by user
// POSTCONDITION: An object in the array containing this information, and the array count incremented
void updateInv3(Vehicle v[], int max);
// This function increments all filled array's WEEKS ON LOT
// PRECONTDITION: An array of objects with VIN data
// POSTCONDITION: All filled arrays with their WEEKS ON LOT incremented by 1
void searchInv4(Vehicle v1[], string& searchForVIN);
// This function searches the filled array for a VIN value entered by the user
// PRECONTDITION: A filled array of VIN data and the first 3 values of VIN data a user wishes to search for
// POSTCONDITION: If match is found in the array, that objects data printed to screen
void makeUC(string&);          
// This function accepts a call by refrence string and uppercases the string for the length of a string
// PRECONDITION: Any string with lowercase letters
// POSTCONDITION: The string is capitalized

/***********************MAIN***********************/
int main()
{
    ifstream in_stream;                         // Declare the input file
    ofstream out_stream;                        // Declare the output file
    Vehicle vehicles[MAX_SIZE_INV];             // Declare object array
    string vinSearch;                           // Variable for storing VIN of desired vehicle
    int arrayCount(0);                          // For keeping track of the used arrays
    int menuChoice(0);                          // For user interaction

    in_stream.open(IN_FILE_NAME);               // Open input file
    if (in_stream.fail())                       // Check to see if open function fails
    {
        cout << "Input file opening failed.\nFile does not exist.\n";
        return(-1);
    }

    for (int ix = 0; ix < MAX_SIZE_INV; ix++)   // Fill the object arrays completely
    {
        vehicles[ix].rdVehicle(in_stream);
        if (vehicles[ix].getVin() == "?")       // Do not count empty arrays
        {
            break;
        }
        arrayCount++;                           // Count all filled objects in the array
    }

    cout << "WELCOME TO THE VEHICLE INVENTORY DATA PROGRAM!!!\n";

    do{                                         // Main loop of program
        cout << "\nMenu:\n 1) View Inventory\n 2) New Entry\n 3) Update Entry\n 4) Search Inventory\n 0) Exit program\n\n\tChoice: ";
        cin >> menuChoice;
        cout << endl << endl;
        switch (menuChoice)
        {
        case 1:                                 // View contents of input file
            viewInv1(vehicles, MAX_SIZE_INV);
            break;
        case 2:                                 // Add entry to input file
            addToInv2(vehicles, arrayCount);
            break;
        case 3:                                 // Edit Entry of input file
            updateInv3(vehicles, MAX_SIZE_INV);
            cout << "\nWEEKS ON LOT has been updated for each vehicle in inventory;\n\n";
            break;
        case 4:                                 // Search input file
            cout << "Enter the first 3 characters of the VIN you wish to search for.\n";
            cout << "[EXAMPLE: ' RGL ']\n\n\tVIN: ";
            cin >> vinSearch;
            cout << endl;
            makeUC(vinSearch);
            searchInv4(vehicles, vinSearch);
            break;
        case 0:
            cout << "THANK YOU FOR USING THE VEHICLE INVENTORY DATA PROGRAM!!!\n\nGOODBYE!\n\n";
            in_stream.close();
            out_stream.open(IN_FILE_NAME);      // Open the output file appending
            if (out_stream.fail())              // Checks to see if open function fails
            {
                cout << "Output file opening failed.\n";
                in_stream.close();
                return(-1);
            }
            for (int ix = 0; ix < MAX_SIZE_INV; ix++)// Fill the object arrays
            {
                vehicles[ix].wrtVehicle(out_stream);
            }
            out_stream.close();
            return (0);
        default:
            cout << "Illegal choice.\n";
        }
    } while (true);
    return(0);
}

/***********************MEMBER FUNCTIONS***********************/
bool Vehicle::rdVehicle(istream& rdS)           // Reads data from the stream
{
    if (rdS >> vin)                             // Checks for more entries
    {
        getBaseModel(vin);
        rdS >> price >> weeksOnLot;             // Fills the other 2 values from stream
        return (true);                          // Returns true if reads in another set
    }
    return (false);                             // No other entries exist, Return FALSE
}
void Vehicle::wrtVehicle(ostream& wrtS)         // Writes data to a stream
{
    wrtS << vin << "\t" << price << "\t" << weeksOnLot << "\n";
}
string Vehicle::getVin()                        // Accessor Function
{
    return(vin);
}
void Vehicle::updateVin(string newVin)          // Mutator Function
{
    vin = newVin;
    getBaseModel(newVin);
}
double Vehicle::getPrice()                      // Accessor Function
{
    return(price);
}
void Vehicle::updatePrice(double newPrice)      // Mutator Function
{
    price = newPrice;
}
int Vehicle::getWeeksOnLot()                    // Accessor Function
{
    return(weeksOnLot);
}
void Vehicle::updateWeeksOnLot(int newWeeks)    // Mutator Function
{
    weeksOnLot = newWeeks;
}
/***********************CONSTRUCTORS***********************/
Vehicle::Vehicle()                              // Default Constructor
{
    vin = "?";
    baseModel = "?";
    price = -1.00;
    weeksOnLot = 0;
}
Vehicle::Vehicle(string newVin)                 // Single Argument Constructor
{
    vin = newVin;
    getBaseModel(newVin);
    price = -1.00;
    weeksOnLot = 0;
}
Vehicle::Vehicle(string newVin, double newPrice)// Double Argument Constructor
{
    vin = newVin;
    getBaseModel(newVin);
    price = newPrice;
    weeksOnLot = 0;
}
/***********************FRIEND FUNCTIONS***********************/
bool compareModel(Vehicle& car1, Vehicle& car2) // Friend function compare base model 1
{
    return(car1.baseModel == car2.baseModel);
}
bool operator ==(Vehicle& car1, Vehicle& car2)  // Friend function compare base model 2
{
    return(car1.baseModel == car2.baseModel);
}
void operator ++(Vehicle& car1)                 // Friend function increment WEEKS ON LOT
{
    car1.weeksOnLot += 1;
}
/***********************PRIVATE HELPER FUNCTIONS***********************/
void Vehicle::getBaseModel(string& vin)
{
    baseModel = vin.substr(0, 3);
}

/***********************NON-MEMBER FUNCTIONS***********************/

void viewInv1(Vehicle v[], int max)             // The 1) View Inventory menu choice
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    for (int ix = 0; ix < max; ix++)
    {
        if (v[ix].getVin() == "?")              // Check for empty objects in the array
        {
            return;
        }
        v[ix].wrtVehicle(cout);
    }
}

void addToInv2(Vehicle v[], int& count)         // The 2) New Entry menu choice
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    string vin;
    double price;
    int choice(0);
    if (count >= MAX_SIZE_INV)                  // Check to see if array is full.
    {
        cout << "Inventory is full.\n";
        return;
    }

    cout << "9 Digit VIN of the vehicle: ";     // Prompt for new entry data
    cin >> vin;
    makeUC(vin);                                // Ensure data entered matches inventpory
    if (vin.length() != MAX_SIZE_VIN)           // Error checking
    {
        cout << "Invalid VIN entered.\n";
        return;
    }

    cout << "Do you know the price of the vehicle?\n1) YES\n0) NO\n\n\tChoice: ";
    cin >> choice;
    if (choice == 0)
    {
        v[count].updateVin(vin);
        v[count].wrtVehicle(cout);
        count++;
    }
    else if(choice == 1)
    {
        cout << "\nEnter the PRICE of the vehicle without punctuation: ";
        cin >> price;
        cout << endl;
        v[count].updateVin(vin);
        v[count].updatePrice(price);
        v[count].wrtVehicle(cout);
        count++;
    }
    else
    {
        cout << "Invalid Choice: ";
        return;
    }
}

void updateInv3(Vehicle v[], int max)           // The 3) Update Entry menu choice.
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    for (int ix = 0; ix < max; ix++)
    {
        if (v[ix].getVin() == "?")              // Check for empty objects in the array
        {
            return;
        }
        ++v[ix];
        v[ix].wrtVehicle(cout);
    }
}

void searchInv4(Vehicle v1[], string& searchForVIN)// The 4) Search Inventory menu choice.
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    Vehicle searchVehicle(searchForVIN);

    for (int ix = 0; ix < MAX_SIZE_INV; ix++)
    {
        if (v1[ix].getVin() == "?")             // Check for empty objects in the array
        {
            return;
        }
        if (compareModel(v1[ix], searchVehicle))
        {
            v1[ix].wrtVehicle(cout);
        }
        //if (v1[ix].getVin().substr(0, 3)==searchForVIN)
        //{
        //    v1[ix].wrtVehicle(cout);
        //}
    }
}

void makeUC(string& vin)                        // Uppercases the first 3 letters of string input
{
    int count = (int)vin.length();

    for (; count-- > 0;)
    {
        vin[count] = toupper(vin[count]);
    }
}

/* EXAMPLE ' vehicles.txt ' FILE */
/*
RGLK27844	14800	8
RLVY26499	17450	10
RLTS43992	18456.9	13
RGMA74881	23050	6
TLTD37882	29544.5	11
RLTX26888	0	4
RGMC33389	15000	3
RGLL44488	23999	2
*/
