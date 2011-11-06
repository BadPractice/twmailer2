#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ldap.h>
#define LDAP_HOST "ldap.technikum-wien.at"
#define LDAP_PORT 389
#define SEARCHBASE "dc=technikum-wien,dc=at"
#define SCOPE LDAP_SCOPE_SUBTREE
#define BIND_USER "uid=if10b037,ou=People,dc=technikum-wien,dc=at"			/* anonymous bind with user and pw NULL */
#define BIND_PW "Get_my_passw0rd()"    										/* -> kein anonymous bind from home */
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
		string filter;
		
		/* C-Variablen für Konvertierung von C++-Strings */		
		const char* filter_c;  // Für User-search C++ - Konversion
		const char* passwd_c;
		const char* found;
      
        LDAP *ld;                /* LDAP resource handle */
        LDAPMessage *result, *e; /* LDAP result handle */    		
		int  rc;
		char *attribs[3];        /* attribute array for search */
		
    
};

#endif // LOGIN_H
