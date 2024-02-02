#ifndef date_h
#define date_h
// Include custom headers
#include "storable.cpp"

// Include standard cpp headers
#include <ctime>
#include <string>
using namespace std;

typedef struct Date : Serializable
{
private:
    // Structure holding date & time info
    struct tm date;
    bool empty;

public:
    // Constructor, create date from string
    Date(string sate);
    // Create date from current time
    Date();
    // Add given number of days in this date
    Date operator+(int days);

    // If this date is greater than given date
    bool operator>(Date date) const;

    // If this date is greater than or equal to given date
    bool operator>=(Date date) const;

    // if this date is less then given date
    bool operator<(Date date) const;

    // If this date is less then or equal to given date
    bool operator<=(Date date) const;

    bool isEmpty() const;
    string toString() const;

} Date;

#endif