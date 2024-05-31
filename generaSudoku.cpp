#include <cstdlib>
#include <utility>
#include "costanti.h"

using namespace std;

/**
 * @brief Questa funzione viene chiamata prima della generazione del Sudoku per inizializzare tutte le celle della matrice a zero.
 *
 * @param mat La matrice del Sudoku da inizializzare con zeri.
 */
void initMatrice(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            mat[i][j] = 0; // Inizializza ogni cella della matrice con zero.
        }
    }
}

/**
 * @brief Questa funzione copia i valori dalla matrice di origine alla matrice di destinazione.
 *
 * @param mat1 La matrice di destinazione.
 * @param mat2 La matrice di origine.
 */
void copiaMatrice(int mat1[DIM][DIM], int mat2[DIM][DIM]) {
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++){
            mat1[i][j] = mat2[i][j]; // Copia il valore dalla matrice di origine alla matrice di destinazione.
        }
    }
}

/**
 * @brief Questa funzione controlla se il numero specificato è valido nella cella specificata della matrice del Sudoku.
 *
 * @param mat La matrice del Sudoku.
 * @param rig La riga della cella.
 * @param col La colonna della cella.
 * @param num Il numero da controllare.
 * @return true se il numero è valido nella cella specificata, altrimenti false.
 */
bool controlloNumero(int mat[DIM][DIM], int rig, int col, int num) {
    // Controllo riga.
    for (int i = 0; i < DIM; i++) {
        if (mat[rig][i] == num) {
            return false;
        }
    }

    // Controllo colonna.
    for (int i = 0; i < DIM; i++) {
        if (mat[i][col] == num) {
            return false;
        }
    }

    // Controllo box 3x3.
    int rigBox = rig - rig % 3;
    int colBox = col - col % 3;

    for (int i = rigBox; i < rigBox + 3; i++) {
        for (int j = colBox; j < colBox + 3; j++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
    }

    // Se il numero supera tutti i controlli, restituisce true.
    return true;
}

/**
 * @brief Restituisce le indici di riga e colonna della prima cella vuota nella matrice del Sudoku.
 * Se la matrice è piena, la funzione restituisce false e imposta rig e col a -1.
 *
 * @param mat La matrice del Sudoku in cui cercare la prima cella vuota.
 * @param rig Variabile di output per l'indice di riga della cella vuota.
 * @param col Variabile di output per l'indice di colonna della cella vuota.
 * @return true se viene trovata una cella vuota, altrimenti false.
 */
bool verificaMatriceVuota(int mat[DIM][DIM], int& rig, int& col) {
    // Cicli for per individuare la prima cella vuota.
    for (rig = 0; rig < DIM; rig++) {
        for (col = 0; col < DIM; col++) {
            if (mat[rig][col] == 0) {
                // Se viene trovata una cella vuota, restituisce true.
                return true;
            }
        }
    }

    // Se la matrice è piena, restituisce false e imposta rig e col a -1.
    rig = -1;
    col = -1;
    return false;
}

/**
 * @brief Questa funzione utilizza l'algoritmo di backtracking per generare o risolvere un Sudoku in modo ricorsivo.
 *
 * @param mat La matrice del Sudoku da generare o risolvere.
 * @param risoluzioneCPU Indica se la funzione è utilizzata per la generazione o la risoluzione del Sudoku.
 * @return true se è stata trovata una soluzione al Sudoku, altrimenti false.
 */
bool risolviSudoku(int mat[DIM][DIM], bool risoluzioneCPU) {
    int rig, col;

    // Verifica se la matrice è piena, in tal caso esce dalla funzione poiché la soluzione è stata trovata.
    if (!verificaMatriceVuota(mat, rig, col)) {
        return true;
    }

    int numeri[DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Mescola i numeri solo durante la generazione del Sudoku.
    if (!risoluzioneCPU) {
        for (int i = 0; i < DIM; i++) {
            int j = rand() % 9;
            swap(numeri[i], numeri[j]);
        }
    }

    // Prova ad inserire i numeri nella cella vuota rispettando le regole del Sudoku.
    for (int i = 0; i < DIM; i++) {
        if (controlloNumero(mat, rig, col, numeri[i])) {
            // Il numero soddisfa le regole del Sudoku, quindi viene inserito nella cella.
            mat[rig][col] = numeri[i];

            // Prova a risolvere il Sudoku utilizzando il numero e richiamando la funzione stessa in modo ricorsivo.
            if (risolviSudoku(mat, risoluzioneCPU)) {
                // Soluzione trovata, restituisce true.
                return true;
            }

            // Ripristina la cella poiché nessun numero inserito soddisfa le regole del Sudoku
            // e si proverà con un altro numero nella cella precedente.
            mat[rig][col] = 0;
        }
    }

    // Non è stata trovata una soluzione, restituisce false.
    // Si procederà alla cella precedente e si proverà con il numero successivo.
    return false;
}

/**
 * @brief  Questa funzione rimuove un numero specificato di numeri dalla matrice del Sudoku, rendendoli vuoti (rappresentati con lo 0).
 *
 * @param mat La matrice del Sudoku completo già risolto.
 * @param num Il numero di numeri da rimuovere dalla matrice per rendere il Sudoku giocabile.
 */
void cavaNumeri(int mat[DIM][DIM], int num) {
    do {
        // Genera numeri casuali da 0 a 8 per riga e colonna.
        int rig = rand() % 9;
        int col = rand() % 9;

        // Cancella solo le celle con numeri diversi da 0, sostituendoli con 0.
        if (mat[rig][col] != 0) {
            mat[rig][col] = 0;
            num--;
        }

        // Continua a cancellare numeri finché non raggiunge 0.
    } while (num > 0);
}

/**
 * @brief Questa funzione viene chiamata da verificaSudoku() ed esegue una ricerca ricorsiva per determinare se il Sudoku ha più di una soluzione.
 *
 * @param mat La matrice del Sudoku da verificare.
 * @param soluzioni Paramentro di output che indica il numero di soluzioni trovate durante la ricerca.
 * @return true se il Sudoku ha una sola soluzione, altrimenti false.
 */
bool sudokuSoluzioni(int mat[DIM][DIM], int& soluzioni) {
    int rig, col;

    // Se la matrice non contiene celle vuote, il Sudoku è valido.
    if (!verificaMatriceVuota(mat, rig, col)) {
        // Incrementa il contatore delle soluzioni.
        soluzioni++;

        // Restituisce un booleano in base al numero di soluzioni trovate.
        if (soluzioni <= 1) {
            // Continua a cercare altre soluzioni se ne è stata trovata solo una.
            return true;
        } else {
            // Il Sudoku ha più di una soluzione, quindi è invalido.
            return false;
        }
    }

    // Prova ad inserire i numeri da 1 a 9 nella cella vuota.
    for (int num = 1; num <= DIM; num++) {
        // Controlla se è possibile inserire il numero senza violare le regole del Sudoku.
        if (controlloNumero(mat, rig, col, num)) {
            // Il numero è valido, quindi viene inserito nella cella vuota.
            mat[rig][col] = num;

            // Chiamata ricorsiva per esplorare le possibili soluzioni.
            if (!sudokuSoluzioni(mat, soluzioni)) {
                // Se non è possibile trovare una soluzione con il numero inserito, torna indietro.
                return false;
            }

            // Reset della cella dopo la ricorsione per esplorare altre soluzioni.
            mat[rig][col] = 0;
        }
    }

    // Se si è arrivati a questo punto, significa che la soluzione è stata trovata.
    return true;
}

/**
 * @brief Questa funzione verifica se un Sudoku ha esattamente una soluzione, restituendo true se è valido e false altrimenti.
 *
 * @param mat La matrice del Sudoku da verificare.
 * @return true se il Sudoku ha una sola soluzione, altrimenti false.
 */
bool verificaSudoku(int mat[DIM][DIM]) {
    int copia[DIM][DIM];
    int soluzioni = 0;

    // Copia la matrice del Sudoku per non modificarla direttamente.
    copiaMatrice(copia, mat);

    // Verifica il numero di soluzioni possibili per il Sudoku.
    sudokuSoluzioni(copia, soluzioni);

    // Restituisce true se il Sudoku ha esattamente una soluzione.
    return soluzioni == 1;
}
