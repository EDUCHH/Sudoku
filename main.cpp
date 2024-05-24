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
    /*
    cout << "+-------------------------+\n";
    cout << "| " << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " || " << mat[0][3] << " " << mat[0][4] << " " << mat[0][5] << " || " << mat[0][6] << " " << mat[0][7] << " " << mat[0][8] << " |\n";
    cout << "| " << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " || " << mat[1][3] << " " << mat[1][4] << " " << mat[1][5] << " || " << mat[1][6] << " " << mat[1][7] << " " << mat[1][8] << " |\n";
    cout << "| " << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " || " << mat[2][3] << " " << mat[2][4] << " " << mat[2][5] << " || " << mat[2][6] << " " << mat[2][7] << " " << mat[2][8] << " |\n";
    cout << "|-------++-------++-------|\n";
    cout << "| " << mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " || " << mat[3][3] << " " << mat[3][4] << " " << mat[3][5] << " || " << mat[3][6] << " " << mat[3][7] << " " << mat[3][8] << " |\n";
    cout << "| " << mat[4][0] << " " << mat[4][1] << " " << mat[4][2] << " || " << mat[4][3] << " " << mat[4][4] << " " << mat[4][5] << " || " << mat[4][6] << " " << mat[4][7] << " " << mat[4][8] << " |\n";
    cout << "| " << mat[5][0] << " " << mat[5][1] << " " << mat[5][2] << " || " << mat[5][3] << " " << mat[5][4] << " " << mat[5][5] << " || " << mat[5][6] << " " << mat[5][7] << " " << mat[5][8] << " |\n";
    cout << "|-------++-------++-------|\n";
    cout << "| " << mat[6][0] << " " << mat[6][1] << " " << mat[6][2] << " || " << mat[6][3] << " " << mat[6][4] << " " << mat[6][5] << " || " << mat[6][6] << " " << mat[6][7] << " " << mat[6][8] << " |\n";
    cout << "| " << mat[7][0] << " " << mat[7][1] << " " << mat[7][2] << " || " << mat[7][3] << " " << mat[7][4] << " " << mat[7][5] << " || " << mat[7][6] << " " << mat[7][7] << " " << mat[7][8] << " |\n";
    cout << "| " << mat[8][0] << " " << mat[8][1] << " " << mat[8][2] << " || " << mat[8][3] << " " << mat[8][4] << " " << mat[8][5] << " || " << mat[8][6] << " " << mat[8][7] << " " << mat[8][8] << " |\n";
    cout << "+-------------------------+\n";
    */
    string RED = "\033[31m";
    string BLUE = "\033[34m";
    string RESET = "\033[0m";
    
    cout << RED << "+-------------------------+\n";
    for (int i = 0; i < 9; ++i) {
        cout << RED << "| ";
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0) cout << RED << "|| ";
            cout << BLUE << mat[i][j] << " ";
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
        caricaPartita(sudoku, soluzioneSudoku);
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