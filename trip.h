#ifndef trip_h
#define trip_h

// Include coustom headers
#include "date.h"
#include "storable.cpp"
#include "user.h"
#include "vehicle.h"

// Standard CPP header
#include <string>
using namespace std;

// Trip class which helps in managing trip-related data

class Trip : public storable
{
private:
    /**
     * Const pointer to contant vehicle in memory
     * We will create vehicle in memory and assighn address of that vehicle to 'vehicle' pointer
     * this is a contant pointer so that it cannot point to other vehicle objects
     *
     */

    const Vehicle *vehicle;

    /**
     * Const pointer to contant user in memory
     * We will create user in memory and assighn address of that user to 'user' pointer
     * This is a constant pointer so that it connot point to other user objects
     *
     */
    const User *user;
    /**
     * We need to keep track record of start and end date of the trip so that at the
     * time of booking a trip we can find vehicle that are free in that specific duration.
     */
    Date startDate;

    Date endDate;

    // We also keep track of reading of Odometer so that fare can be calculated
    long startReading;
    long endReading;

    // fare of the trip
    double fare;

    // Trip is completed or not
    bool completed;

public:
    /**
     * @brief Contructor
     * input: Pointer to vehicle,
     * input: pointer to user,
     * input start date of the trip,
     * input: end date of the trip,
     * input: Record id (default to 0),
     * input: PUC Expiration Date
     */
    Trip(const Vehicle *vehicle, const User *user, Date startDate, Date endDate,
         long recordId = 0, long startReading = 0, long endReading = 0, double fare = 0.0,
         bool isCompleted = false);

    // Getter methods

    const User &getUser() const;
    const Vehicle &getVehicle() const;
    Date getStartDate() const;
    Date getEndDate() const;
    long getStartReading() const;
    long getEndReading() const;
    double getFare() const;
    bool isCompleted() const;

    // Start trip
    //  input: start reading of the vehicle's odometer
    void startTrip(long startReading);
    /*
    Complete trip
    input: End reading of vehicle's odometer
    output: Claculate the return fare of trip
    */
    double completeTrip(long endReading);

    // display record on screen
    void display() const;

    // Overridden virtual methods
    string toString() const;

    void setDataFrom(storable *s);
};

#endif