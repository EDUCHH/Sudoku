#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "generaSudoku.cpp"
#include "partita.cpp"
#include "gestioneFile.cpp"
#include "costanti.h"

using namespace std;

/**
 * @brief Stampa una griglia di Sudoku 9x9 utilizzando i numeri forniti nella matrice 'mat'.
 * L'output della griglia è colorato come segue:
 * - Le celle vuote (indicate da 0) sono colorate in viola.
 * - I numeri corretti sono colorati in blu.
 * - I numeri errati sono colorati in rosso.
 *
 * @param mat La matrice 9x9 contenente i numeri del Sudoku.
 * @param soluzione Indica se la matrice rappresenta una soluzione corretta.
 * @param modificheSudoku La matrice 9x9 che tiene traccia delle modifiche apportate al Sudoku.
 */
void stampaSudoku(int mat[DIM][DIM], bool soluzione, int modificheSudoku[DIM][DIM]){
    // Input file.
    int soluzioneSudoku[DIM][DIM];
    caricaSoluzione(soluzioneSudoku);
    // Output prima riga.
    cout << GREEN << "    0 1 2    3 4 5    6 7 8\n";
    cout << RED << "  " << "+-------------------------+\n";
    // Ciclo che si ripete per le righe.
    for (int i = 0; i < 9; ++i) {
        // Output primo carattere riga.
        cout << GREEN << i << RED << " | ";
        // Ciclio che si ripete per il numero di colonne.
        for (int j = 0; j < 9; ++j) {
            // Output divisore ogni 3 colonne tranne la prima.
            if (j % 3 == 0 && j != 0) cout << RED << "|| ";
            // Il numero della matrice viene stampato in viola se è zero o blu se non è zero e non va sostituito.
            if (mat[i][j] == 0) {
                cout << PURPLE << mat[i][j] << " ";
            } else if(modificheSudoku[i][j] == 1){
                cout << ORANGE << mat[i][j] << " ";
            } else if(soluzione && mat[i][j] != soluzioneSudoku[i][j]){
                cout << RED << mat[i][j] << " ";
            } else {
                cout << BLUE << mat[i][j] << " ";
            }
        }
        // Output ultimo carattere riga.
        cout << RED << "| " << GREEN << i << RED << "\n";
        // Output divisore ogni 3 righe tranne l'ultima.
        if (i % 3 == 2 && i != 8) {
            cout << RED << "  " <<  "|-------++-------++-------|\n";
        }
    }
    // Output ultima riga.
    cout << RED << "  " << "+-------------------------+\n" << RESET;
    cout << GREEN << "    0 1 2    3 4 5    6 7 8\n";
}

/**
 * @brief Gestisce il flusso di gioco per una partita di Sudoku, consentendo al giocatore di giocare o alla CPU di risolvere il Sudoku.
 * Se il parametro 'partitaNuova' è true, viene inizializzata una nuova partita con una griglia generata casualmente.
 * Se 'partitaNuova' è false, viene caricata una partita esistente da file.
 *
 * @param partitaNuova Indica se si tratta di una nuova partita o di una partita esistente da caricare.
 */
void avviaPartita(bool partitaNuova) {
    int soluzioneSudoku[DIM][DIM];
    int sudoku[DIM][DIM];

    // 0: Numero non inserito dall'utente.
    // 1: Numero inserito dall'utente.
    int modificheSudoku[DIM][DIM];
    int suggerimentiDisponibili = 0;

    if (partitaNuova) {
        initMatrice(soluzioneSudoku); // Viene inizializzata a 0 la matrice con la soluzione del sudoku.
        initMatrice(modificheSudoku); // Viene inizializzata a 0 la matrice con le modifiche del sudoku.
        risolviSudoku(soluzioneSudoku, false); // Viene generata la soluzione del sudoku.

        suggerimentiDisponibili = inputDifficolta(); // Viene inserita presa in input la difficoltà.

        do {
            copiaMatrice(sudoku, soluzioneSudoku); // Viene copiata la matrice con la soluzione in quella con il sudoku.
            cavaNumeri(sudoku, suggerimentiDisponibili); // Toglie i numeri dal sudoku in base alla difficoltà.
        } while (!verificaSudoku(sudoku)); // Viene verificato che il sudoku ha una sola soluzione.

        suggerimentiDisponibili /= 10;
    } else {
        caricaPartita(sudoku, soluzioneSudoku, modificheSudoku, suggerimentiDisponibili); // Viene caricato il sudoku e la soluzione da file.
        // Controllo che il sudoku non sia già risolto.
        if(verificaVittoria(soluzioneSudoku, sudoku)){
            cout << RED << "Non e' possibile caricare la partita in quanto questa e' finita\n" << RESET;
            return;
        }
    }

    if (sceltaGiocatore()/* Viene scelto il giocatore, player o cpu */) {
        // Player.
        cout << GREEN << "Ci sono "<< RESET << suggerimentiDisponibili << GREEN << " suggerimenti disponibili!" << RESET << '\n';
        salvaPartita(sudoku, soluzioneSudoku, modificheSudoku, suggerimentiDisponibili); // Viene salvata la partita su file.

        while (!partitaTerminata(sudoku)/* Finché la partita non è terminata continua il ciclo. */) {
            stampaSudoku(sudoku, false, modificheSudoku); // Viene stampato il sudoku.
            
            int returnInputMossa = inputMossa(sudoku, modificheSudoku); // Viene chiesta in input la mossa.
            if(returnInputMossa == 1) {
                return;
            } else if(returnInputMossa == 2) {
                if(suggerimentiDisponibili > 0){
                    if(suggerimento(sudoku, soluzioneSudoku)){
                        suggerimentiDisponibili--;
                    }
                    if(suggerimentiDisponibili == 0){
                        cout << RED << "Suggerimenti rimanenti: "<< RESET << suggerimentiDisponibili << '\n';
                    } else{
                        cout << GREEN << "Suggerimenti rimanenti: "<< RESET << suggerimentiDisponibili << '\n';
                    }
                    
                } else{
                    cout << RED << "Non ci sono suggerimenti disponibili!" << RESET << '\n';
                }
            }

            salvaPartita(sudoku, soluzioneSudoku, modificheSudoku, suggerimentiDisponibili); // Viene salvata la partita su file.
        }
        stampaSudoku(sudoku, true, modificheSudoku); // Viene stampato il sudoku finito.
        aggiornaStorico(verificaVittoria(soluzioneSudoku, sudoku)); // Viene aggiornato lo storico.
        outputEventualiErrori(soluzioneSudoku, sudoku);
    } else {
        // CPU.
        stampaSudoku(sudoku, false, modificheSudoku); // Viene stampato il sudoku.
        risolviSudoku(sudoku, true); // Viene risolto il sudoku.

        if (partitaTerminata(sudoku) /* Controllo che il sudoku sia completo. */) {
            stampaSudoku(sudoku, false, modificheSudoku); // Viene stampato il sudoku completo.

            salvaPartita(sudoku, soluzioneSudoku, modificheSudoku, suggerimentiDisponibili); // Viene salvata la partita.
        } else {
            // Output in caso che il sudoku non è risolto.
            cout << RED << "non e' stato possibile risolvere il sudoku \n" << RESET;
        }
        // Non si va ad aggiornare lo storico perché è dell'utente.
    }
}

/**
 * @brief Funzione per visualizzare il menu del gioco Sudoku e ottenere l'opzione scelta dall'utente.
 * Il menu mostra le seguenti opzioni:
 * 1. Avvia una partita
 * 2. Carica una partita
 * 3. Vedere le regole
 * 4. Storico delle partite
 * 5. Resetta lo storico
 * 6. Esci dal gioco
 * L'utente è tenuto a inserire un'opzione valida compresa tra 1 e 5.
 *
 * @return L'opzione scelta dall'utente.
 */
int menu() {
    int min = 1, max = 6, opzione;

    cout << YELLOW;
    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Vedere le regole \n";
    cout << "4. Storico delle partite \n";
    cout << "5. Resetta lo storico \n";
    cout << "6. Esci dal gioco \n";
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

/**
 * @brief Questa funzione gestisce il menu principale del gioco, consentendo all'utente di avviare una partita, caricare una partita esistente,
 * visualizzare le regole del gioco o consultare lo storico delle partite.
 *
 * @return 0 se il programma è terminato correttamente.
 */
int main () {
    stampaFile("asciiArt.txt"); // Stampa il file ASCII art all'avvio del gioco.
    creazioneFile(); // Verifica se ci sono i file e li crea se necessario.
    srand(time(NULL)); // Inizializza il generatore di numeri casuali.

    while (true) {
        int opzione = menu(); // Mostra il menu e ottiene l'opzione scelta dall'utente.

        switch (opzione) {
            case 1:
                // Avvia una partita.
                avviaPartita(true);
                break;
            case 2:
                // Carica una partita.
                avviaPartita(false);
                break;
            case 3:
                // Visualizza le regole del gioco.
                stampaFile("regole.txt");
                break;
            case 4:
                // Mostra lo storico delle partite.
                stampaStorico();
                break;
            case 5:
                // Resetta lo storico delle partite.
                resetStorico();
                break;
            case 6:
                // Esci dal gioco.
                return 0;
        }
    }
}
