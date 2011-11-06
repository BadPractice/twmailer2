all: hts1

hts1: badguy.o connection.o iplist.o login.o main.o message.o user.o
	g++ badguy.o connection.o iplist.o login.o main.o message.o user.o -o hts1 -pthread -lldap -DLDAP_DEPRECATED

badguy.o: badguy.h badguy.cpp
	g++ -c badguy.cpp


connection.o: connection.h connection.cpp
	g++ -c connection.cpp

iplist.o: iplist.h iplist.cpp
	g++ -c iplist.cpp

login.o: login.h login.cpp
	g++ -c -lldap -DLDAP_DEPRECATED login.cpp

main.o: login.h user.h message.h connection.h main.cpp
	g++ -c main.cpp

message.o: message.h message.cpp
	g++ -c message.cpp

user.o: user.h user.cpp
	g++ -c user.cpp

clean:
	rm -rf *o hts1

start: hts1
	./hts1
