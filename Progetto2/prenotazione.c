#include "prenotazione.h"
#include "stdinutils.h"


Prenotati insertHead(Prenotati P, int partenza,int destinazione, int costo_complessivo, int durata_complessiva)
{

    Prenotati X = (Prenotati )malloc(sizeof(struct voliPrenotati));
    (X)->partenza = partenza;
    (X)->destinazione = destinazione;
    X->costo_complessivo=costo_complessivo;
    X->durata_complessiva=durata_complessiva;
    (X)->next = P;

    P=(X);

    return P;
}


void printVoliPrenotati(Prenotati P, int i)
{
    if (P != NULL)
    {
        printf("%d)\t%d -> %d \t\t\t\t%d\t%d", i, (P)->partenza, (P)->destinazione, P->costo_complessivo, P->durata_complessiva);
        printf("\n");
        printVoliPrenotati(P->next, i+1);

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

void freeCustomers (Customers C)
{

    if (C!=NULL)
    {
        freeVoliPrenotati(C->elenco_prenotazioni);
        freeCustomers(C->next);
        free(C);
    }

}

int esistono_mete_gettonate (Nomi_Luoghi NM)
{

    int esistono_mete_gettonate=0;

    while(NM!=NULL && !esistono_mete_gettonate)
    {

        if ((NM)->contatore_voli>0)
        {
            esistono_mete_gettonate=1;
        }
        NM=(NM)->next;

    }

    return esistono_mete_gettonate;
}

void AggiornaContatore(Nomi_Luoghi NM, int id)
{
    int trovato=0;

    while(NM!=NULL && !trovato)
    {
        if((NM)->id==id)
        {
            (NM)->contatore_voli++;
            trovato=1;
        }

        NM=(NM)->next;
    }

}


void visualizza_prenotazioni_effettuate(char *username, Customers Utente)
{

    while (Utente!=NULL && strcmp((Utente)->user, username))
    {
        Utente=(Utente)->next;
    }
    printf("Prenotazioni in ordine dall'ultima effettuata.\n\nNumero  Partenza->Destinazione      Costo       Durata\n\n");
    printVoliPrenotati((Utente)->elenco_prenotazioni, 1);

}



void registra(Customers *L, char *name, char * surname, char * username, char * password)
{

    Customers new_node= malloc(sizeof(struct customer));

    strcpy(new_node->nome,name);
    strcpy(new_node->cognome,surname);
    strcpy(new_node->user,username);
    strcpy(new_node->password,password);
    new_node->punti=0;
    new_node->elenco_prenotazioni=NULL;
    new_node->next=NULL;

    if (*L==NULL)
    {
        *L = new_node;
        new_node->next = NULL;
    }
    else
    {
        new_node->next = *L;
        *L=new_node;
    }


}


int UserGiaPresente(Customers L, char *username)
{
    Customers current = L;
    int presente=0;


    while(current!=NULL && !presente)
    {
        if (!strcmp(current->user,username)) presente=1;
        current=current->next;
    }

    return presente;

}

int controllaCredenziali(Customers L,char  username[], char  password[])
{
    Customers current = L;

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

//restituisce il massimo numero di visite, per tutte le mete
int trova_max_visite (Nomi_Luoghi NM)
{

    int max=(NM)->contatore_voli;
    while(NM!=NULL )
    {

        if ((NM)->contatore_voli>max)
        {

            max=(NM)->contatore_voli;
        }
        NM=(NM)->next;

    }

    return max;
}

//restituisce la meta col numero piu' alto di visite
int TrovaMetaGettonata(Nomi_Luoghi NM)
{

    int max=trova_max_visite(NM);
    int meta_gettonata;

    while(NM!=NULL)
    {
        if(NM->contatore_voli==max)
        {
            meta_gettonata=NM->id;
        }
        NM=NM->next;
    }

    return meta_gettonata;
}


//principale funzione operativa, si occupa della prenotazione di un nuovo volo
void prenotaVolo(Graph G, Customers Cliente, char * username, Nomi_Luoghi NM)
{

    int scelta;
    int partenza, destinazione, costo_comp=0, durata_comp=0, scelta2;


    while( Cliente!=NULL && strcmp((Cliente)->user,username ))
    {
        Cliente= (Cliente)->next;
    }

    scelta_visualizza_elenco(NM);
    printf("Per favore inserisci il numero corrispondente al luogo di partenza.\t");
    fflush(stdin);
    scanf("%d", &partenza);
    fflush(stdin);

    printf("Inserisci\n1 per la tratta piu' economica in assoluto da dove vuoi partire\n2 per le mete piu' gettonate\n3 per inserire manualmente una destinazione\n4 per annullare\nScegli:\t");
    fflush(stdin);
    scanf("%d", &scelta);
    fflush(stdin);
    switch (scelta)
    {

    case 1:
    {
        durata_comp=0;
        //prima chiamo dijkstra con parametro output 0, in modo che mi restituisca la localita' piu' vicina (in termini di costo del biglietto) a quella di partenza
        destinazione=dijkstra_costo(G, partenza, 0, 0, 0, &durata_comp);
        //ora la chiamo con parametro output 1 in modo che possa ottenere il costo per quella destinazione dalla partenza scelta
        costo_comp=dijkstra_costo(G, partenza, destinazione, 1, 1, &durata_comp);
        if (costo_comp==2147483647)
        {
            printf("Ci dispiace, questo viaggio non e' disponibile.\n");
            return;
        }
        printf("La tratta piu' economica ti costera' %d euro ed e': %d.\n", costo_comp, destinazione);
        printf("Durera' %d minuti.\n", durata_comp);
        stampa_lista_nomi(NM);
        printf("\nVuoi andarci?[1\\0]?\t");
        fflush(stdin);
        scanf("%d", &scelta);
        fflush(stdin);
        if (scelta)
        {

            if ((Cliente )->punti >0)
            {
                printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                fflush(stdin);
                scanf("%d", &scelta);
                fflush(stdin);
                if (scelta)
                {
                    costo_comp=costo_comp-(Cliente)->punti;

                    (Cliente)->punti=0;
                }
            }
            (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp, durata_comp);
            printf("Prenotazione confermata e registrata!\n");
            AggiornaContatore(NM,destinazione);
            (Cliente)->punti +=(durata_comp/100)*10; //il 10% dell'ordine
        }
        break;
    }

    case 2:
    {


        if (!esistono_mete_gettonate(NM))
        {
            printf("Non abbiamo delle mete da consigliarti in questo momento, sono tutte ugualmente belle!\n");
        }
        else
        {
            destinazione=TrovaMetaGettonata(NM);
            printf("la destinazione al momento piu' gettonata e': %d\n", destinazione);
            durata_comp=0;
            costo_comp=dijkstra_costo(G, partenza, destinazione, 1, 1, &durata_comp);
            if (costo_comp==2147483647)
            {
                printf("Ci dispiace, questo viaggio non e' disponibile.\n");
                return;
            }
            printf("La viaggio ti costera' %d euro e durera' %d minuti.\n", costo_comp, durata_comp);
            printf("\nVuoi andarci?[1\\0]?\t");
            fflush(stdin);
            scanf("%d", &scelta);
            fflush(stdin);
            if (scelta)
            {
                if ((Cliente )->punti >0)
                {
                    printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                    fflush(stdin);
                    scanf("%d", &scelta);
                    fflush(stdin);
                    if (scelta)
                    {
                        costo_comp=costo_comp-(Cliente)->punti;

                        (Cliente)->punti=0;
                    }
                }
                (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp, durata_comp);
                AggiornaContatore(NM,destinazione);
                printf("Prenotazione confermata e registrata!\n");
                (Cliente)->punti +=(durata_comp/100)*10; //il 10% dell'ordine
            }
        }
        break;
    }
    case 3 :
    {

        scelta_visualizza_elenco(NM);
        printf("Inserisci il numero corrispondente alla destinazione desiderata.\t");
        fflush(stdin);
        scanf("%d", &destinazione);
        fflush(stdin);

        int durata_comp_economica=0;
        int costo_comp_breve=0;
        int costo_comp_economica=dijkstra_costo(G, partenza, destinazione, 1, 1, &durata_comp_economica);
        if (costo_comp_economica==2147483647)
        {
            printf("Ci dispiace, questo viaggio non e' disponibile.\n");
            return;
        }
        printf("La tratta piu' economica ti costera' %d euro e durera' %d minuti.\n", costo_comp_economica, durata_comp_economica);

        int durata_comp_breve=dijkstra_durata(G, partenza, destinazione, 1, &costo_comp_breve);
        printf("La tratta piu' breve ti costera' %d euro e durera' %d minuti.\n\n", costo_comp_breve, durata_comp_breve);

        if (costo_comp_economica==costo_comp_breve)
        {
            printf("Come puoi osservare, la due migliori tratte disponibili hanno lo stesso prezzo, scegli quella con meno scali per\n"
                   "un viaggio piu' confortevole o l'altra se ti senti un vero turista!\nQualora siano previsti gli stessi scali scegliere la prima o seconda sara' indifferente. Grazie!\n\n");
        }

        printf("Inserisci\n1 per la tratta piu' economica\n2 per la tratta piu' breve\n3 per annullare.\nRicorda che "
               "piu' viaggi piu' accumulerai punti per fantastici sconti per i tuoi prossimi voli!\t");
        fflush(stdin);
        scanf("%d", &scelta2);
        fflush(stdin);
        switch (scelta2)
        {

        case 1:

        {
            if ((Cliente)->punti >0)
            {
                printf("\nTi ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                fflush(stdin);
                scanf("%d", &scelta);
                fflush(stdin);
                if (scelta)
                {
                    costo_comp_economica=costo_comp_economica-(Cliente)->punti;

                    (Cliente)->punti=0;
                }
            }
            (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp_economica, durata_comp_economica);
            printf("Prenotazione confermata e registrata!\n");
            AggiornaContatore(NM,destinazione);
            (Cliente)->punti=(Cliente)->punti + (costo_comp_economica/100)*10; //il 10% dell'ordine
            break;
        }
        case 2:
        {

            if ((Cliente )->punti >0)
            {
                printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                fflush(stdin);
                scanf("%d", &scelta);
                fflush(stdin);
                if (scelta)
                {
                    costo_comp_breve=costo_comp_breve-(Cliente)->punti;

                    (Cliente)->punti=0;
                }
            }
            (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp_breve,durata_comp_breve);
            printf("Prenotazione confermata e registrata!\n");
            AggiornaContatore(NM,destinazione);
            (Cliente)->punti=(Cliente)->punti + (costo_comp_breve/100)*10; //il 10% dell'ordine
            break;
        }

        break;

        }


    }

    case 4:

    {

        return;
    }

    }

}

