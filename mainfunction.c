#include"mainfunction.h"


	void login(){
		int choice;
		
		do 
	{
		
		
		printf("\n\n---Menu' Principale Aeroporto---\n\n");
		printf("1 - Prenota un volo\n");
		printf("2 - Visualizza prenotazioni effettuate\n");
		printf("3 - Esci\n");
		
		choice=readint();
		
			switch (choice)	{
				
				case 1: 
				
				/*funzioni da implementare: 
				bisogna creare un sottomenu che permetta di scegliere le tratte, con due opzioni, solo partenza
				e partenza e destinazione
	*/
				break;
				
				
				case 2:
				// da implementare: stampa grafo	
				break;
				
				case 3:
				
				return;
				
				default:
				
				printf("\nScelta non corretta\nDigitare 1 per prenotare un volot\n2Per visualizzare le prenotazioni effettuate\n3Per uscire");
				
				
							}
			
		
		
	}while (choice !=1 || choice !=2  || choice !=3);
	
	
}
	
	void menutratte(){
		
		int choice;
			do{
		
		printf("\n\n---Menu' gestione tratte---\n\n");
		printf("1 - Aggiungere tratta\n");
		printf("2 - Rimuovi tratta\n");
		printf("3 - Esci\n");
		
		choice=readint();
		
		switch (choice)
				{
					
					case 1:
						// implementare funzioni aggiunta vertici e archi
					
					break;
					
					case 2:
						//implementare funzioni rimuovi nodi e archi
					break;
					
					case 3:
					
					return;
					
					default:
						
					printf("\nScelta non corretta:\nDigitare 1 per aggiungere una tratta\nDigitare 2 per eliminare una tratta\nDigitare 3 per uscire");
				}
		
			}while(choice !=1 || choice !=2 || choice !=3);
		
		}
		
	int controllaCredenziali(Customers *L,char * username, char * password){
			Customers *current = L;
		
		while(current!=NULL && strcmp(current->user,username)!=0 && strcmp (current->password, password)!= 0){
			current=current->next;
		}
		if(current!=NULL){
		return 1;
		 
		}else{
			
			return 0;
		}
	
		
		
	}
	
