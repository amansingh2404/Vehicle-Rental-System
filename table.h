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
};

#endif