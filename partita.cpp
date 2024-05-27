#include <iostream>
#include "costanti.h"

using namespace std;

// Funzione per permettere all'utente di scegliere se giocare come giocatore o far risolvere il Sudoku dalla CPU.
// Questa funzione richiede all'utente di inserire la scelta del giocatore, dove 0 rappresenta la CPU e 1 rappresenta il Player.
// L'utente è tenuto a inserire un'opzione valida compresa tra 0 e 1.
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

// Funzione per consentire all'utente di decidere se uscire dalla partita o continuare.
// Questa funzione richiede all'utente di inserire 's' per confermare l'uscita dalla partita o 'n' per continuare.
// L'utente è tenuto a inserire un'opzione valida tra 's' e 'n'.
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

// Questa funzione controlla se la griglia di gioco 'mat' è completamente riempita, ossia se non ci sono più celle vuote.
// False indica che la partita non è terminata, mentre true indica il caso contrario.
bool partitaTerminata(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if(mat[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

// Funzione per gestire l'input della mossa del giocatore nel Sudoku.
// Questa funzione richiede all'utente di inserire un numero da 1 a 9 e la posizione in cui inserirlo nella griglia di gioco.
// L'utente è guidato a inserire un numero valido e a posizionarlo in una cella vuota della griglia.
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

// Funzione per verificare se la griglia di gioco corrente corrisponde alla soluzione del Sudoku.
// Questa funzione confronta ogni cella della griglia di gioco 'mat' con la corrispondente cella nella soluzione del Sudoku 'soluzioneSudoku'.
// Restituisce true se la griglia di gioco è corretta e corrisponde alla soluzione, altrimenti restituisce false.
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

// Questa funzione richiede all'utente di inserire un numero compreso tra 1 e 40 che rappresenta il livello di difficoltà del gioco.
// L'utente è tenuto a inserire un numero valido all'interno di questo intervallo.
int inputDifficolta() {
    int numero;

    do {
        cout << ORANGE << "Inserisci la difficolta' di gioco [1 - 40]: " << RESET;
        cin >> numero;
    } while (numero <= 0 || numero >= 41);

    return numero;
}

// Questa funzione confronta la griglia di gioco 'sudoku' con la soluzione del Sudoku 'soluzioneSudoku' e stampa gli errori, se presenti.
// Viene mostrata la posizione dell'errore e il numero corretto che dovrebbe essere presente in quella cella.
void outputEventualiErrori(int soluzioneSudoku[DIM][DIM], int sudoku[DIM][DIM]){
    if (!verificaVittoria(soluzioneSudoku, sudoku)){
        cout << RED << "Ecco gli errori: " << RESET << '\n';
        for(int i=0; i < DIM; i++){
            for(int j=0; j < DIM; j++){
                if(soluzioneSudoku[i][j] != sudoku[i][j]){
                    cout << "pos[" << i <<"-" << j << "] " << RED << sudoku[i][j] << RESET << " -> " << GREEN << soluzioneSudoku[i][j] << RESET << '\n';
                }
            }
        }
    }
}