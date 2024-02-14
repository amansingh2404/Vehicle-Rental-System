#ifndef application_h
#define applilcation_h

// Include custom headers
#include "vehicle.h"
#include "user.h"
#include "trip.h"
#include "database.h"
#include "error.cpp"
#include "string_helper.h"

// Include standard cpp headers
#include <fstream>
extern const char DELEMETER;

class Application
{
private:
    Database *db;
    void renderMenu();
    void welcome();
    void gotoXY(int x, int y) const;

    // Render menus
    void renderAddNewVehicleMenu() const;
    void renderViewVehicleMenu() const;
    void renderEditvehicleMenu() const;
    void renderAddNewUserMenu() const;
    void renderAddNewTripMenu() const;
    void renderViewTripMenu() const;
    void renderstartTripMenu() const;
    void renderCompleteTripMenu() const;
    void showDialog(string message, string id = "") const;

    void cleanMemory();

public:
    Application();
    // Start Application
    void start();
};

#endif