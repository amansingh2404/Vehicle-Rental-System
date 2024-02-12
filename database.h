#ifndef database_h
#define database_h

/*  Include custom headers*/

#include "vehicle.h"
#include "user.h"
#include "trip.h"
#include "table.cpp"
#include "error.cpp"

using namespace std;

/*
 This is a Database class and axts as a middleware, so we can hide low-level details like file handling
 add, update records, etc.

*/
class Database
{
private:
    // Database have multiple tables

    // Vehicle table
    Table<Vehicle> *vehicleTable;

    // User table
    Table<User> *userTable;

    // Trip Table
    Table<Trip> *tripTable;

    /*
     fetch all the data from the files
     Can throw 'IOErrors' and 'memoryError'
    */
    void fetchAllVehicles() throw(IOError, MemoryError);
    void fetchAllUsers() throw(IOError, MemoryError);
    void fetchAllTrip() throw(IOError, MemoryError);

    void cleanUp();

public:
    /*
     Constructure can throw 'MemoryError' of 'IOError'
     If the system is out of memory or I/O Operations cannot be performed then this error will be thrown
    */

    Database() throw(MemoryError, IOError);
    ~Database();

    // Get reference to the database tables
    //  All are constant pointer to constant objects. So, user can neither change pointer nor the data
    const Table<Vehicle> *const getVehichleRef() const;
    const Table<User> *const getUserRef() const;
    const Table<Trip> *const getTripRef() const;

    // Query vehicle by 'registrationNo'

    const Vehicle *const getVehichle(string regisrtationNo) const throw(NoSuchRecordError);

    // Query User by contant Number
    const User *const getUser(string constactNo) const throw(NoSuchRecordError);

    // Find the vehicle of given type which is available in a given duration
    const vector<const Vehicle *> getVehichle(Date startDate, Date endDate, VehicleType type) const;

    // Add new record of type T in database

    template <class T>
    void addNewRecord(T *record) throw(IOError, MemoryError);

    // update Record In database
    template <class T>
    void updateRecord(T *record) throw(IOError, NoSuchRecordError);
};

#endif