#include"customers.h"




	void registra(Customers **L, char *name, char * surname, char * username, char * password){
		
		Customers *new= malloc(sizeof(Customers));
		
		new->nome=name;
		new->cognome=surname;
		new->user=username;
		new->password=password;
		
		 if (!*L) {
        *L = new;
        new->next = NULL;
    }
    else {
        Customers *n = *L;
        while (n->next && n->cognome > surname)
            n = n->next;
        new->next = n->next;
        n->next = new;
    }
		
		
	}
	
	
		int UserGiaPresente(Customers *L, char *username){
		
		Customers *current = L;
		
		while(current!=NULL && strcmp(current->user,username)!=0){
			current=current->next;
		}
		if(current!=NULL){
		return 1;
		 
		}else{
			
			return 0;
		}
	
		
	}
