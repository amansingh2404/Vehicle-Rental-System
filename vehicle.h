#ifndef vehicle_h
#define vehicle_h

#include "date.h"
#include "storable.cpp"
#include <string>

using namespace std;
// Support for different type of vehicle for different purpose
typedef enum
{
    bike = 1,
    car = 2,
    towera = 3
} VehicleType;

// Vehicle class will help to manage vahicle realted data
class Vehicle : public storable
{
private:
    // Registration number given by RTO.
    string registrationNumber;
    // Type of the vehicle given by "VehicleType" enum
    VehicleType type;
    // Number of seats this vehicle has
    int seats;
    // Name of vehicle manufacturer
    string companyName;

    // Each vehicle has different price per KM
    // This will be required to calculate fare when trip ends
    double pricePerKm;
    // this is the date when PUC will expire
    Date PUCEpirationDate;

public:
    /**
     * @brief Constructor for vehicle
     * Input: Registration number for vehicle
     * Input: vehicle type
     * Input: number of seats
     * Input: company name
     * Input: price per KM
     * Input: PUC expiration date
     * Input: recordId(defaults to 0)
     *
     */
    Vehicle(string registrationNumber, VehicleType type, int seats,
            string companyName, double pricePerKm, Date PUCEpirationDate,
            long recordId = 0);

    /**
     * @brief Getter method with const attribute i.e. this method is not changing
     * data of the current object.
     * If this method is not marked as constant, then it cannot be called from constant object
     * of this class.
     * Following code snippet will show error if 'getRegistrationNumber' is not marked with cost keyword
     * const Vehicle* object = new Vehicle(...);
     * auto registrationNo = object->getRegistrationNumber();
     *
     */
    string getRegistrationNumber() const;
    VehicleType getVehicleType() const;
    string getVehicleTypeName() const;
    int getSeats() const;
    string getCompanyName() const;
    double getPricePerKm() const;
    Date getPUCEpirationDate() const;

    /**
     * @brief Function which sets new price of the vehicle
     * input: New price of the vehicle
     *
     */
    void setPricePerKm(double newPrice);
    // display record on screen
    void display() const;
    // overridden virtual method
    string toString() const;
    void setDataFrom(storable *s);
};

#endif