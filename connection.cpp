#include "connection.h"

#include <string.h>
using namespace std;

connection::connection()
{
    create_socket = socket (AF_INET, SOCK_STREAM, 0);

    memset(&address,0,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons (PORT);

    if (bind ( create_socket, (struct sockaddr *) &address, sizeof (address)) != 0)
    {
        cerr<<"bind error"<<endl;
          return;
    }
    listen (create_socket, 5);

    addrlen = sizeof (struct sockaddr_in);
}

int connection::get_sock()
{
    return new_socket;
}

string connection::get_msg()
{
    return buffer;
}

int connection::connect()
{
    new_socket = accept ( create_socket, (struct sockaddr *) &cliaddress, &addrlen );
    if (new_socket > 0)
    {
        buffer = "Welcome to my server! I hate you so much!\n";
        send(new_socket, buffer.c_str(), buffer.size(),0);
        cout<<"client connected.....  " << inet_ntoa (cliaddress.sin_addr)<<":"<<ntohs(cliaddress.sin_port)<<endl;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int connection::recive()
{
    char buf[BUF];
    size = recv (new_socket, (void *) &buf, BUF,NULL);
    if( size > 0)
    {
        buf[size] = '\0';
        buffer.assign(buf);
        cout<<buffer.size()<<endl;
        return EXIT_SUCCESS;
    }
    else if (size == 0)
    {
        cout<<"Client closed remote socket"<<endl;
        return EXIT_FAILURE;
    }
    else
    {
        cout<<"recv error"<<endl;
        return EXIT_FAILURE;
    }
}
void connection::say_ok()
{
    char ans[4] = "OK\n";
        send(new_socket, ans, sizeof(ans),0);
}

void connection::say_err()
{
    char ans[5] = "ERR\n";
        send(new_socket, ans, sizeof(ans),0);
}

void connection::say_message(string ans)
{
     send(new_socket, ans.c_str(), ans.size(),0);
}

connection::~connection()
{
    close (new_socket);
}
