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
    /*
    //inizio test grafi
    Graph G=NULL;
    Nomi_Luoghi NM = NULL;

    G=popola_grafo_file(G, &NM);
    printGraph(G);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("--------------------------------------------\n");
    removeEdge(G, 15, 14); //rimuovo la tratta da Catanzaro a reggio calabria
    printGraph(G);
    printf("--------------------------------------------\n");
    addEdge (G, 15, 14, 40, 25); //rimetto la tratta, impostando un costo di 40 euro e durata di 25 min
    printGraph(G);
    printf("----------------------------------------\n");
    removeNode (G, 15, &NM); //rimuovo catanzaro come aeroporto;
    printGraph(G);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("-------------------------------------------\n");
    aggiungi_aeroporto(G, &NM);
    printGraph(G);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("Il nodo ha %d archi. Ne aspetto 68 perche' ho rimosso catanzaro\n", numeroArchi(G));
    printf("aspetto 1: %d\n", esisteArco(G, 15, 14)); //controllo se esista la tratta da cosenza a reggio calabria
    printf("aspetto 0: %d\n", esisteArco(G, 18, 17)); //controllo se esista la tratta da salerno a bari
    printf("aspetto 45: %d\n", costoArco(G, 15, 14)); //costo della tratta da cosenza a reggio calabria

    freeGraph(G);
    cancellaListaNomi(NM);
    //fine test grafi

    //inizio test dijstra
    int V = 9;
    G = initGraph(V);
    addEdge(G, 0, 1, 4, 6);
    addEdge(G, 0, 7, 8, 2);
    addEdge(G, 1, 0, 4, 5);
    addEdge(G, 1, 2, 8, 5);
    addEdge(G, 1, 7, 11, 5);
    addEdge(G, 2, 1, 8,5);
    addEdge(G, 2, 3, 7,5);
    addEdge(G, 2, 8, 2,5);
    addEdge(G, 2, 5, 4,5);
    addEdge(G, 3, 2, 8,5);
    addEdge(G, 3, 4, 9,5);
    addEdge(G, 3, 5, 14,5);
    addEdge(G, 4, 5, 10,5);
    addEdge(G, 4, 3, 9,5);
    addEdge(G, 5, 6, 2,5);
    addEdge(G, 5, 4, 10,5);
    addEdge(G, 5, 2, 4,5);
    addEdge(G, 5, 3, 14,5);
    addEdge(G, 6, 7, 1,5);
    addEdge(G, 6, 5, 2,5);
    addEdge(G, 6, 8, 6,5);
    addEdge(G, 7, 8, 7,5);
    addEdge(G, 7, 6, 1,5);
    addEdge(G, 7, 0, 8,5);
    addEdge(G, 7, 1, 11,5);
    addEdge(G, 8,2, 2,5);
    addEdge(G, 8,6, 6,5);
    addEdge(G, 8,7, 7,5);
    printGraph(G);
    //parto da 0 e devo arrivare al nodo 8. calcolando per costo, dovro' ottenere un prezzo di 14
    printf("La tratta piu' economica ti costera' %d.\n", dijkstra_costo(G, 0, 8));
    printf("La tratta piu' breve ti costera' %d.\n", dijkstra_durata(G, 0, 8));

    //  freeGraph(G);
    //fine test dijstra
    */
    Customers *Utenti=NULL;
    int choice;
    Graph G=NULL;
    Nomi_Luoghi NM = NULL;

    G=popola_grafo_file(G, &NM);
    printGraph(G);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("--------------------------------------------\n");

    /*Menu da aggiustare sia esteticamente per le funzioni*/
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
                login(G, &Utenti, username, NM);//se tutto ok passiamo alle funzionalità del menù login
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
                login(G, &Utenti, username, NM);
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
