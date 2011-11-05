#ifndef USER_H
#define USER_H
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <stdlib.h>
using namespace std;

class user
{
    public:
        user(string aaa);
        void send(string to, string message);
        string do_list();
        void do_del(int);
        string do_read(int msg);
        int writefile(string);
         ~user();
    protected:
    private:
        string name;
        int getfilenames(list<string > *);
        string getfile(string filename, int anz);
        bool sortnumb (string first, string second);
    };

#endif // USER_H
