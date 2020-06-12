#include "prenotazione.h"
//#include "customers.h"
//#include "Graph.h"
//#include "Dijkstra.h"
#include "stdinutils.h"

#define MIN_VOLI_PER_GETTONATI 2

/*
Prenotati initNode(char *partenza, char *destinazione, int costo, int durata)
{
    Prenotati P = (Prenotati)malloc(sizeof(struct voliPrenotati));
    P->partenza = partenza;
    P->destinazione = destinazione;
    P->costo = costo;
    P->durata = durata;
    P->next = NULL;

    return P;
}


Prenotati insertTail(Prenotati P, char *partenza, char *destinazione, int costo, int durata)
{
    if (P != NULL)
    {
        P->next = insertTail(P->next, partenza, destinazione, costo, durata);
    }
    else
    {
        P = initNode(partenza,destinazione,costo,durata);
    }

    return P;
}


Prenotati insertHead(Prenotati P, int partenza,int destinazione, int costo, int durata)
{
    if (P != NULL)
    {
        Prenotati X = (Prenotati )malloc(sizeof(struct voliPrenotati));
        X->partenza = partenza;
        X->destinazione = destinazione;
        X->costo = costo;
        X->durata=durata;
        X->next = P;

        return X;
    }

    return initNode(partenza, destinazione, costo, durata);
}


void printVoliPrenotati(Prenotati P)
{
    if (P != NULL)
    {
        printf(" %s %s ", P->partenza, P->destinazione);
        printf(" %d ", P->costo);
        printf(" %d ", P->durata);
        printVoliPrenotati(P->next);
        printf("\n");
    }
}


void freeVoliPrenotati(Prenotati P)
{
    if (P != NULL)
    {
        freeVoliPrenotati(P->next);
        free(P);
    }
}
*/

Prenotati initNode(int partenza, int destinazione, int peso)
{
    Prenotati P = (Prenotati)malloc(sizeof(struct voliPrenotati));
    P->partenza = partenza;
    P->destinazione = destinazione;
    P->peso=peso;
    P->next = NULL;

    return P;
}


Prenotati insertTail(Prenotati P, int partenza, int destinazione, int peso)
{
    if (P != NULL)
    {
        P->next = insertTail(P->next, partenza, destinazione, peso);
    }
    else
    {
        P = initNode(partenza,destinazione,peso);
    }

    return P;
}


Prenotati insertHead(Prenotati P, int partenza,int destinazione, int peso)
{
    if (P != NULL)
    {
        Prenotati X = (Prenotati )malloc(sizeof(struct voliPrenotati));
        X->partenza = partenza;
        X->destinazione = destinazione;
        X->peso=peso;
        X->next = P;

        return X;
    }

    return initNode(partenza, destinazione, peso);
}

/*
void printVoliPrenotati(Prenotati *P, int i)
{
    if (P != NULL)
    {
        printf("%d) %d -> %d ", i, (*P)->partenza, (*P)->destinazione);
        printVoliPrenotati(, i+1);
        printf("\n");
    }
}*/


void freeVoliPrenotati(Prenotati P)
{
    if (P != NULL)
    {
        freeVoliPrenotati(P->next);
        free(P);
    }
}


/*
void prenotaVolo(Graph G, Customers Cliente, char * username, Nomi_Luoghi NM)
{

    char* scelta;
    int partenza, destinazione, costo_comp, durata_comp, scelta2;
    int esistono_mete_gettonate=0, destinazione_gia_scelta=0;

    while( Cliente!=NULL && strcmp (Cliente->user,username )!=0)
    {
        Cliente= Cliente->next;
    }

    if (Cliente ->punti >0)
    {
        printf("\n Hai accumulato %d punti.\n",Cliente->punti) ;
    }

    printf("\nVuoi vedere le mete piu' gettonate[S\\n]?\t");
    fflush(stdin);
    scelta=read();
    if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
    {

        while( NM!=NULL )
        {

            if (NM->contatore_voli>MIN_VOLI_PER_GETTONATI)
            {
                printf("id: %d - %s con %d visite totali ricevute\n",NM->id,NM->nome_luogo, NM->contatore_voli);
                esistono_mete_gettonate=1;
            }
            NM=NM->next;

        }
        if (!esistono_mete_gettonate)
        {
            printf("Non abbiamo delle mete da consigliarti in questo momento, sono tutte ugualmente belle!\n");


        printf("\nVuoi andare in uno dei luoghi piu gettonati[S\\n]?\t");
        fflush(stdin);
        scelta=read();
        if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
        {
            printf("Inserisci il numero corrispondente alla destinazione desiderata.\t");
            fflush(stdin);
            destinazione=readint();
            destinazione_gia_scelta=1;
        }
        }
    }
    if (!destinazione_gia_scelta)
    {
        scelta_visualizza_elenco(NM);
        printf("Inserisci il numero corrispondente alla destinazione desiderata.\t");
        fflush(stdin);
        destinazione=readint();
    }

    printf("Perfetto.\nOra inserisci il numero corrispondente al luogo di partenza.\t");
    fflush(stdin);
    partenza=readint();

    costo_comp=dijkstra_costo(G, partenza, destinazione);
    printf("La tratta piu' economica ti costera' %d.\n", costo_comp);
    durata_comp=dijkstra_durata(G, partenza, destinazione);
    printf("La tratta piu' breve ti costera' %d.\n", durata_comp);


    printf("Inserisci\n1 per la tratta piu' economica\n2 per la tratta piu' breve\n3 per annullare.\nRicorda che "
           "piu' il viaggio sara' costoso piu' accumulerai punti per fantastici sconti per i tuoi prossimi voli!\t");
    fflush(stdin);
    scelta2=readint();
    switch (scelta2)
    {

    case 1:

    {
        if (Cliente ->punti >0)
        {
            printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[S\\n]?\t", Cliente->punti);
            fflush(stdin);
            scelta=read();
            if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
            {
                costo_comp=costo_comp-Cliente->punti;

                Cliente->punti=0;
            }
        }
        *Cliente->elenco_prenotazioni=insertHead(*Cliente->elenco_prenotazioni, partenza, destinazione, costo_comp);
        Cliente->punti=(costo_comp/100)*10; //il 10% dell'ordine
        break;
    }
    case 2:
    {

        if (Cliente ->punti >0)
        {
            printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[S\\n]?\t", Cliente->punti);
            fflush(stdin);
            scelta=read();
            if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
            {
                costo_comp=costo_comp-Cliente->punti;

                Cliente->punti=0;
            }
        }
        *Cliente->elenco_prenotazioni=insertHead(*Cliente->elenco_prenotazioni, partenza, destinazione, durata_comp);
        Cliente->punti=(durata_comp/100)*10; //il 10% dell'ordine
        break;
    }
    case 3:

    {

        return;
    }

    }



}
*/

void visualizza_prenotazioni_effettuate(char *username, Customers *Utente)
{

    //ho il dubbio che possa andare in seg scritta cosi' in un caso particolare ma in effetti non credo
    //se dovesse dare problemi basta mettere la strcmp in un if dentro il ciclo e aggiornare una flag quando entra nell'if per uscire dal ciclo
    while (Utente!=NULL && !strcmp(Utente->user, username))
    {
        Utente=Utente->next;
    }
    //printVoliPrenotati(Utente->elenco_prenotazioni, 1);
    /*
    struct voliPrenotati **tmp=(Utente->elenco_prenotazioni); int i=0;
    while (*tmp!=NULL) {
        printf("%d) %d -> %d \n", i, tmp.partenza, *tmp->destinazione);
        printf("\n");
        *tmp=*tmp->next;
        i++;
    }*/
    printf("%d)  ", *(Utente->elenco_prenotazioni)->partenza);

}



void registra(Customers **L, char *name, char * surname, char * username, char * password)
{

    Customers *new_node= malloc(sizeof(Customers));

    new_node->nome=name;
    new_node->cognome=surname;
    new_node->user=username;
    new_node->password=password;
    new_node->punti=0;

    if (!*L)
    {
        *L = new_node;
        new_node->next = NULL;
    }
    else
    {
        Customers *n = *L;
        while (n->next && n->cognome > surname)
            n = n->next;
        new_node->next = n->next;
        n->next = new_node;
    }


}


int UserGiaPresente(Customers *L, char *username)
{

    Customers *current = L;

    while(current!=NULL && strcmp(current->user,username)!=0)
    {
        current=current->next;
    }
    if(current!=NULL)
    {
        return 1;

    }
    else
    {

        return 0;
    }


}

int controllaCredenziali(Customers *L,char * username, char * password)
{
    Customers *current = L;

    while(current!=NULL && strcmp(current->user,username)!=0 && strcmp (current->password, password)!= 0)
    {
        current=current->next;
    }
    if(current!=NULL)
    {
        return 1;

    }
    else
    {

        return 0;
    }



}
