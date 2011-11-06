#include "message.h"
#include <cstdlib>
#include <iostream>
message::message()
{
    type='\0';
}

char message::open(string msg)
{
    string help;
    int pos;
    pos=msg.find("\n",0);
    if(pos<1 || pos>MAX_LENGTH_COMMAND+1
				||(unsigned int)pos==string::npos) return type = 'e';
    help=msg.substr(0,pos);
    msg=msg.substr(pos+1);
    if(help.compare("send")==0)
    {
        if(help.length() !=4) return type='e';
        pos=msg.find("\n",0);
        reciver=msg.substr(0,pos);
        msg=msg.substr(pos+1);
			reciverlist.clear();
			while((pos=reciver.find(","))!=string::npos)
			{
				if(pos > MAX_LENGTH_ADRESS) return type='e';
				reciverlist.push_back(reciver.substr(0,pos));
				reciver=reciver.substr(pos+1);
				
			} 
			reciverlist.push_back(reciver);
        pos=msg.find("\n",0);
        betreff=msg.substr(0,pos);
        cout<<"betreff: "<<betreff<<endl;
        msg=msg.substr(pos+1);
        if(reciver.length() > MAX_LENGHT_BETREFF) return type='e';
        text=msg;
        cout<<"message: "<<text<<endl;
        return type='s';
    }
    if(help.compare("delete")==0)
    {
        if(help.length() !=6) return type='e';
        msg_nmb=atoi(msg.c_str());
        return type ='d';

    }
    if(help.compare("read")==0)
    {
        if(help.length() !=4) return type='e';
                msg_nmb=atoi(msg.c_str());
        return type= 'r';
    }
    if(help.compare("list")==0)
    {
        if(help.length() !=4) return type='e';
        return type= 'l';
    }
    if(help.compare("quit")==0)
    {
        if(help.length() !=4) return type='e';
        return type= 'q';
    }
    return type= 'e';
}

string message::get_reciver()
{
    if(type!= 's')return "";
    return reciver;
}

list <string> message::get_reciverlist()
{
    return reciverlist;
}

string message::get_betreff()
{
    if(type!= 's'&& type!= 'm')return "";
    return betreff;
}

int message::get_msg_nmb()
{
    if(type!= 'r'&&type!='d')return -1;
    return msg_nmb;
}

string message::get_message()
{
    if(type!= 's'&& type!= 'm')return "";
    return text;
}
char message::get_type()
{
    return type;
}
message::~message()
{
    //dtor
}
