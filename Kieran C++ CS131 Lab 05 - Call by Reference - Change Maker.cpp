// This program accepts a number of cents from the user (positive integer in the range of 0 to 1,000) and 
// outputs the smallest number of coins made up of quarters, dimes, nickels and pennies that equal the value of total cents specified.
//
// Created by Kieran Bessert 2/13/2020
// Last edited 2/13/2020


/*
Pseudocode;
Ask user for how many cents they have and store in variable?
check if this is a valid entry

how many quarters can we return?
how many dimes can we return?
how many nickles can we return?
can we return any pennies?

Tell the user total coins returned
*/

#include <iostream>
using namespace std;

void changeMaker(int input1, int &quarters, int &dimes, int &nickles, int &pennies);
// Calculates the coins to return to the user based on an entered integer between 0 to 1000
// Precondition: The amount of Cents as an integer
// Postcondition: The number of least number of quarters, dimes, nickels and pennies that equal the value of total cents

int main()
{
	int change(1), Quarters(0), Dimes(0), Nickles(0), Pennies(0), coins(0);

    cout << "Welcome to the Change Maker!!!\n"
        << endl
        << "Lets calculate how many coins you get!!\n"
        << endl;


    while (change != 0)
    {
        change = 1;
        cout << "Please enter an integer amount between\n"
            << "1 and 1000\n"
            <<"of the amount of change you have to exchange.\n"
            << endl
            << "NOTE: Enter the integer '0' to exit the program\n"
            << endl;

        cin >> change;

        while (change < 0 || change > 1000)
        {
            cout << "This amount exceeds the range of\n"
                << "1 to 1000\n"
                << "and is not the valid exit character '0'\n"
                << endl;
            break;
        }

        if (change != 0) {

            changeMaker(change, Quarters, Dimes, Nickles, Pennies);
            cout << endl
                << endl
                << "You have entered \n"
                << change
                << endl
                << "cents to convert to coins.\n"
                << endl
                << "This equates to;\n";

            cout << Quarters << " Quarters\n";
            cout << Dimes << " Dimes\n";
            cout << Nickles << " Nickles\n";
            cout << Pennies << " Pennies\n";

            coins = Quarters + Dimes + Nickles + Pennies;

            cout
                << endl
                << "a total of " << coins << " coins.\n"
                << endl;
        }
    }
}

void changeMaker(int input1, int &quarters, int &dimes, int &nickles, int &pennies)
{
    quarters = input1 / 25;
    input1 = input1 - (quarters * 25);

    dimes = input1 / 10;
    input1 = input1 - (dimes * 10);

    nickles = input1 / 5;
    input1 = input1 - (nickles * 5);

    pennies = input1 / 1;
    pennies = input1;

    input1 = 1;
}
