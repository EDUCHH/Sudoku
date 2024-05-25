#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "generaSudoku.cpp"
#include "partita.cpp"
#include "gestioneFile.cpp"
#include "costanti.h"

using namespace std;

//cose
void stampaSudoku(int mat[DIM][DIM]){
    string RED = "\033[31m";
    string BLUE = "\033[34m";
    string GREEN = "\033[32m";
    string RESET = "\033[0m";

    cout << RED << "+-------------------------+\n";
    for (int i = 0; i < 9; ++i) {
        cout << RED << "| ";
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0) cout << RED << "|| ";
            if (mat[i][j] == 0) {
                cout << GREEN << mat[i][j] << " ";
            } else {
                cout << BLUE << mat[i][j] << " ";
            }
        }
        cout << RED << "|\n";
        if (i % 3 == 2 && i != 8) {
            cout << RED << "|-------++-------++-------|\n";
        }
    }
    cout << RED << "+-------------------------+\n" << RESET;
}

//partita
void avviaPartita(bool partitaNuova) {
    int soluzioneSudoku[DIM][DIM];
    int sudoku[DIM][DIM];

    if (partitaNuova) {
        initMatrice(soluzioneSudoku);
        risolviSudoku(soluzioneSudoku, false);

        //copia matrice
        int num = inputDifficolta();

        do {
            copiaMatrice(sudoku, soluzioneSudoku);
            cavaNumeri(sudoku, num);
        } while (!verificaSudoku(sudoku));
    } else {
        //controlo che la partita non sia già finita
        if(verificaVittoria(soluzioneSudoku, sudoku)){
            caricaPartita(sudoku, soluzioneSudoku);
        }
        else{
            cout << "Non è possibile caricare la paritta in quanto questa è finita\n";
            return;
        }
    }

    if (sceltaGiocatore()) {
        //player
        while (!partitaTerminata(sudoku)) {
            stampaSudoku(sudoku);
            inputMossa(sudoku);
            if (exitPartita()) {
                return;
            }
            salvaPartita(sudoku, soluzioneSudoku);
        }
        aggiornaStorico(verificaVittoria(soluzioneSudoku, sudoku));
    } else {
        //cpu
        stampaSudoku(sudoku);
        risolviSudoku(sudoku, true);

        if (partitaTerminata(sudoku)) {
            stampaSudoku(sudoku);

            if (exitPartita()) {
                return;
            }
            salvaPartita(sudoku, soluzioneSudoku);
        } else {
            cout << "non è stato possibile risolvere il sudoku \n";
        }
        // non si va ad aggiornare lo storico perché è dell'utente.
    }
}

int menu() {
    int min = 1, max = 6, opzione;

    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Salva ultima partita \n";
    cout << "4. Vedere le regole \n";
    cout << "5. Storico delle partite \n";
    cout << "6. Esci dal gioco \n";

    do{
        cout << "Inserisci un'opzione: ";
        cin >> opzione;

        if (opzione < min || opzione > max) {
            cout << "Input errato! \n";
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
                //Salva ultima partita
                break;
            case 4:
                //Vedere le regole
                stampaRegole();
                break;
            case 5:
                //Storico delle partite
                stampaStorico();
                break;
            case 6:
                //Esci dal gioco
                return 0;
        }
    }
}