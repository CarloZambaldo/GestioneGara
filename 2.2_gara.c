/*
    GARA SPORTIVA:
        il programma ottine in input dati generali dei concorrenti,
        consente di inserire un punteggio dato dai giudici
        stampa una classifica generale
*/
// da fare: salvare tutto su file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_atleti 10
#define n_giudici 4
#define lungh_codice 5
#define ID_luogo 25

typedef struct situazione_atleta {
    char codice[lungh_codice]; 
    int points_giudice[n_giudici];
    int points;
    char provenienza[ID_luogo]; 
    int eta;
} dancer;

void inizializza(struct situazione_atleta ballerine[]);
int esiste(char atleta[], struct situazione_atleta ballerine[]);
void nuovoAtleta(struct situazione_atleta ballerine[], int numero);
void stampaTUTTO(struct situazione_atleta ballerine[]);
void inserisciPunti(struct situazione_atleta ballerine[], int numero);
void puntiAtleta(struct situazione_atleta ballerine[], int numero);
void puntiGiudice(struct situazione_atleta ballerine[], int id);
void classifica(struct situazione_atleta ballerine[]);

// menu
int opzioni(){
    int scelta;
    system("PAUSE");
    system("CLS");
    printf("\nScegliere l'operazione da svolgere:\n");
    printf("1 - Inserire i punteggi dell'atleta\n");
    printf("2 - Visualizzare i punteggi dell'atleta\n");
    printf("3 - Visualizzare i punteggi per giudice\n");
    printf("4 - Visualizza tutto\n");
    printf("5 - Stampa classifica\n");
    printf("0 - Esci\n");

    printf("\ninserire il numero della scelta: ");
    scanf("%d", &scelta);
    printf("\n\n");
    return scelta;
}

// -------------------------------------------------------------------------------------------

int main(){
    printf("Inizializzo");
    char num[lungh_codice];
    dancer table_ballerine[n_atleti];
    inizializza(table_ballerine);

    // inserimento codici atleti, controlla se esistono gia'
    printf("\nInserire i codici degli atleti:\n");
    int i=0;
    for(i=0; i<n_atleti; i++){
        do{
            printf("Inserire il codice dell'atleta n.%d: ", i+1);
            scanf("%s", num);  

            if(strlen(num)<lungh_codice){
                printf("\nIl codice %s e' troppo corto (ha solo %d caratteri su %d necessari)!\n", num, strlen(num), lungh_codice);
            }
            if(esiste(num, table_ballerine)!=0){
                printf("\nL'atleta con il codice %s esiste gia'!\n", num);
            }
        } while (esiste(num, table_ballerine) != 0 || strlen(num)<lungh_codice);     // controllo se esiste gia' l'atleta
        
        // se il codice e' diverso dalle altre ballerine lo inserisco e chiedo altre informazioni
        int j=0;
        for(j=0; j<lungh_codice; j++){
            table_ballerine[i].codice[j]=num[j];
        }
        nuovoAtleta(table_ballerine, i);
        printf("\n - \n");
    }

    int scelta;
    do{
        scelta = opzioni();
        switch(scelta){
            case 0:
            {
                printf("Arrivederci!\n");
                break;
            }
            
            case 1:     // Inserire il punteggio dell'atleta
            {
                printf("Di quale atleta desideri inserire il punteggio? ");
                scanf("%s", num);
                int trovato=esiste(num, table_ballerine);
                if(trovato!=0){
                    inserisciPunti(table_ballerine, (trovato-1)); // -1 poiche' avevo aggiunto +1 nella funzione per lasciare lo 0 nel solo caso fosse assente
                } else {
                    printf("Non ho trovato l'atleta cercato.\n");
                }
                scelta = 4;
                break;   
            }
                
            case 2:     // Visualizzare  i punteggi dell'atleta
            {
                printf("Di quale atleta desideri visualizzare il punteggio? ");
                scanf("%s", num);
                int trovato=esiste(num, table_ballerine);
                if(trovato!=0){
                    puntiAtleta(table_ballerine, (trovato-1)); // -1 poiche' avevo aggiunto +1 nella funzione per lasciare lo 0 nel solo caso fosse assente
                } else {
                    printf("Non ho trovato l'atleta cercato.\n");
                }
                scelta = 4;
                break;
            }
                

            case 3:     // Visualizzare i punteggi per giudice
            {
                int ch;
                printf("Numero del giudice corrispondente: ");
                scanf("%d", &ch);
                ch--;   // considero che l'utente scriva 1 ma intenda il primo (a cui corrisponde 0)
                if(ch>=0 && ch<n_giudici){
                    puntiGiudice(table_ballerine, ch); // -1 poiche' avevo aggiunto +1 nella funzione per lasciare lo 0 nel solo caso fosse assente
                } else {
                    printf("Non ho trovato il giudice cercato.\n");
                }
                scelta = 4;
                break;
            }
                
            case 4:     // Visualizza tutto
            {
                stampaTUTTO(table_ballerine);
                break;
            }
                
            case 5:     // Stampa classifica
            {
                classifica(table_ballerine);
                break;
            }
                
            default:
            {
                printf("Errore Fatale!\nPremi invio per ripristinare.");
                scanf("");
                scelta=4;
                break;
            }     
        }
    } while (scelta != 0);
    
    return 0;
}

// ---------------------------------------------------------------------------------

// inizializza
void inizializza(struct situazione_atleta ballerine[]){
    int i=0, j=0;
    for(i=0; i<n_atleti; i++){
        printf(".");

        for(j=0; j<lungh_codice; j++){
            ballerine[i].codice[j]=' ';
        }
        ballerine[i].codice[lungh_codice]='\0';   // inserisco il carattere terminatore

        for(j=0; j<ID_luogo-1; j++){
            ballerine[i].provenienza[j]=' ';
        }
        ballerine[i].provenienza[ID_luogo]='\0'; // carattere terminatore

        ballerine[i].eta=0;

        for(j=0; j<n_giudici; j++){
            ballerine[i].points_giudice[j]=0;
        }

        ballerine[i].points=0;
    }
    printf(" Fine.\n");
}


// controllo se esiste gia' l'atleta, in caso affermativo ritorno la posizione +1 , se non esiste 0
int esiste(char atleta[], struct situazione_atleta ballerine[]){
    int i=0, j, k=0;
    for(i=0; i<n_atleti; i++){
        k=0;
        for(j=0; j<lungh_codice; j++){
            if(atleta[j]==ballerine[i].codice[j]){      // stranamente strcmp() non funziona a causa di valori in eccesso alla fine della stringa
                k++;
            }
        }
        if(k==lungh_codice){
          return (i+1);  
        }
    }
    return 0;
}

// inserimento informazioni aggiuntive sull'atleta (dopo aver controllato se non esiste gia')
void nuovoAtleta(struct situazione_atleta ballerine[], int numero){
    printf("Inserire i dati dell'atleta %s:\n", ballerine[numero].codice);
    printf("Nazionalita': ");
    scanf("%s", &(ballerine[numero].provenienza));
    printf("Eta' atleta: ");
    scanf("%d", &(ballerine[numero].eta));
}

// inserisco il punteggio dell'atleta (viene passata la posizione dell'atleta dopo averlo cercato con esiste())
void inserisciPunti(struct situazione_atleta ballerine[], int numero){
    int i;
    char ohcazzo='j';
    printf("[Il punteggio e' un valore intero, numeri reali vengono troncati]\n");
    if(ballerine[numero].points!=0){
        do{
            printf("Attenzione! E' gia' presente un punteggio per questo atleta, volete sovrascriverlo? [y/n]");
            scanf("%c",&ohcazzo);
        } while (ohcazzo!='y' && ohcazzo!='n');
    }
    if(ohcazzo=='y' || ohcazzo=='j'){
        for(i=0; i<n_giudici; i++){   
            printf("Punteggio giudice %d: ", i+1);
            scanf("%d", &(ballerine[numero].points_giudice[i]));
            ballerine[numero].points += ballerine[numero].points_giudice[i];
        }
    } else {
        printf("Non ho modificato il valore.\n");
    }
    
}


// stampo il punteggio di un atleta solo
void puntiAtleta(struct situazione_atleta ballerine[], int numero){
    printf("Il punteggio di %s e': %d.\n\n", ballerine[numero].codice, ballerine[numero].points);
}


// stampo i punteggi che ha dato il giudice id
void puntiGiudice(struct situazione_atleta ballerine[], int id){
    printf("\nIl giudice %d ha dato i seguenti punteggi: \n", id+1);
    int i=0, som=0;
    printf(" Punti\tAtleta\n");
    for(i=0; i<n_atleti; i++){
        printf("  %d \t%s\n", ballerine[i].points_giudice[id], ballerine[i].codice);
        som+=ballerine[i].points_giudice[id];
    }
    printf("\n  Per un totale di: %d punti.\n", som);
}


// genero e stampo la classifica degli atleti
void classifica(struct situazione_atleta ballerine[]){
    int voti[n_atleti];  // la prima riga e' dedicata ai punteggi, la seconda a quante volte compaiono
    int i,j;
    for(i=0; i<n_atleti; i++){
        voti[i]=ballerine[i].points;
    }

    // riordino i punteggi (dal piu' alto al piu' basso)
    for(j=0; j<n_atleti; j++){
        for(i=0; i<n_atleti; i++){
            if(voti[i]<voti[i+1]){
                voti[i]+=voti[i+1];
                voti[i+1]=voti[i]-voti[i+1];
                voti[i]-=voti[i+1];  
            }
        }
    }

    // elimino i punteggi ripetuti
    int L=n_atleti;
    i=1;
    do{
        if (voti[i]==voti[i-1]){
            for(j=i; j<L; j++)
                voti[j-1]=voti[j];
            L--; 
            voti[L]=-1;
	    } else {
            i++;
        } 
    } while (i<L);
    
    // controllo chi ha il punteggio piu' alto e scrivo la classifica
    printf("Posiz\tCodice\tPunti\n");
    int posizione=0;
    for(i=0; i<L; i++){
        for(j=0; j<n_atleti; j++){
            if(voti[i]==ballerine[j].points){
                printf(" %d\t%s\t%d\n", posizione, ballerine[j].codice, ballerine[j].points);
            }
        }
        posizione++;
    }
}


// stampo tutto quello che so
void stampaTUTTO(struct situazione_atleta ballerine[]){
    int i=0;
    for(i=0; i<n_atleti; i++){
        printf("Atleta %s\n", ballerine[i].codice);
        printf(" Nazionalita': %s\n", ballerine[i].provenienza);
        printf(" Eta': %d\n", ballerine[i].eta);
        printf(" Punteggio totale: %d\n", ballerine[i].points);
        int j=0;
        for(j=0; j<n_giudici; j++){
            printf("   Punteggio dato dal giudice %d: %d\n", j+1, ballerine[i].points_giudice[j]);
        }
        printf("\n - - - - - - - - - - - - \n\n");
    }
}