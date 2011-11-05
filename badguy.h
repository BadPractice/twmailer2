#ifndef BADGUY_H
#define BADGUY_H
#include  <string>
#include <ctime>
using namespace std;
class badguy
{
public:
    badguy(string);
    time_t get_time();
    string get_name();
    virtual ~badguy();
protected:
private:
    time_t mytime;
    string name;
};

#endif // BADGUY_H
