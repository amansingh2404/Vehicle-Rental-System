/* Include custom headers */

#include "application.h"
#include "database_templates.cpp"

// Using standard CPP headers
#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits>

using namespace std;

Application ::Application()
{
    try
    {
        this->db = new Database();
    }
    catch (Error e)
    {
        cout << e.getMessage();
        exit(EXIT_FAILURE);
    }
}

void Application ::gotoXY(int x, int y) const
{
    printf("%c[%d;%df", 0x1B, y, x);
}

void Application ::renderMenu()
{

    unsigned char choice = 1;
    while (true)
    {
        system("clear");

        gotoXY(25, 4);
        cout << "Select any option from below";
        gotoXY(25, 5);
        cout << "1. Add New Vehicle";
        gotoXY(25, 6);
        cout << "2. View vehicle details";
        gotoXY(25, 7);
        cout << "3. Edit vehicle details";
        gotoXY(25, 8);
        cout << "4. Add new user";
        gotoXY(25, 9);
        cout << "5. Add new trip";
        gotoXY(25, 10);
        cout << "6. View Trip";
        gotoXY(25, 11);
        cout << "7. Start trip";
        gotoXY(25, 12);
        cout << "8. Complete trip";
        gotoXY(25, 13);
        cout << "9. Exit";

        gotoXY(30, 15);
        cout << "Enter your choice: ";

        gotoXY(50, 15);
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {

        case '1':
            this->renderAddNewVehicleMenu();
            break;

        case '2':
            this->renderViewVehicleMenu();
            break;

        case '3':
            this->renderEditvehicleMenu();
            break;

        case '4':
            this->renderAddNewUserMenu();
            break;

        case '5':
            this->renderAddNewTripMenu();
            break;

        case '6':
            this->renderViewTripMenu();
            break;

        case '7':
            this->renderstartTripMenu();
            break;

        case '8':
            this->renderCompleteTripMenu();
            break;

        case '9':
            this->cleanMemory();
            system("clear");
            exit(EXIT_SUCCESS);
            break;

        default:
            this->cleanMemory();
            system("clear");
            exit(EXIT_SUCCESS);
            break;
        }
    }
}
