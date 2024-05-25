#include <iostream>
#include "costanti.h"

using namespace std;

int sceltaGiocatore() {
    int min = 0, max = 1;
    int giocatore;

    do {
        cout << "Inserisci il giocatore (0-CPU // 1-Player): \n";
        cin >> giocatore;

        if (giocatore < min || giocatore > max) {
            cout << "Input errato!\n";
        }
    } while (giocatore < min || giocatore > max);

    return giocatore;
}
//0: CPU ----- 1: PLAYER

bool exitPartita() {
    char input;

    do {
        cout << "Vuoi uscire dalla partita? (s/n) \n";
        cin >> input;

        if (input != 's' && input != 'n') {
            cout << "Input errato! \n";
        }
    } while (input != 's' && input != 'n');

    if (input == 's') {
        return true;
    } else {
        return false;
    }
}

bool partitaTerminata(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int p = 0; p < DIM; p++) {
            if(mat[i][p] == 0) {
                return false;
            }
        }
    }

    return true;
}
//FALSE: SUDOKU NON COMPLETO ----- TRUE: SUDOKU COMPLETO

void inputMossa(int mat[DIM][DIM]) {
    int numero;
    int min, max;
    bool restart;
    int rig, col;

    //Input numero
    min = 1; max = 9;
    do {
        cout << "Inserisci un numero: \n";
        cin >> numero;

        if (numero < min || numero > max) {
            cout << "Input errato! \n";
        }
    } while (numero < min || numero > max);

    //posizione numero
    min = 0; max = 8;
    do {
        restart = false;
        cout << "Inserisci la posizione in cui vuoi inserire il numero (r-c): \n";
        cin >> rig /*righe*/ >> col /*colonne*/;

        if ((rig < min || rig > max) || (col < min || col > max)) { //controllo dati dentro alla tabella
            cout << "Input errato! \n";
            restart = true;
        } else {
            if (mat[rig][col] != 0) {
                cout << "Cella gia' occupata! \n";
                restart = true;
            } else {
                mat[rig][col] = numero;
            }
        }
    } while (restart);
}
//rig: RIGA ----- col: COLONNA

bool verificaVittoria(int soluzioneSudoku[DIM][DIM], int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (soluzioneSudoku[i][j] != mat[i][j]) {
                return false;
            }
        }
    }

    return true;
}
//TRUE: SUDOKU CORRETTO ----- FALSE: SUDOKU SBAGLIATO

// funzione che chiede all'utente il numero di numeri da togliere dal sudoku completo
int inputDifficolta() {
    int numero;

    do {
        cout << "Inserisci la difficolta' di gioco [1 - 40]: ";
        cin >> numero;
    } while (numero <= 0 || numero >= 41);

    return numero;
}