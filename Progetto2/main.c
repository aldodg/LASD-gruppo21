/*
@authors
Abbate Carmine
Fabio De Martino
Aldo Di Giovanni*/

#include"graph.h"
#include"customers.h"
#include"stdinutils.h"
#include"mainfunction.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{

    int choice;

    /*Menu da aggiustare sia esteticamente per le funzioni*/
    do
    {


        printf("\n\n------------Login----------\n\n");
        printf("1 - Registrati\n");
        printf("2 - Accedi con credenziali\n");
        printf("3 - Gestisci tratte\n");
        choice=readint();
        switch (choice)
        {

        case 1:
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

            /*Controllo su username, se gi� registrato impedisce la registrazione, altrimenti riempiamo la lista degli utenti*/
            if(!UserGiaPresente(Utenti,username)) //se l'username cercato non esiste, allora lo registriamo in lista
            {

                registra(&Utenti,nome,cognome,username, pass);
                printf("\nRegistrazione avvenuta con successo!\n");
                login();//se tutto ok passiamo alle funzionalit� del men� login
            }
            else
            {

                printf("\nLo username scelto non e' disponibile, riprovare!\n");//altrimenti ritorna al menu login
            }

            break;

        case 2:

            printf("Inserisci Username: \n");
            fflush(stdin);
            username=read();
            printf("Inserisci Password: \n");
            pass=read();

            if (!controllaCredenziali(Utenti, username,pass))
            {
                printf("\nNon esiste un utente %s o password errata, controllare e riprovare\n", username);
                break;
            }
            else
            {
                printf("\nAccesso Eseguito correttamente!\nBenvenuto %s \n", username);
                login();
            }


            break;

        case 3:
            //metodo incompleto, va completato con le funzioni sui grafi
            menutratte();

        default:

            printf("\nValore non corretto!\nDigitare 1 per registrarsi\nDigitare 2 per accedere con credenziali\n\n");

            break;

        }



    }
    while(choice!=1 || choice !=2 || choice !=3);








    return 0;

}
