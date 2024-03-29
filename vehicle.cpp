// Include custom headers
#include "vehicle.h"
#include "string_helper.h"
const char DELIMITER = ';';

Vehicle::Vehicle(string registrationNumber, VehicleType type, int seats, string companyName, double pricePerKm,
                 Date PUCEpirationDate, long recordId) : storable(recordId)
{
    this->registrationNumber = registrationNumber;
    this->type = type;
    this->seats = seats;
    this->companyName = companyName;
    this->pricePerKm = pricePerKm;
    this->PUCEpirationDate = PUCEpirationDate;
}
string Vehicle::getRegistrationNumber() const
{
    return this->registrationNumber;
}

VehicleType Vehicle::getVehicleType() const
{
    return this->type;
}
int Vehicle::getSeats() const
{
    return this->seats;
}
string Vehicle::getCompanyName() const
{
    return this->companyName;
}
double Vehicle::getPricePerKm() const
{
    return this->pricePerKm;
}
Date Vehicle::getPUCEpirationDate() const
{
    return this->PUCEpirationDate;
}
void Vehicle::setPricePerKm(double newPrice)
{
    this->pricePerKm = newPrice;
}
string Vehicle ::getVehicleTypeName() const
{
    switch (this->type)
    {
    case VehicleType::bike:
        return "Bike";
    case VehicleType::car:
        return "Car";
    case VehicleType::towera:
        return "Towera";
    default:
        return "Unknown";
    }
}
void Vehicle::display() const
{
    cout << "vehicle Details: " << endl;
    cout << "Registration Number: " << this->registrationNumber << endl;
    cout << "Vehicle Type: " << this->getVehicleTypeName() << endl;
    cout << "Number of seats: " << this->seats << endl;
    cout << "Company Name: " << this->companyName << endl;
    cout << "Price per KM: " << this->pricePerKm << endl;
    cout << "PUC Expiration Date: " << this->PUCEpirationDate.toString() << endl;
}
string Vehicle ::toString() const
{
    stringstream ss;
    ss << recordId << DELIMITER
       << registrationNumber << DELIMITER
       << type << DELIMITER
       << seats << DELIMITER
       << companyName << DELIMITER
       << to_string(pricePerKm) << DELIMITER
       << PUCEpirationDate.toString();

    return ss.str();
}
void Vehicle ::setDataFrom(storable *s)
{
    /* The line `Vehicle * v = dynamic_cast<Vehicle*> (s);` is performing a dynamic cast of the pointer
    `s` to a `Vehicle` pointer. */
    Vehicle *v = dynamic_cast<Vehicle *>(s);
    if (v)
    {
        this->registrationNumber = v->registrationNumber;
        this->type = v->type;
        this->seats = v->seats;
        this->companyName = v->companyName;
        this->pricePerKm = v->pricePerKm;
        this->PUCEpirationDate = v->PUCEpirationDate;
    }
}
