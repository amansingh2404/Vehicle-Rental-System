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

#endif
