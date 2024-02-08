// Include custom headers
#include "trip.h"
#include "string_helper.h"

// Include standard cpp headers
#include <iostream>

const char DELIMITER = ';';

Trip ::Trip(const Vehicle *vehicle, const User *user, Date startDate, Date endDate,
            long recordId, long startReading, long endReading, double fare, bool isCompleted)
    : storable(recordId)
{
    this->vehicle = vehicle;
    this->user = user;
    this->startDate = startDate;
    this->endDate = endDate;
    this->startReading = startReading;
    this->endReading = endReading;
    this->fare = fare;
    this->completed = isCompleted;
}
const User &Trip ::getUser() const { return *this->user; }
const Vehicle &Trip ::getVehicle() const { return *this->vehicle; }
Date Trip ::getStartDate() const { return this->startDate; }
Date Trip ::getEndDate() const { return this->endDate; }
long Trip ::getStartReading() const { return this->startReading; }
long Trip ::getEndReading() const { return this->endReading; }
double Trip ::getFare() const { return this->fare; }
bool Trip ::isCompleted() const { return this->completed; }

void Trip ::startTrip(long starReading)
{
    this->startReading = starReading;
}
double Trip::completeTrip(long endReading)
{
    if (this->completed)
    {
        return this->fare;
    }
    this->endReading = endReading;
    this->fare = (this->endReading - this->startReading) * this->vehicle->getPricePerKm();
    this->completed = true;
    return this->fare;
}

void Trip ::display() const
{
    cout << " Vehicle Details: " << endl;
    cout << "Registration Number: " << this->vehicle->getRegistrationNumber() << endl;
    cout << "Vehicle Type: " << this->vehicle->getVehicleTypeName() << endl;
    cout << "Company name: " << this->vehicle->getCompanyName() << endl;
    cout << "Price per km: " << this->vehicle->getPricePerKm() << endl;
    cout << endl;

    cout << "User Details: " << endl;
    cout << "Name: " << this->user->getName() << endl;
    cout << "Contact: " << this->user->getContact() << endl;
    cout << endl;

    cout << "Trip details: " << endl;
    cout << "Start Date: " << this->startDate.toString() << endl;
    cout << "End Date: " << this->endDate.toString() << endl;

    string tripStatus = "Not Started";
    if (this->startReading != 0)
    {
        tripStatus = "On going";
        cout << "Start Reading: " << this->startReading << endl;
    }
    if (this->completed)
    {
        tripStatus = "Completed";
        cout << "End Reading: " << this->endReading << endl;
        cout << "Total run: " << this->endReading - this->startReading << endl;
        cout << "Total fare: " << this->fare << endl;
    }
    cout << "Trip status: " << tripStatus << endl;
}

string Trip ::toString() const
{
    stringstream ss;
    ss << recordId << DELIMITER
       << vehicle->getRecordId() << DELIMITER
       << user->getRecordId() << DELIMITER
       << startDate.toString() << DELIMITER
       << endDate.toString() << DELIMITER
       << startReading << DELIMITER
       << endReading << DELIMITER
       << fare << DELIMITER
       << completed;
    return ss.str();
}
/**
 * Set data from a storable object to the current Trip object.
 *
 * @param s pointer to the storable object to set data from
 *
 * @return void
 *
 * @throws None
 */
void Trip::setDataFrom(storable *s)
{
    Trip *trip = dynamic_cast<Trip *>(s);
    if (trip)
    {
        this->vehicle = trip->vehicle;
        this->user = trip->user;
        this->startDate = trip->startDate;
        this->endDate = trip->endDate;
        this->startReading = trip->startReading;
        this->endReading = trip->endReading;
        this->fare = trip->fare;
        this->completed = trip->completed;
    }
}
