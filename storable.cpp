#ifndef storable_cpp
#define storable_cpp

#include "serializable.cpp"

#include <string>
#include <iostream>
using namespace std;
/**
 * Storable is a class which can be stored in file.
 * Anything which is storable must have 'recordId' (used as unique key)
 * It is derived form the serializable class. Anything which is 'storable' must be 'serializable.
 * (must have toString function)
 *
 */
class storable : public Serializable
{
protected:
    // unique recordId which acts as a primary key to find data
    // This property is protected, so only derived class can access it directly

    long recordId;

public:
    // construcor Input: recordId

    storable(long recordId)
    {
        this->recordId = recordId;
    };
    long getRecordId() const
    {
        return this->recordId;
    };
    /**
     *pure virtual function
     Every subclass of this class must provide a suitable way to set 'this'
     object from 'storable*s
     *This is similar to copy constructor
     */
    virtual void setDataFrom(storable *s) = 0;
    /**
     * @brief Friend class declaration
     * table and database can access private member of this class
     * Table class: It sets 'recordId' of object inside ' addNewRecord
     * method
     * Database class: It sets 'recordId of object inside 'addNewRecord'method
     *
     */
    template <class T>
    friend class Table;
    friend class Database;
};

#endif