#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "generaSudoku.cpp"
#include "partita.cpp"
#include "gestioneFile.cpp"
#include "costanti.h"

using namespace std;

// Funzione per stampare una griglia di Sudoku 9x9 con i numeri forniti nella matrice 'mat'.
// L'output della griglia è colorata in colori diversi
// Lo 0 che indica una cella vuota è colorato in viola
// Il numero inserito correttamente è colorato in blu
// Il numero inserito non corretto è colorato in rosso
void stampaSudoku(int mat[DIM][DIM], bool soluzione){
    //input file
    int soluzioneSudoku[DIM][DIM];
    caricaSoluzione(soluzioneSudoku);
    //output prima riga
    cout << GREEN << "    0 1 2    3 4 5    6 7 8\n";
    cout << RED << "  " << "+-------------------------+\n";
    //ciclo che si ripete per le righe
    for (int i = 0; i < 9; ++i) {
        //output primo carattere riga
        cout << GREEN << i << RED << " | ";
        // ciclio che si ripete per il numero di colonne
        for (int j = 0; j < 9; ++j) {
            // output divisore ogni 3 colonne tranne la prima
            if (j % 3 == 0 && j != 0) cout << RED << "|| ";
            // il numero della matrice viene stampato in viola se e' zero o blu se non e' zero e non va sostituito
            if (mat[i][j] == 0) {
                cout << PURPLE << mat[i][j] << " ";
            }  else if(soluzione && mat[i][j] != soluzioneSudoku[i][j]){
                cout << RED << mat[i][j] << " ";
            } else {
                cout << BLUE << mat[i][j] << " ";
            }
        }
        //output ultimo carattere riga
        cout << RED << "| " << GREEN << i << RED << "\n";
        //output divisore ogni 3 righe tranne l'ultima
        if (i % 3 == 2 && i != 8) {
            cout << RED << "  " <<  "|-------++-------++-------|\n";
        }
    }
    //output ultima riga
    cout << RED << "  " << "+-------------------------+\n" << RESET;
    cout << GREEN << "    0 1 2    3 4 5    6 7 8\n";
}

// Funzione per avviare una partita di Sudoku.
// Questa funzione gestisce il flusso di gioco per una partita di Sudoku, consentendo al giocatore di giocare o alla CPU di risolvere il Sudoku.
// Se il parametro 'partitaNuova' è true, viene inizializzata una nuova partita con una griglia generata casualmente.
// Se 'partitaNuova' è false, viene caricata una partita esistente da file.
void avviaPartita(bool partitaNuova) {
    int soluzioneSudoku[DIM][DIM];
    int sudoku[DIM][DIM];

    if (partitaNuova) {
        initMatrice(soluzioneSudoku); // viene inizializzata a 0 la matrice con la soluzione del sudoku
        risolviSudoku(soluzioneSudoku, false); // viene generata la soluzione del sudoku

        int num = inputDifficolta(); // viene inserita presa in input la difficolta'

        do {
            copiaMatrice(sudoku, soluzioneSudoku); // viene copiata la matrice con la soluzione in quella con il sudoku
            cavaNumeri(sudoku, num); // toglie i numeri dal sudoku (num = difficolta')
        } while (!verificaSudoku(sudoku)); // viene verificato che il sudoku ha una sola soluzione
    } else {
        caricaPartita(sudoku, soluzioneSudoku); // viene caricato il sudoku e la soluzione da file
        // controllo che il sudoku non sia gia' risolto
        if(verificaVittoria(soluzioneSudoku, sudoku)){
            cout << RED << "Non e' possibile caricare la partita in quanto questa e' finita\n" << RESET;
            return;
        }
    }

    if (sceltaGiocatore()/* viene scelto il giocatore, player o cpu */) {
        //player
        while (!partitaTerminata(sudoku)/* finche' la partita non e' terminata continua il ciclo */) {
            stampaSudoku(sudoku, false); // viene stampato il sudoku
            inputMossa(sudoku); // viene chiesta in input la mossa
            salvaPartita(sudoku, soluzioneSudoku); // viene salvata la partita su file
            if(!partitaTerminata(sudoku)/* se la partita è terminata non chiede di uscire */){
                if (exitPartita() /* chiedo all'utente se vuole uscire dal gioco */) {
                    return; // torno al main
                }
            }
        }
        stampaSudoku(sudoku, true); // viene stampato il sudoku finito
        aggiornaStorico(verificaVittoria(soluzioneSudoku, sudoku)); // viene aggiornato lo storico
        outputEventualiErrori(soluzioneSudoku, sudoku);
    } else {
        //cpu
        stampaSudoku(sudoku, false); // viene stampato il sudoku
        risolviSudoku(sudoku, true); // viene risolto il sudoku

        if (partitaTerminata(sudoku) /* controllo che il sudoku sia completo */) {
            stampaSudoku(sudoku, false); // viene stampato il sudoku completo

            salvaPartita(sudoku, soluzioneSudoku); // viene salvata la partita
        } else {
            // output in caso che il sudoku non e' risolto
            cout << RED << "non e' stato possibile risolvere il sudoku \n" << RESET;
        }
        // non si va ad aggiornare lo storico perché è dell'utente.
    }
}

// Funzione per visualizzare il menu del gioco Sudoku e ottenere l'opzione scelta dall'utente.
// Il menu mostra le seguenti opzioni:
// 1.  Avvia una partita
// 2.  Carica una partita
// 3.  Vedere le regole
// 4.  Storico delle partite
// 5.  Esci dal gioco
// L'utente è tenuto a inserire un'opzione valida compresa tra 1 e 5.
int menu() {
    int min = 1, max = 5, opzione;

    cout << YELLOW;
    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Vedere le regole \n";
    cout << "4. Storico delle partite \n";
    cout << "5. Esci dal gioco \n";
    cout << RESET;

    do{
        cout << ORANGE <<  "Inserisci un'opzione: " << RESET;
        cin >> opzione;

        if (opzione < min || opzione > max) {
            cout << RED << "Input errato! \n" << RESET;
        }
    } while (opzione < min || opzione > max);

    return opzione;
}

// Funzione principale del gioco Sudoku.
// Questa funzione gestisce il menu principale del gioco, consentendo all'utente di avviare una partita, caricare una partita esistente,
// visualizzare le regole del gioco o consultare lo storico delle partite.
int main () {
    creazioneFile(); //verifica se ci sono i file e in caso li crea
    srand(time(NULL));

    while (true) {
        int opzione = menu();

        switch (opzione) {
            case 1:
                //Avvia una partita
                avviaPartita(true);
                break;
            case 2:
                //Carica una partita
                avviaPartita(false);
                break;
            case 3:
                //Vedere le regole
                stampaRegole();
                break;
            case 4:
                //Storico delle partite
                stampaStorico();
                break;
            case 5:
                //Esci dal gioco
                return 0;
        }
    }
}