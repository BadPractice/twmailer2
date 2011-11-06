#include "login.h"


login::login(string msg) { 
    int pos;				// Username und Passwort aus Eingabe werden zugewiesen
    pos=msg.find("\n",0);
    name=msg.substr(0,pos);
    
    passwd=msg.substr(pos+1); // \n sollen ausgelassen werden
    pos=msg.find("\n",0);
    passwd.erase(pos);        // weiteres \n wird gelöscht

    
    filter = "(uid="; // search-Filter zusammenstückeln
    filter += name;
    filter += "*)";
    filter_c = filter.c_str();
    
    passwd_c = passwd.c_str();

    rc=0;
    
	attribs[0]=strdup("uid");/* return uid and cn of entries */
	attribs[1]=strdup("cn");
	attribs[2]='\0';         /* array must be NULL terminated */
}


int login::proof()
{
	
	/* setup LDAP connection */
	if((ld=ldap_init(LDAP_HOST, LDAP_PORT)) == NULL) {
		perror("ldap_init failed");
		return EXIT_FAILURE;
	}
	printf("\nconnected to LDAP server %s on port %d\n",LDAP_HOST,LDAP_PORT);
	
	/* non-anonymous bind from home */
	rc = ldap_simple_bind_s(ld,BIND_USER,BIND_PW);
	
	if(rc != LDAP_SUCCESS) {
		fprintf(stderr,"\nLDAP error: %s\n",ldap_err2string(rc));
		return EXIT_FAILURE;
	} else {
		printf("\npretended anonymous bind successful\n");
	}
	
	/* perform LDAP search */
	rc = ldap_search_s(ld, SEARCHBASE, SCOPE, filter_c, attribs, 0, &result);
	
	if(rc != LDAP_SUCCESS) {
		fprintf(stderr,"\nLDAP search error: %s\n",ldap_err2string(rc));
		return EXIT_FAILURE;
	}
	
	e = ldap_first_entry(ld, result);
	found = ldap_get_dn(ld,e);
	printf("\nDN: %s\n",found);
	
	/* User anmelden */
	rc = ldap_simple_bind_s(ld,found,passwd_c);
	
	if(rc != LDAP_SUCCESS) {
		fprintf(stderr,"\nLDAP error: %s\n",ldap_err2string(rc));
		return EXIT_FAILURE;
	} else {
		printf("\nbind successful\n");
	}
	
	printf("\nTotal results: %d\n", ldap_count_entries(ld, result));
	
	
	/* free memory used for result */
	ldap_msgfree(result);
	free(attribs[0]);
	free(attribs[1]);
	printf("\nLDAP login succeeded\n");
	
	ldap_unbind(ld);
	return EXIT_SUCCESS;
}

string login::get_name()
{
    return name;
}
login::~login()
{
    //dtor
}
