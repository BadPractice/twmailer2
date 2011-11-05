#ifndef LOGIN_H
#define LOGIN_H
#include <string>
using namespace std;

class login
{
    public:
        login(string);
        int proof();
        string get_name();
        virtual ~login();
    protected:
    private:
    string name;
    string passwd;
};

#endif // LOGIN_H
