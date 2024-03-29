#ifndef table_h
#define table_h

// Include coustom headers
#include "storable.cpp"
#include "error.cpp"

// Standard CPP header
#include <vector>
#include <string>
#include <fstream>

using namespace std;
/*
    This is templated (generic) class. It reperesents in-memory database table.
    Table can be of type 'Vehicle', 'user', 'Trip'.
*/
template <class T>
class Table
{
private:
    // Name of database file
    string fileName;

    // File stream used to read and write data from database file
    fstream fileStream;
    /*
        Original data is stored here
        "vector is a container type and behaves like dynamic array"
    */
    vector<storable *> *records = NULL;

    /*
     This is a private method
     We will share Pointer of record with recordId = 'recordId'
     This is itentional, hence it is kept as private method

    */

    T *getReferenceOfRecordForId(long recordId) const throw(NoSuchRecordError);

    /*
        This is a private function. It is called aftr inserting new record or updating data.
        This funtions writes data to a file.
      */
    void writeTofile() throw(IOError);

    /*
      Add new record to database
      Input: fileName of database.
      This method can throw "MemoryError" of IOError
    */
    const T *const addNewRecord(T data) throw(MemoryError, IOError);

    /*
    Update record in database
    Input:  new record of generic type 'T'.
    This method can throw "IOError"
    */
    void updateRecord(T updatedRecord) throw(IOError, NoSuchRecordError);

public:
    /*
        Constructure
        Input: FileName of database.
    */
    Table(string fileName) throw(MemoryError);
    ~Table();

    // Get recordId for next round
    long getNextRecordId() const;
    /*
    Get record for perticular "recordId"
    input: 'recordId' of the record
    We will return const T * const (Constant pointer to constant record so user cannot modify that record accidently.)
    This method can show "NoSuchRecordError"
    */
    const T *const getRecordForId(long recordId) const throw(NoSuchRecordError);

    /*
      Class database can use this class Private methods and variables.
      We will use 'getReferenceRecordId' to get actual record reference

    */
    friend class Database;
};

#endif