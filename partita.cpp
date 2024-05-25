#include <iostream>
#include "costanti.h"

using namespace std;

int sceltaGiocatore() {
    int min = 0, max = 1;
    int giocatore;

    do {
        cout << ORANGE << "Inserisci il giocatore (0-CPU // 1-Player): " << RESET;
        cin >> giocatore;

        if (giocatore < min || giocatore > max) {
            cout << RED <<"Input errato!\n" << RESET;
        }
    } while (giocatore < min || giocatore > max);

    return giocatore;
}
//0: CPU ----- 1: PLAYER

bool exitPartita() {
    char input;

    do {
        cout << ORANGE << "Vuoi uscire dalla partita? (s/n) " << RESET;
        cin >> input;

        if (input != 's' && input != 'n') {
            cout << RED << "Input errato! \n" << RESET;
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
        cout << ORANGE << "Inserisci un numero: " << RESET;
        cin >> numero;

        if (numero < min || numero > max) {
            cout << RED << "Input errato! " << RESET;
        }
    } while (numero < min || numero > max);

    //posizione numero
    min = 0; max = 8;
    do {
        restart = false;
        cout << ORANGE << "Inserisci la posizione in cui vuoi inserire il numero (r-c): \n" << RESET;
        cin >> rig /*righe*/ >> col /*colonne*/;

        if ((rig < min || rig > max) || (col < min || col > max)) { //controllo dati dentro alla tabella
            cout << RED << "Input errato! \n" << RESET;
            restart = true;
        } else {
            if (mat[rig][col] != 0) {
                cout << RED << "Cella gia' occupata! \n" << RESET;
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
        cout << ORANGE << "Inserisci la difficolta' di gioco [1 - 40]: " << RESET;
        cin >> numero;
    } while (numero <= 0 || numero >= 41);

    return numero;
}