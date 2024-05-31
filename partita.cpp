#include <iostream>
#include "costanti.h"

using namespace std;

/**
 * @brief Funzione per permettere all'utente di scegliere se giocare come giocatore o far risolvere il Sudoku dalla CPU.
 * 
 * Questa funzione richiede all'utente di inserire la scelta del giocatore, dove 0 rappresenta la CPU e 1 rappresenta il Player.
 * L'utente è tenuto a inserire un'opzione valida compresa tra 0 e 1.
 * 
 * @return Il valore scelto dall'utente (0 per la CPU, 1 per il Player).
 */
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

/**
 * @brief La funzione permette all'utente di inserire un suggerimento nella griglia del Sudoku in base alle coordinate specificate.
 * Se l'utente inserisce -1 come coordinata, la funzione restituisce false.
 * 
 * @param sudoku La griglia del Sudoku in cui inserire il suggerimento.
 * @param soluzioneSudoku La griglia contenente la soluzione del Sudoku.
 *
 * @return Restituisce true se il suggerimento è stato inserito correttamente, altrimenti restituisce false.
 */
bool suggerimento(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM]){
    int min=0, max=8;
    int rig, col;
    bool restart;

    do{
        restart = false;
        cout << ORANGE << "Dove vuoi inserire il suggerimento (r-c):" << RESET << '\n';
        cin >> rig;

        if(rig == -1){
            return false;
        }
        
        cin >> col;
        if(col == -1){
            return false;
        }

        if((rig >= min && rig <= max) && (col >= min && col <= max)){
            if(sudoku[rig][col] == 0){
                sudoku[rig][col] = soluzioneSudoku[rig][col];
                cout << GREEN << "Suggerimento utilizzato: " << RESET << soluzioneSudoku[rig][col] << '[' << rig << '-' << col << ']' << '\n';
            } else{
                cout << RED << "Cella gia' occupata!" << RESET << '\n';
                restart = true;
            }
        } else{
            cout << RED << "Input errato!" << RESET << '\n';
            restart = true;
        }
    }while(restart);

    return true;
}

/**
 * @brief Questa funzione verifica se la griglia di gioco 'mat' non contiene più celle vuote.
 * 
 * @param mat La griglia di gioco da controllare.
 *
 * @return Restituisce false se la partita non è terminata (ci sono ancora celle vuote), altrimenti restituisce true.
 */
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

/**
 * @brief Gestisce l'input della mossa del giocatore nel Sudoku.
 * 
 * Questa funzione richiede all'utente di inserire un numero da 1 a 9 e la posizione in cui inserirlo nella griglia di gioco.
 * L'utente è guidato a inserire un numero valido e a posizionarlo in una cella vuota della griglia.
 * 
 * @param mat La griglia di gioco del Sudoku.
 *
 * @param modificheSudoku La griglia che tiene traccia delle modifiche effettuate dall'utente.
 * @return Restituisce 0 se l'input è stato gestito correttamente, 1 se l'utente ha inserito -1 come input per uscire, 2 se l'utente ha inserito -2 come input per il suggerimento.
 */
int inputMossa(int mat[DIM][DIM], int modificheSudoku[DIM][DIM]) {
    int numero;
    int min, max;
    bool restart;
    int rig, col;

    // Input numero
    min = 1; max = 9;
    do {
        cout << ORANGE << "Inserisci un numero: " << RESET;
        cin >> numero;
        
        if(numero == -1){
            return 1;
        } else if(numero == -2){
            return 2;
        } else if (numero < min || numero > max) {
            cout << RED << "Input errato! " << RESET << '\n';
        }
    } while (numero < min || numero > max);

    // Posizione numero
    min = 0; max = 8;
    do {
        restart = false;
        cout << ORANGE << "Inserisci la posizione in cui vuoi inserire il numero (r-c): \n" << RESET;

        // Righe
        cin >> rig;

        if(rig == -1){
            int returnInputMossa = inputMossa(mat, modificheSudoku);
            if(returnInputMossa == 1){
                return 1;
            } else if(returnInputMossa == 2){
                return 2;
            }
            break;
        }

        // Colonne.
        cin >> col; 

        if(col == -1){
            int returnInputMossa = inputMossa(mat, modificheSudoku);
            if(returnInputMossa == 1){
                return 1;
            } else if(returnInputMossa == 2){
                return 2;
            }
            break;
        }

        // Controllo dati dentro alla tabella.
        if ((rig < min || rig > max) || (col < min || col > max)) {
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

/**
 * @brief Verifica se la griglia di gioco corrente corrisponde alla soluzione del Sudoku.
 * 
 * Questa funzione confronta ogni cella della griglia di gioco 'mat' con la corrispondente cella nella soluzione del Sudoku 'soluzioneSudoku'.
 * Restituisce true se la griglia di gioco è corretta e corrisponde alla soluzione, altrimenti restituisce false.
 * 
 * @param soluzioneSudoku La griglia contenente la soluzione del Sudoku.
 * @param mat La griglia di gioco da verificare.
 *
 * @return Restituisce true se la griglia di gioco corrisponde alla soluzione, altrimenti restituisce false.
 */
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

/**
 * @brief Richiede all'utente di inserire un numero che rappresenta il livello di difficoltà del gioco.
 * 
 * Questa funzione richiede all'utente di inserire un numero compreso tra 1 e 40.
 * L'utente è tenuto a inserire un numero valido all'interno di questo intervallo.
 * 
 * @return Il numero che rappresenta il livello di difficoltà scelto dall'utente.
 */
int inputDifficolta() {
    int numero;

    do {
        cout << ORANGE << "Inserisci la difficolta' di gioco [1 - 40]: " << RESET;
        cin >> numero;
    } while (numero <= 0 || numero >= 41);

    return numero;
}

/**
 * @brief Questa funzione confronta la griglia di gioco 'sudoku' con la soluzione del Sudoku 'soluzioneSudoku' e stampa gli errori, se presenti.
 * Viene mostrata la posizione dell'errore e il numero corretto che dovrebbe essere presente in quella cella.
 * 
 * @param soluzioneSudoku La griglia contenente la soluzione del Sudoku.
 * @param sudoku La griglia di gioco da confrontare con la soluzione.
 */
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
