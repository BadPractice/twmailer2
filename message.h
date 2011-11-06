#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_LENGTH_COMMAND 8
#define MAX_LENGTH_ADRESS 8
#define MAX_LENGHT_BETREFF 80
#include <string>
#include <list>
using namespace std;
class message
{
    public:
        message();
        char open(string msg);
        char get_type();
        string get_reciver();
        list <string> get_reciverlist();
        string get_betreff();
        string get_message();
        int get_msg_nmb();
        virtual ~message();
    protected:
    private:
    char type ;
    list<string> reciverlist;
    string reciver;
    string betreff;
    string text;
    int msg_nmb;

};

#endif // MESSAGE_H
