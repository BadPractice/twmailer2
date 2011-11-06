#include "badguy.h"
#include <iostream>
#define TIMEOUT 60

badguy::badguy(string arg)
{
    //ctor
    mytime=time(NULL);
    mytime=mytime + TIMEOUT;
    name=arg;
}

time_t badguy::get_time()
{
    return mytime;
}

string badguy::get_name()
{
    return name;
}


badguy::~badguy()
{
    //dtor
}
