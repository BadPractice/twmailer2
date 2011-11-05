#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define BUF 1024
#define PORT 6543

using namespace std;

class client
{
    public:
        client(int);
        int recive();
        string get_msg();
        void say_ok();
        void say_err();
        void say_message(string);
        int get_sock();
        virtual ~client();
    protected:
    private:
    int size;
    int new_socket;
    string buffer;
};

#endif // CLIENT_H
