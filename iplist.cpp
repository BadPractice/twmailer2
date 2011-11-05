#include "iplist.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#define TRY_LIMIT 3
iplist::iplist()
{
    //ctor
}

void iplist::read()
{
	clear();
	int pos;
	string line, name;
	time_t mytime;
	    ifstream handle;
    handle.open(".badguys", ios::in);
    while (handle.good())
    {
        getline (handle,line);
            pos=line.find(":",0);
    name=line.substr(0,pos);
    line =line.substr(pos+1);
    mytime=atoi(line.c_str());
    }
}

void iplist::clear()
{
	badguys.clear();
}

void iplist::add(string arg)
{
    badguys.push_back(badguy(arg));
}

void iplist::debug_msg()
{
	list<badguy>::iterator it;
    it=badguys.begin();
    while(it!=badguys.end())
    {
		cout<<"Element name: "<<(*it).get_name()<<endl;
		cout <<"Element time "<<(*it).get_time()<<endl;
		it++;
	}
}

void iplist::refresh()
{
	time_t mytime;
    time(&mytime);
    while(badguys.front().get_time()<mytime && badguys.begin()!=badguys.end())badguys.pop_front();
}
int iplist::check(string arg)
{
	cout<<"badguys empty  "<<badguys.empty()<<endl;
	//if(badguys.empty()==0)return 0;
	string h;
    int count=0;
    time_t mytime;
    time(&mytime);
    list<badguy>::iterator it;
    it=badguys.begin();



    while((*it).get_time()<mytime && it!=badguys.end())
    {
		 it++;
	 }
    while(it!=badguys.end())
    {
        if(!arg.compare((*it).get_name()))
        {
            count++;
            if(count==TRY_LIMIT)
            {
                return 1;
            }
        }

		it++;
    }
        return 0;
}
void clear();

void iplist::save()
{
    ofstream handle;
	list<badguy>::iterator it;  
    handle.open(".badguys",ios::out);
	
    it=badguys.begin();
    while(it!=badguys.end())
    {
		handle<<(*it).get_name()<<":"<<(*it).get_time()<<endl;
		it++;
	}
    handle.close();
}


iplist::~iplist()
{
    //dtor
}

