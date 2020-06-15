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

int main()
{

    Customers Utenti=NULL;
    int choice;
    Graph G=NULL;
    Nomi_Luoghi NM = NULL;

    G=popola_grafo_file(G, &NM);
    printGraph(G);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("--------------------------------------------\n");
    char usercazz[6];
    char cogncazz[6];
    char namecazz[6];
    char psw[6];
    char psw2[6];

    do
    {


        printf("\n\n------------Login----------\n\n");
        printf("1 - Registrati\n");
        printf("2 - Accedi con credenziali\n");
        printf("3 - Pannello admin\n");
        printf("4 - Esci\nScegli:\t");
        choice=readint();
        switch (choice)
        {

        case 1:
        {

            printf("\nBenvenuto nel menu' di registrazione!\n\n");
            fflush(stdin);
            printf("Inserisci Username: \n");fflush(stdin);
            scanf("%s", usercazz);
            //username=read();
            printf("\nInserisci Cognome: \n");fflush(stdin);
            //cognome=read();
            scanf("%s", cogncazz);
            printf("\nInserisci Nome: \n");fflush(stdin);scanf("%s", namecazz);
            //nome=read();scanf("%s", cogncazz);
            printf("\nInserisci Password\n");fflush(stdin);scanf("%s", psw);
            //pass=read();
            printf("\nRipeti Password\n");fflush(stdin);scanf("%s", psw2);
            //pass2=read();

            /*if (strcmp (pass,pass2)!=0) // controllo sulle password
            {
                printf("\nPassword non coincidenti, reinserire password\n");
                fflush(stdin);
                printf("\nInserisci Password\n");
                pass=read();
                printf("\nRipeti Password\n");
                pass2=read();
            }*/

            /*Controllo su username, se già registrato impedisce la registrazione, altrimenti riempiamo la lista degli utenti*/
            if(!UserGiaPresente(Utenti,usercazz)) //se l'username cercato non esiste, allora lo registriamo in lista
            {

                registra(&Utenti,namecazz,cogncazz,usercazz, psw);
                printf("%s ddd", Utenti->cognome);
                printf("\nRegistrazione avvenuta con successo!\n");
                login(G, Utenti, usercazz, NM);//se tutto ok passiamo alle funzionalità del menù login

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
            username=read();
            printf("Inserisci Password: \n");
            pass=read();

            if (!controllaCredenziali(Utenti, username, pass))
            {
                printf("\nNon esiste un utente %s oppure la password e' errata, controllare e riprovare.\n\n", username);
                break;
            }
            else
            {
                printf("\nAccesso Eseguito correttamente!\nBenvenuto %s \n", username);
                login(G,&Utenti, username, NM);
            }


            break;
        }
        case 3:
        {
            printf("\nMenu Admin, inserire password:\n");
            fflush(stdin);
            adpass=read();

            if ( strcmp (adpass,"Admin")==0 || strcmp (adpass, "admin")==0)
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

            freeGraph(G);
            cancellaListaNomi(NM);
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
