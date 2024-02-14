#ifndef database_cpp
#define database_cpp

// Include custom headers

#include "database.h"
#include "string_helper.h"

// Includind standard cpp headers
#include <iostream>
using namespace std;

const char DELEMETER = ';';

Database ::Database() throw(IOError, MemoryError)
{
    try
    {
        this->vehicleTable = new Table<Vehicle>("vehicles.txt");
        this->userTable = new Table<User>("users.txt");
        this->tripTable = new Table<Trip>(" Trips.txt ");

        // Fetch data for vehicles
        this->fetchAllVehicles();

        // Fetch data for users
        this->fetchAllUsers();

        // Fetch data for trips
        this->fetchAllTrip();
    }
    catch (...)
    {
        throw;
    }
}

void Database::fetchAllVehicles() throw(IOError, MemoryError)
{

    // Opening file for reading

    this->vehicleTable->fileStream.open(this->vehicleTable->fileName);

    if (!this->vehicleTable->fileStream)
    {
        throw IOError();
    }
    // Read all line from file

    for (string line; getline(this->vehicleTable->fileStream, line);)
    {
        // Split string with given delemeter
        vector<string> components = split(line, DELEMETER);

        // Get all the componets from the vector

        auto recordId = stoi(components[0]);
        auto registrationNumber = components[1];
        auto type = VehicleType(stoi(components[2]));
        auto seats = stoi(components[3]);
        auto companyName = components[4];
        auto pricePerKm = stod(components[5]);
        auto PUCExpirationDate = Date(components[6]);

        // Create record and store
        storable *record = new Vehicle(registrationNumber, type, seats, companyName, pricePerKm, PUCExpirationDate, recordId);
        if (!record)
        {
            throw MemoryError();
        }

        this->vehicleTable->records->push_back(record);
    }
    // close file
    this->vehicleTable->fileStream.close();
}

void Database ::fetchAllUsers() throw(IOError, MemoryError)
{
    // Open file for reading
    this->userTable->fileStream.open(this->userTable->fileName);

    if (!this->userTable->fileStream)
    {
        throw IOError();
    }
    // Read all the lines from the Usertable
    for (string line; getline(this->userTable->fileStream, line);)
    {
        // split string with given delimeter
        vector<string> components = split(line, DELEMETER);

        // Get all the components from the vector
        auto recordId = stoi(components[0]);
        auto name = components[1];
        auto contact = components[2];
        auto email = components[3];

        // Create record and store
        storable *record = new User(name, contact, email, recordId);

        if (!record)
        {
            throw MemoryError();
        }
        this->userTable->records->push_back(record);
    }
    // close the file
    this->userTable->fileStream.close();
}
void Database ::fetchAllTrip() throw(IOError, MemoryError)
{
    // Opening the file for reading
    this->tripTable->fileStream.open(this->tripTable->fileName);
    if (!this->tripTable->fileStream)
    {
        throw IOError();
    }
    // Read all the lines from the file
    for (string line; getline(this->tripTable->fileStream, line);)
    {
        // Split string with given delimeter
        vector<string> components = split(line, DELEMETER);
        // get all components from vector

        try
        {
            auto recordId = stoi(components[0]);
            auto vehiclePtr = this->vehicleTable->getReferenceOfRecordForId(stoi(components[1]));
            auto userPtr = this->userTable->getReferenceOfRecordForId(stoi(components[2]));
            auto startDate = Date(components[3]);
            auto endDate = Date(components[4]);
            auto startReading = stoi(components[5]);
            auto endReading = stoi(components[6]);
            auto fare = stod(components[7]);
            auto isCompleted = components[8] == "0" ? false : true;

            // Create record and store
            storable *record = new Trip(vehiclePtr, userPtr, startDate, endDate, recordId,
                                        startReading, endReading, fare, isCompleted);

            if (!record)
            {
                throw MemoryError();
            }
            this->tripTable->records->push_back(record);
        }
        catch (...)
        {
            // ignore
        }
    }
    this->tripTable->fileStream.close();
}

const Vehicle *const Database ::getVehichle(string registrationNo) const throw(NoSuchRecordError)
{
    for (auto &record : *this->vehicleTable->records)
    {
        Vehicle *vehicle = dynamic_cast<Vehicle *>(record);
        if (vehicle)
        {
            if (vehicle->getRegistrationNumber() == registrationNo)
            {
                return vehicle;
            }
        }
    }
    throw NoSuchRecordError();
}

const User *const Database ::getUser(string contactNo) const throw(NoSuchRecordError)
{
    for (auto &record : *this->userTable->records)
    {
        User *user = dynamic_cast<User *>(record);
        if (user)
        {
            if (user->getContact() == contactNo)
            {
                return user;
            }
        }
    }
    throw NoSuchRecordError();
}

const vector<const Vehicle *> Database ::getVehichle(Date startDate, Date endDate, VehicleType type) const
{
    vector<const Vehicle *> vehicles = vector<const Vehicle *>();

    for (auto &vrecord : *this->vehicleTable->records)
    {
        Vehicle *vehicle = dynamic_cast<Vehicle *>(vrecord);
        if (vehicle && vehicle->getVehicleType() == type)
        {
            // Check if vehicle is free from startDate to endDate
            bool tripFound = false;
            for (auto &trecord : *this->tripTable->records)
            {
                Trip *trip = dynamic_cast<Trip *>(trecord);

                if (trip && !trip->isCompleted() && trip->getVehicle().getRecordId() == vehicle->getRecordId() &&
                    !(trip->getStartDate() >= endDate && trip->getEndDate() >= endDate) &&
                    !(trip->getStartDate() <= startDate && trip->getEndDate() <= startDate)

                )
                {
                    tripFound = true;
                    break;
                }
            }
            if (!tripFound)
            {
                vehicles.push_back(vehicle);
            }
        }
    }
    return vehicles;
}

void Database ::cleanUp()
{
    delete this->vehicleTable;
    delete this->userTable;
    delete this->tripTable;
}

Database::~Database()
{
    this->cleanUp();
}
const Table<Vehicle> *const Database ::getVehichleRef() const
{
    return this->vehicleTable;
}
const Table<User> *const Database ::getUserRef() const
{
    return this->userTable;
}
const Table<Trip> *const Database ::getTripRef() const
{
    return this->tripTable;
}
#endif
