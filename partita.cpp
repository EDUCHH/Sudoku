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

void suggerimento(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM]){
    int min=0, max=8;
    int rig, col;
    bool restart;

    do{
        restart = false;
        cout << ORANGE << "Dove vuoi inserire il suggerimento (r-c):" << RESET << '\n';
        cin >> rig >> col;

        if(sudoku[rig][col] == 0){
            sudoku[rig][col] = soluzioneSudoku[rig][col];
            cout << GREEN << "Suggerimento utilizzato: " << RESET << soluzioneSudoku[rig][col] << '[' << rig << '-' << col << ']' << '\n';
        } else{
            cout << RED << "Cella gia' occupata!" << RESET << '\n';
            restart = true;
        }
    }while(restart);
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
int inputMossa(int mat[DIM][DIM], int modificheSudoku[DIM][DIM]) {
    int numero;
    int min, max;
    bool restart;
    int rig, col;

    //Input numero
    min = 1; max = 9;
    do {
        cout << ORANGE << "Inserisci un numero: " << RESET;
        cin >> numero;
        
        if(numero == -1){
            return 1;
        } else if(numero == -2){
            return 2;
        } else if (numero < min || numero > max) {
            cout << RED << "Input errato! " << RESET;
        }
    } while (numero < min || numero > max);

    //posizione numero
    min = 0; max = 8;
    do {
        restart = false;
        cout << ORANGE << "Inserisci la posizione in cui vuoi inserire il numero (r-c): \n" << RESET;
        cin >> rig /*righe*/;

        if(rig == -1){
            inputMossa(mat, modificheSudoku);
            break;
        }

        cin >> col /*colonne*/;

        if(col == -1){
            inputMossa(mat, modificheSudoku);
            break;
        }


        if ((rig < min || rig > max) || (col < min || col > max)) { //controllo dati dentro alla tabella
            cout << RED << "Input errato! \n" << RESET;
            restart = true;
        } else {
            if (mat[rig][col] != 0) {
                if(modificheSudoku[rig][col] == 1){
                    mat[rig][col] = numero;
                    break;
                }
                cout << RED << "Cella gia' occupata! \n" << RESET;
                restart = true;
            } else {
                mat[rig][col] = numero;
                modificheSudoku[rig][col] = 1;
            }
        }
    } while (restart);

    return 0;
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