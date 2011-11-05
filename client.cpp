#include "client.h"

client::client(int aaa)
{
    new_socket=aaa;
    //ctor
}

client::~client()
{
    //dtor
}

string client::get_msg()
{
    return buffer;
}


int client::recive()
{
 //   char buf[] = buffer.c_str();
     char buf[BUF];
        size = recv (new_socket, (void *) &buf, BUF,NULL);
    if( size > 0)
    {
        buf[size] = '\0';
        buffer.assign(buf);
        //cout<<buffer.size()<<endl;
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
void client::say_ok()
{
    char ans[4] = "OK\n";
        send(new_socket, ans, sizeof(ans),0);
}

void client::say_err()
{
    char ans[5] = "ERR\n";
        send(new_socket, ans, sizeof(ans),0);
}

void client::say_message(string ans)
{
     send(new_socket, ans.c_str(), ans.size(),0);
}
