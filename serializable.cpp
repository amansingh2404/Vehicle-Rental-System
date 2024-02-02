// Include standard cpp headers
#include <string>
using namespace std;

/**
 * @brief This is serializable class and it is an abstract class
 * any class derived from this class must implement 'tostring' method
 *  writer- Aman singh
 */
class Serializable
{
public:
    /**
     * @brief Pure virtual function
     * 'serialazable does not know what 'toString' method will do
     * It is responsibelity of the derived class to inplement it's own toString method
     *
     */
    virtual string toString() const = 0;
};