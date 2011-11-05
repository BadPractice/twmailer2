#ifndef IPLIST_H
#define IPLIST_H
#include <list>
#include <string>
#include "badguy.h"
using namespace std;
class iplist
{
    public:
        iplist();
        void add(string);//add a Person
        int check(string);//check if Person is blocked
        void debug_msg();//messages used for debugging
        void save();//save list to file
        void read();//import lixst from file 
					//(includeing clearing current)
        void clear();//delete all
        void refresh();//remove old timestamps from list
        virtual ~iplist();
    protected:
    private:
        list<badguy> badguys;
};

#endif // IPLIST_H
