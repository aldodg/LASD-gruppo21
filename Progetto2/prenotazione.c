#include "prenotazione.h"
#include "stdinutils.h"

#define MIN_VOLI_PER_GETTONATI 2


Prenotati insertHead(Prenotati P, int partenza,int destinazione, int peso)
{

    Prenotati X = (Prenotati )malloc(sizeof(struct voliPrenotati));
    (X)->partenza = partenza;
    (X)->destinazione = destinazione;
    (X)->peso=peso;
    (X)->next = P;

    P=(X);

    return P;
}


void printVoliPrenotati(Prenotati P, int i)
{
    if (P != NULL)
    {
        printf("%d) %d -> %d ", i, (P)->partenza, (P)->destinazione);
        printVoliPrenotati(P->next, i+1);
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

int esistono_mete_gettonate (Nomi_Luoghi NM)
{

    int esistono_mete_gettonate=0;
    while(NM!=NULL )
    {

        if ((NM)->contatore_voli>0);
        {
            printf("id: %d - %s con %d visite totali ricevute\n",(NM)->id,(NM)->nome_luogo, (NM)->contatore_voli);
            esistono_mete_gettonate=1;
        }
        NM=(NM)->next;

    }

    return esistono_mete_gettonate;
}

void prenotaVolo(Graph G, Customers Cliente, char * username, Nomi_Luoghi NM)
{

    int scelta;
    int partenza, destinazione, costo_comp=0, durata_comp=0, scelta2;
    //int  destinazione_gia_scelta=0;

    while( Cliente!=NULL && strcmp((Cliente)->user,username ))
    {
        Cliente= (Cliente)->next;
    }

    scelta_visualizza_elenco(NM);
    printf("Per favore inserisci il numero corrispondente al luogo di partenza.\t");
    fflush(stdin);
    scanf("%d", &partenza);

    printf("Inserisci\n1 per la tratta piu' economica in assoluto da dove vuoi partire\n2 per le mete piu' gettonate\n3 per inserire manualmente una destinazione\n4 per annullare\nScegli:\t");
    fflush(stdin);
    scanf("%d", &scelta);
    switch (scelta)
    {

    case 1:
    {
        destinazione=dijkstra_costo(G, partenza, 0, 0, 0);
        costo_comp=dijkstra_costo(G, partenza, destinazione, 1, 1);
        printf("La tratta piu' economica ti costera' %d e sarebbe %d.\n", costo_comp, destinazione);
        stampa_lista_nomi(NM);
        if ((Cliente )->punti >0)
        {
            printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
            fflush(stdin);
            scanf("%d", &scelta);
            //if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
            if (scelta)
            {
                costo_comp=costo_comp-(Cliente)->punti;

                (Cliente)->punti=0;
            }
        }
        (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp);
        printf("Prenotazione confermata e registrata!\n");
        (Cliente)->punti=(durata_comp/100)*10; //il 10% dell'ordine
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
            printf("\nVuoi andare in uno dei luoghi piu gettonati[1\\0]?\t");
            fflush(stdin);
            scanf("%d", &scelta);
            //if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
            if (scelta)
            {
                printf("Inserisci il numero corrispondente alla destinazione desiderata.\t");
                fflush(stdin);
                //destinazione=readint();
                //destinazione_gia_scelta=1;
                scanf("%d", &destinazione);
            }

            costo_comp=dijkstra_costo(G, partenza, destinazione, 1, 1);
            printf("La tratta piu' economica ti costera' %d.\n", costo_comp);

            if ((Cliente )->punti >0)
            {
                printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                fflush(stdin);
                scanf("%d", &scelta);
                //if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
                if (scelta)
                {
                    costo_comp=costo_comp-(Cliente)->punti;

                    (Cliente)->punti=0;
                }
            }
            (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp);
            AggiornaContatore(&NM,destinazione);
            printf("Prenotazione confermata e registrata!\n");
            (Cliente)->punti=(durata_comp/100)*10; //il 10% dell'ordine
        }
        break;
    }
    case 3 :
    {

        scelta_visualizza_elenco(NM);
        printf("Inserisci il numero corrispondente alla destinazione desiderata.\t");
        fflush(stdin);
        scanf("%d", &destinazione);

        costo_comp=dijkstra_costo(G, partenza, destinazione, 0, 1);
        printf("La tratta piu' economica ti costera' %d.\n", costo_comp);
        durata_comp=dijkstra_durata(G, partenza, destinazione, 1);
        printf("La tratta piu' breve ti costera' %d.\n", durata_comp);

        printf("Inserisci\n1 per la tratta piu' economica\n2 per la tratta piu' breve\n3 per annullare.\nRicorda che "
               "piu' il viaggio sara' costoso piu' accumulerai punti per fantastici sconti per i tuoi prossimi voli!\t");
        fflush(stdin);
        scanf("%d", &scelta2);
        switch (scelta2)
        {

        case 1:

        {
            if ((Cliente)->punti >0)
            {
                printf("\nTi ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                fflush(stdin);
                scanf("%d", &scelta);
                //if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
                if (scelta)
                {
                    costo_comp=costo_comp-(Cliente)->punti;

                    (Cliente)->punti=0;
                }
            }
            //printf("annagg ttcos");
            (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, costo_comp);
            //printf("hhhfuh %d %d", (Cliente)->elenco_prenotazioni->destinazione);
            printf("Prenotazione confermata e registrata!\n");
            (Cliente)->punti=(costo_comp/100)*10; //il 10% dell'ordine
            break;
        }
        case 2:
        {

            if ((Cliente )->punti >0)
            {
                printf("\n Ti ricordiamo che hai accumulato %d punti sui tuoi viaggi.\nVuoi usarli?[1\\0]?\t", (Cliente)->punti);
                fflush(stdin);
                scanf("%d", &scelta);
               // if (strcmp (scelta,"S")==0 || strcmp (scelta, "s")==0)
                if (scelta)
                {
                    durata_comp=durata_comp-(Cliente)->punti; //ZOZZIMMA DA SISTEMARE

                    (Cliente)->punti=0;
                }
            }
            (Cliente)->elenco_prenotazioni=insertHead((Cliente)->elenco_prenotazioni, partenza, destinazione, durata_comp);
            printf("Prenotazione confermata e registrata!\n");
            (Cliente)->punti=(durata_comp/100)*10; //il 10% dell'ordine
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


void visualizza_prenotazioni_effettuate(char *username, Customers Utente)
{

    //int i=1;
    //printf("user: %s", username);
    //printf("user: %s", (Utente)->user);
    //printf ("uallr %d ", strcmp((Utente)->user, username));
    while (Utente!=NULL && strcmp((Utente)->user, username))
    {
        Utente=(Utente)->next;
    }
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

int controllaCredenziali(Customers L,char * username, char * password)
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

int TrovaMetaGettonata(Nomi_Luoghi NM){




    int max=(NM)->contatore_voli;
    int metagettonata=0;
    while(NM!=NULL )
    {

        if ((NM)->contatore_voli>max);
        {
            //printf("id: %d - %s con %d visite totali ricevute\n",(NM)->id,(NM)->nome_luogo, (NM)->contatore_voli);
            //esistono_mete_gettonate=1;
            max=(NM)->contatore_voli;
        }
        NM=(NM)->next;

    }

    while(NM!=NULL)
    {
    if(NM->contatore_voli==max)  {

        metagettonata=NM->id;
    }

    }

    return metagettonata;
}

void AggiornaContatore(Nomi_Luoghi * NM, int id)
{

   while(NM!=NULL){
    if((*NM)->id==id){
    (*NM)->contatore_voli++;

    }

    (*NM)->next;
   }

}
