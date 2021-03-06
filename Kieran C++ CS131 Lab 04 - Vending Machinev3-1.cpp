// This program emulates a vending machine that dispenses Ice Cream Bars by;
// - Prompting the user for money
// - Dispensing correct change
// Created by Kieran Bessert 2/4/2020
// Last edited 2/10/2020

#include <iostream>
using namespace std;

const double Ice_Cream(2.75);

void Greeting();
// Greets the user and declares the value of global variable Ice_Cream

double Add_Change();
// A function to prompt the user to insert coins until enough has been inserted to buy the Ice Cream Bar.
// The user is prompted for input.
// Returns the total amount of money inserted.

void Change_Back(double cash);
// A function to calculate the amount of change that should be returned to the user.
// The input is obtained by the prior function's output.

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    double Total(0.0);

    Greeting();
    Total = Add_Change();
    Change_Back(Total);
}

void Greeting()
{
    cout << "Welcome to the Ice Cream Bar Vending Machine!\n" << endl;
    cout << "An Ice Cream Bar costs $" << Ice_Cream << "." << endl;
    cout << endl;
}

double Add_Change()
{
    double total(0.0);
    char coin;

    cout << "Please select a coin you wish to insert.\n"
        << "You may choose;\n"
        << endl
        << "D for a Dollar ($1.00)\n"
        << "q for a Quarter ($0.25)\n"
        << "d for a Dime ($0.10)\n"
        << "n for a Nickle ($0.05)\n"
        << endl;
    while (total < Ice_Cream)
    {
        cin >> coin;
        switch (coin)
        {
        case 'D':
            total = total + 1.00;
            cout << "Your current total is " << total << endl;
            break;
        case 'q':
            total = total + 0.25;
            cout << "Your current total is " << total << endl;
            break;
        case 'd':
            total = total + 0.10;
            cout << "Your current total is " << total << endl;
            break;
        case 'n':
            total = total + 0.05;
            cout << "Your current total is " << total << endl;
            break;
        default:
            cout << "Invalid coin selection." << endl;
            break;
        }
        //Simulates a person putting money into the vending machine by repeatedly prompting the user for the next coin to be inserted.  
        //Outputs the total entered so far after each coin is inserted.
    }
    return total;
}
void Change_Back(double cash)
{
    double change;
    change = cash - Ice_Cream;
    cout << endl
        << "Enjoy your ice cream bar!\n"
        << endl
        << "Your change is $"
        << change
        << ".\n";
    // Outputs to the screen the amount of change that should be returned.
}
