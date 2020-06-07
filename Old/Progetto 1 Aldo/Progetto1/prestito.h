#define DIM 100
#define MATR 10
#include "deposito_libri.h"


Node_Sospese *controlla_richieste_sospese (Node *, Node_Sospese *);
Node_Sospese* chiedi_prestito(Node *, char matricola[], Node_Sospese*);
void stampa_lista_richieste(Node_Sospese *);
Node_Sospese *ins_coda_richiesta(Node_Sospese *top_richieste, char titolo_tmp[],  char matricola_richiedente_tmp[]);
