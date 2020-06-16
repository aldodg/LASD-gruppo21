/*

@authors
Abbate Carmine
Fabio De Martino
Aldo Di Giovanni

*/

#include "Graph.h"

#include "stdinutils.h"
#include "mainfunction.h"
#include "List.h"
#include "Dijkstra.h"
#include "prenotazione.h"
#define MAX 30

int main()
{

    Customers Utenti=NULL;
    int choice;
    Graph G=NULL;
    Nomi_Luoghi NM = NULL;

    G=popola_grafo_file(G, &NM);


    char usernames[MAX];
    char cognomes[MAX];
    char nomes[MAX];
    char psw[MAX];
    char psw2[MAX];
    char adminpass[MAX];

    do
    {


        printf("Benvenuto!\n\n------------Login----------\n\n");
        printf("1 - Registrati\n");
        printf("2 - Accedi con credenziali\n");
        printf("3 - Pannello admin\n");
        printf("4 - Esci\nScegli:\t");
        fflush(stdin);
        choice=readint();
        switch (choice)
        {

        case 1:
        {

            printf("\nBenvenuto nel menu' di registrazione!\n\n");
            fflush(stdin);
            printf("Inserisci Username: \n");
            fflush(stdin);
            scanf("%s", usernames);
            printf("\nInserisci Cognome: \n");
            fflush(stdin);
            scanf("%s", cognomes);
            printf("\nInserisci Nome: \n");
            fflush(stdin);
            scanf("%s", nomes);
            printf("\nInserisci Password\n");
            fflush(stdin);
            scanf("%s", psw);
            printf("\nRipeti Password\n");
            fflush(stdin);
            scanf("%s", psw2);


            while (strcmp (psw,psw2)!=0) // controllo sulle password
            {
                printf("\nPassword non coincidenti, reinserire password\n");
                fflush(stdin);
                printf("\nInserisci Password\n");
                fflush(stdin);
                scanf("%s", psw);
                printf("\nRipeti Password\n");
                fflush(stdin);
                scanf("%s", psw2);
            }

            /*Controllo su username, se già registrato impedisce la registrazione, altrimenti riempiamo la lista degli utenti*/
            if(!UserGiaPresente(Utenti,usernames)) //se l'username cercato non esiste, allora lo registriamo in lista
            {

                registra(&Utenti,nomes,cognomes,usernames, psw);
                printf("\nRegistrazione avvenuta con successo!\n");
                login(G, Utenti, usernames, NM);//se tutto ok passiamo alle funzionalità del menù login

            }
            else
            {
                printf("\nL'username scelto non e' disponibile, riprovare per favore.\n");//altrimenti ritorna al menu login
            }

            break;
        }
        case 2:
        {

            printf("Inserisci Username: \n");
            fflush(stdin);
            scanf("%s", usernames);
            printf("Inserisci Password: \n");
            fflush(stdin);
            scanf("%s", psw);

            if (!controllaCredenziali(Utenti, usernames, psw))
            {
                printf("\nNon esiste un utente %s oppure la password e' errata, controllare e riprovare.\n\n", usernames);
                break;
            }
            else
            {
                printf("\nAccesso Eseguito correttamente!\nBenvenuto %s \n", usernames);
                login(G,Utenti, usernames, NM);
            }


            break;
        }
        case 3:
        {
            printf("\nMenu Admin, inserire password:\n");
            fflush(stdin);
            scanf("%s", adminpass);
            fflush(stdin);

            if ( strcmp (adminpass,"Admin")==0 || strcmp (adminpass, "admin")==0)
            {

                printf("\nPassword corretta, benvenuto!\n");
                menutratte(G, NM);

            }
            else 	if ( strcmp (adpass,"Admin")!=0 || strcmp (adpass, "admin")!=0)
            {
                printf("\nPassword non corretta!\n");

            }
            break;
        }
        case 4:
        {
            printf("\nArrivederci!\n");
            freeGraph(G);
            cancellaListaNomi(NM);
            freeCustomers(Utenti);
            return 0;
        }
        default:
        {

            printf("\nDigitare 1 per registrarsi\nDigitare 2 per accedere con credenziali\nDigitare 3 per gestire le tratte\nScegli:\t");

            break;

        }

        }

    }
    while(choice!=1 || choice !=2 || choice !=3 || choice !=4);


    return 0;

}
