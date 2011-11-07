#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "user.h"
#include "connection.h"
#include <list>
#include "message.h"
#include "login.h"
#include "iplist.h"
#define MAX_LOGIN_TRY 3
iplist myipl = iplist();
void* do_client(void *xxx)
{
    pthread_detach (pthread_self ());cout<<"thread created!"<<endl;
    
    int pos,i=0;
    login *mylog;
    message mymsg = message();
	connection mycon =*((connection *)xxx);
    string h;
    
    
while(1)
{
	myipl.debug_msg();
    if(mycon.recive())
    {
        cout << "bad data"<<endl;
        return NULL;
    }
    h=mycon.get_msg();
    pos=h.find("\n",0);
    h=h.substr(0,pos);
    if(myipl.check(h))
    {
	mycon.say_err();
	return NULL;
    }
    mylog= new login(mycon.get_msg());
    //login wird erstellt mit den string "name\npasswd"
    if((*mylog).proof())
    {
        mycon.say_err();
        delete mylog;
        i++;
        if(i==MAX_LOGIN_TRY)
        { 
			myipl.add(h); 
			return NULL;
		}
    }
    else break;
}
    mycon.say_ok();
    user myusr = user((*mylog).get_name());
    while(1)
    {
        if(mycon.recive())
        {
            cout<<"cant recive data"<<endl;
            return NULL;
        }
        cout<<"recived"<<endl;
        mymsg.open(mycon.get_msg());
        switch(mymsg.get_type())
        {

        case 's':
             h= mymsg.get_betreff()+ "\n"+ mymsg.get_message();
            myusr.send(mymsg.get_reciverlist(),h);
            cout<<mymsg.get_message()<<endl;
            mycon.say_ok();
            break;
        case 'l':
            //cout <<"sende list... "<<endl;
            mycon.say_message(myusr.do_list());
            break;
        case 'r':
            myusr.do_read(mymsg.get_msg_nmb());
            break;
        case 'd':
            myusr.do_del(mymsg.get_msg_nmb());
            break;
        case 'q':
			return NULL;
		case 'e':
			mycon.say_err();
			break;
        }

    }
    return NULL;
}
using namespace std;
int main()
{
    string test;
    list <pthread_t *> threads;
    connection *mycon= new connection();
    connection * copy = NULL;
    while(1)
    {
		cout<<"waiting for someone.."<<endl;
        if(!(*mycon).connect())
        {
            threads.push_back(new pthread_t);
            cout << "createing thread..."<<endl;
          //  cout <<"ip: "<< debug <<endl;


copy = new connection(* mycon);
            pthread_create( threads.back(), NULL, do_client,(void*) copy);
        }
        else return EXIT_FAILURE;

        //  pthread_create( threads.back(), NULL, do_client, (void*) &debug);
    }
    return EXIT_SUCCESS;
    return 0;
}

