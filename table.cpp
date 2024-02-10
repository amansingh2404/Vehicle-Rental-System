// Include custom headers
#include "table.h"

// Standard CPP headers
#include <iostream>
using namespace std;

template <class T>
Table<T>::Table(string fileName) throw(MemoryError)
{
    this->fileName = fileName;

    /*
    Create memory to store all records
    Remember we will store only addresses of records inside this Vector
    Actual record can be accessed by dereferencing data found at specific index of vector

    ** Do not forget to free up memory in destructure **

    */
    this->records = new vector<storable *>();

    if (!this->records)
    {
        throw MemoryError();
    }
}
template <class T>
long Table<T>::getNextRecordId() const
{

    // Next record is total size of record + 1
    return this->records->size + 1;
}
template <class T>
const T *const Table<T>::addNewRecord(T record) throw(MemoryError, IOError)
{

    // We will create new record in memory "newRecord in pointer to the new Record"
    T *newRecord = new T(record);
    if (!newRecord)
    {
        throw new MemoryError();
    }
    newRecord->recordId = this->getNextRecordId();

    /*
       Store address of new record id "record vector"

    */
    this->records->push_back(newRecord);

    // Write data to a file
    try
    {
        this->writeTofile();
    }
    catch (IOError error)
    {
        this->records->pop_back();
        delete newRecord;
    }
    throw;
    // Return newly created record as const so no one can modify it
    return newRecord;
}

template <class T>
void Table<T>::updateRecord(T updateRecord) throw(IOError, NoSuchRecordError)
{
    // first find original record record index

    for (auto &record : *this->records)
    {
        if (record->getRecordId() == updatedRecord.getRecordId())
        {
            /*
                record is a pointer pointinf at some record in heap memory
                we will directly change data to tha address
                Now record is pointing at new updated in memory
                We will keep a backup record so if write fails, we can restore from backup

            */

            T *pointerToRecord = dynamic_cast<T *>(record);
            if (pointerToRecord)
            {
                T oldRecord = T(*pointerToRecord);
                record->setDataFrom(&updatedRecord);
                try
                {
                    this->writeTofile();
                }
                catch (IOError error)
                {
                    // clean up things
                    record->setDataFrom(&oldRecord);

                    // Rethrow exeption
                    throw;
                }
            }
        }
    }
    throw NoSuchRecordError();
}

template <class T>
void Table<T>::writeTofile() throw(IOError)
{
    /*
     In this method, we will overwrite file with all the data that we have
     So Open file with mode 'ios::out | io::trunc'
    */
    this->fileStream.open(fileName, ios::out | ios::trunc);
    if (!this->fileStream)
    {
        throw IOError();
    }
    for (auto &record : records)
    {
        fileStream << record->toString() << endl;
    }
    // close the file
    this->fileStream.close();
}
template <class T>
const T *const Table<T>::getRecordForId(long recordId) const throw(NoSuchRecordError)
{
    try
    {
        return this->getReferenceOfRecordForId(recordId);
    }
    catch (NoSuchRecordError)
    {
        throw;
    }
}
template <class T>
T *Table<T>::getReferenceOfRecordForId(long recordId) const throw(NoSuchRecordError)
{
    for (auto &record : *records)
    {
        if (record->getRecordId() == recordId)
        {
            return dynamic_cast<T *>(record);
        }
    }
    throw NoSuchRecordError();
}

template <class T>
Table<T>::~Table()
{
    // free up memory which is dynamically created
    for (auto &record : *this->records)
    {
        // This is to just delete the record the in-memory data pointed to by record
        delete dynamic_cast<T *>(record);
    }
    /*
      Now 'this->records' contains the address of memory segments that has not data(or corrupted data)
      So clear all the addresses from this->records
    */

    this->records->clear();
    // This will reduce the memory size taken by vector 'this->records'
    this->records->shrink_to_fit();
    // Finally delete the memory pointed to by vector 'this-> records
    delete this->records;
}
