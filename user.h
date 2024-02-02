#ifndef users_h
#define users_h

// Include custom headers
#include "storable.cpp"

// standards headers

#include <string>
using namespace std;

// User class which helps in managing user-related data

class User : public storable
{
private:
    // name of the user
    string name;
    // mobile number of the user
    string contact;
    // email of the user
    string email;

public:
    /**
     * @brief constructure
     * input - name,contact,email
     * input - recordId (default to 0)
     *
     *
     */

    User(string name, string contact, string email, long recordId = 0);

    /**
     * @brief Const attribute
     * Getter methods with const attribute i.e. this is not changing anything of the current
     * object.
     * if this method is not marked as constant, then it cannot be called from a constant object
     * of this class
     *
     *
     */

    string getName() const;
    string getContact() const;
    string getEmail() const;

    /**
     * @brief set name of the user
     * input: New name of the user
     *
     */

    void setName(string newName);
    /**
     * @brief Set contact number of the user
     * Input: New contact number
     *
     */
    void setContact(string newContact);
    /**
     * @brief Set email of the user
     * Input: New email of the user
     *
     */
    void setEmail(string newEmail);

    // Display records on screen
    void display() const;

    // overridden veritual method
    string toString() const;
    void setDataFrom(storable *s);
};

#endif