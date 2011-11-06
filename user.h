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
        void send(list <string> to, string message);
        string do_list();
        void do_del(int);
        string do_read(int msg);
         ~user();
    protected:
    private:
        string name;
        void writefile(string);
        int getfilenames(list<string > *);
        string getfile(string filename);
        bool sortnumb (string first, string second);
    };

#endif // USER_H
