#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "generaSudoku.cpp"
#include "partita.cpp"
#include "gestioneFile.cpp"
#include "costanti.h"

using namespace std;

void stampaSudoku(int mat[DIM][DIM]){
    //output prima riga
    cout << RED << "+-------------------------+\n";
    //ciclo che si ripete per le righe
    for (int i = 0; i < 9; ++i) {
        //output primo carattere riga
        cout << RED << "| ";
        // ciclio che si ripete per il numero di colonne
        for (int j = 0; j < 9; ++j) {
            // output divisore ogni 3 colonne tranne la prima
            if (j % 3 == 0 && j != 0) cout << RED << "|| ";
            // il numero della matrice viene stampato in viola se e' pari a zero e quindi va sostituito, o blu se non e' zero e non va sostituito
            if (mat[i][j] == 0) {
                cout << PURPLE << mat[i][j] << " ";
            } else {
                cout << BLUE << mat[i][j] << " ";
            }
        }
        //output ultimo carattere riga
        cout << RED << "|\n";
        //output divisore ogni 3 righe tranne l'ultima
        if (i % 3 == 2 && i != 8) {
            cout << RED << "|-------++-------++-------|\n";
        }
    }
    //output ultima riga
    cout << RED << "+-------------------------+\n" << RESET;
}

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
            stampaSudoku(sudoku); // viene stampato il sudoku
            inputMossa(sudoku); // viene chiesta in input la mossa
            salvaPartita(sudoku, soluzioneSudoku); // viene salvata la partita su file
            if(!partitaTerminata(sudoku)/* controllo se il sudoku e' sbagliato in questo modo non viene mostrato quando finisce il gioco con il sudoku corretto */){
                if (exitPartita() /* chiedo all'utente se vuole uscire dal gioco */) {
                    return; // torno al main
                }
            }
        }
        stampaSudoku(sudoku); // viene stampato il sudoku finito
        aggiornaStorico(verificaVittoria(soluzioneSudoku, sudoku)); // viene aggiornato lo storico
    } else {
        //cpu
        stampaSudoku(sudoku); // viene stampato il sudoku
        risolviSudoku(sudoku, true); // viene risolto il sudoku

        if (partitaTerminata(sudoku) /* controllo che il sudoku sia completo */) {
            stampaSudoku(sudoku); // viene stampato il sudoku completo

            salvaPartita(sudoku, soluzioneSudoku); // viene salvata la partita
        } else {
            cout << RED << "non e' stato possibile risolvere il sudoku \n" << RESET; // output in caso che il sudoku non e' risolto
        }
        // non si va ad aggiornare lo storico perché è dell'utente.
    }
}

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