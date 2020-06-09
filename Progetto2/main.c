/*
@authors
Abbate Carmine
Fabio De Martino
Aldo Di Giovanni
*/

#include "Graph.h"
#include "customers.h"
#include "stdinutils.h"
#include "mainfunction.h"
#include "gettonate.h"

int main()
{

    //inizio test grafi
    Graph L=NULL;
    Nomi_Luoghi NM = NULL;

    L=popola_grafo_file(L, &NM);
    printGraph(L);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("--------------------------------------------\n");
    removeEdge(L, 15, 14); //rimuovo la tratta da Catanzaro a reggio calabria
    printGraph(L);
    printf("--------------------------------------------\n");
    addEdge (L, 15, 14, 40, 25); //rimetto la tratta, impostando un costo di 40 euro e durata di 25 min
    printGraph(L);
    printf("----------------------------------------\n");
    removeNode (L, 15, &NM); //rimuovo catanzaro come aeroporto;
    printGraph(L);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("-------------------------------------------\n");
    aggiungi_aeroporto(L, &NM);
    printGraph(L);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("Il nodo ha %d archi. Ne aspetto 68 perche' ho rimosso catanzaro\n", numeroArchi(L));
    printf("aspetto 1: %d\n", esisteArco(L, 15, 14)); //controllo se esista la tratta da cosenza a reggio calabria
    printf("aspetto 0: %d\n", esisteArco(L, 18, 17)); //controllo se esista la tratta da salerno a bari
    printf("aspetto 45: %d\n", costoArco(L, 15, 14)); //costo della tratta da cosenza a reggio calabria

    freeGraph(L);
    cancellaListaNomi(NM);
    //fine test grafi

    Customers *Utenti=NULL;
    int choice;

    /*Menu da aggiustare sia esteticamente per le funzioni*/
    do
    {


        printf("\n\n------------Login----------\n\n");
        printf("1 - Registrati\n");
        printf("2 - Accedi con credenziali\n");
        printf("3 - Pannello admin\n");
        printf("4 - Esci\n");
        choice=readint();
        switch (choice)
        {

        case 1:
        {
            // Per leggere da stdin usare la read(), funzione implementata in stdinutils.
            printf("\nBenvenuto nel menu' di registrazione!\n\n");
            fflush(stdin);
            printf("Inserisci Username: \n");
            username=read();
            printf("\nInserisci Cognome: \n");
            cognome=read();
            printf("\nInserisci Nome: \n");
            nome=read();
            printf("\nInserisci Password\n");
            pass=read();
            printf("\nRipeti Password\n");
            pass2=read();

            if (strcmp (pass,pass2)!=0) // controllo sulle password
            {
                printf("\nPassword non coincidenti, reinserire password\n");
                fflush(stdin);
                printf("\nInserisci Password\n");
                pass=read();
                printf("\nRipeti Password\n");
                pass2=read();
            }

            /*Controllo su username, se già registrato impedisce la registrazione, altrimenti riempiamo la lista degli utenti*/
            if(!UserGiaPresente(Utenti,username)) //se l'username cercato non esiste, allora lo registriamo in lista
            {

                registra(&Utenti,nome,cognome,username, pass);
                printf("\nRegistrazione avvenuta con successo!\n");
                login(&NM);//se tutto ok passiamo alle funzionalità del menù login
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

            if (!controllaCredenziali(Utenti, username,pass))
            {
                printf("\nNon esiste un utente %s oppure la password e' errata, controllare e riprovare.\n\n", username);
                break;
            }
            else
            {
                printf("\nAccesso Eseguito correttamente!\nBenvenuto %s \n", username);
                login(&NM);
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
                menutratte();

            }
            else 	if ( strcmp (adpass,"Admin")!=0 || strcmp (adpass, "admin")!=0)
            {
                printf("\nPassword non corretta!\n");

            }
            break;
        }
        case 4:
            return 0;

        default:
        {

            printf("\nDigitare 1 per registrarsi\nDigitare 2 per accedere con credenziali\nDigitare 3 per gestire le tratte\n");

            break;

        }

        }

    }
    while(choice!=1 || choice !=2 || choice !=3 || choice !=4);


    return 0;

}
