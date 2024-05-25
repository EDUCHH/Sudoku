#include <cstdlib>
#include <utility>
#include "costanti.h"

using namespace std;

// Inizializza il sudoku con zeri
// verra chiamata prima della generazione di sudoku.
void initMatrice(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            mat[i][j] = 0;
        }
    }
}

// effettua i controlli. controlla che il numero sia valido nella cella.
bool controlloNumero(int mat[DIM][DIM], int rig, int col, int num) {
    // controllo riga
    for (int i = 0; i < DIM; i++) {
        if (mat[rig][i] == num) {
            return false;
        }
    }

    // controllo colonna
    for (int i = 0; i < DIM; i++) {
        if (mat[i][col] == num) {
            return false;
        }
    }

    // controllo box 3*3

    // in questo modo troviamo le indici della casella in alto a sinistra del box.
    int rigBox = rig - rig % 3;
    int colBox = col - col % 3;

    // rigBox + 3; trova la casella in basso a destra del box. non che l'ultima casella.
    // viceversa per colBox.
    for (int i = rigBox; i < rigBox + 3; i++) {
        for (int j = colBox; j < colBox + 3; j++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
    }

    // una volta superato tutti i controlli viene restituito true.
    return true;
}

// utilizza il backtracking per cercare di generare il sudoku.
// puo essere usato anche per risolvere un sudoku
// è una funzione ricorsiva, vuol dire che la funzione chiama se stessa.
bool risolviSudoku(int mat[DIM][DIM], bool risoluzioneCPU) {
    int rig, col;

    // si pressupone che la matrice sia piena all'inizio
    bool matriceVuota = false;

    // vedere se ci sono delle celle vuote
    for (rig = 0; rig < DIM; rig++) {
        for (col = 0; col < DIM; col++) {
            if (mat[rig][col] == 0) {

                // trovato una cella vuota
                // viene aggiornato la variabile
                matriceVuota = true;
                break;
            }
        }
        if (matriceVuota) {
            // uscire prima dal ciclo for perché c'è una cella vuota
            break;

        }
    }

    // verificare che la matrice sia piena
    // se è piena si esce dalla funzione
    if (!matriceVuota) {
        return true;
    }

    int numeri[DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // i numeri vengono messi a caso solo quando ce la generazione del sudoku
    if (!risoluzioneCPU) {
        for (int i = 0; i < DIM; i++) {
            int j = rand() % 9;
            swap(numeri[i], numeri[j]);
        }
    }

    // si prova ad inserire i numeri nella cella vuota seguendo le regole del sudoku
    for (int i = 0; i < 9; i++) {
        if (controlloNumero(mat, rig, col, numeri[i])) {
            // il numero soddisfa le regole del sudoku, quindi viene inserito nella cella
            mat[rig][col] = numeri[i];

            // si tenta di usare il numero e viene chiamata la funzione stessa per procedere
            if (risolviSudoku(mat, risoluzioneCPU)) {
                // è stata trovata la soluzione, quindi restituisce true
                return true;
            }

            // è necessario ripristinare la cella perché nessun numero inserito soddisfa le regole del sudoku
            // e si proverà con un altro numero nella cella precedente
            mat[rig][col] = 0;
        }
    }

    // non è stato possibile trovare la soluzione, quindi restituisce false
    // si procederà alla cella precedente e si proverà ad usare il numero successivo
    return false;
}

// copia i numeri da mat2 a mat1
void copiaMatrice(int mat1[DIM][DIM], int mat2[DIM][DIM]) {
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++){
            mat1[i][j] = mat2[i][j];
        }
    }
}

// funzione che cancella i numeri dalle celle in modo da rendere il sudoku giocabile 
// mat è un sudoku completo già risolto
// num è il numero dei numeri da togliere dalla matrice
void cavaNumeri(int mat[DIM][DIM], int num) {
    do {
        // genera numeri da 0 a 8
        int rig = rand() % 9;
        int col = rand() % 9;

        // cancella solo celle con numeri diversi da 0
        if (mat[rig][col] != 0) {
            mat[rig][col] = 0;
            num--;
        }

        // continua a cancellare numeri finché non arriva a 0
    } while (num > 0);
}

// funzione ricorsiva che viene chiamata da verificaSudoku()
// restituisce un booleano che indica se il sudoku ha più di una soluzione oppure no.
bool sudokuSoluzioni(int mat[DIM][DIM], int& soluzioni, bool continuaRicerca = false) {
    int rig = -1, col = -1;
    bool matriceVuota = false;

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (mat[i][j] == 0) {
                rig = i;
                col = j;
                matriceVuota = true;
                break;
            }
        }
        if (matriceVuota) {
            break;
        }
    }

    if (!matriceVuota) {
        soluzioni++;
        return soluzioni <= 1;
    }

    for (int num = 1; num <= DIM; num++) {
        if (controlloNumero(mat, rig, col, num)) {
            mat[rig][col] = num;

            if (!sudokuSoluzioni(mat, soluzioni, continuaRicerca)) {
                return false;
            }

            mat[rig][col] = 0; // Reset cella dopo ricorsione
        }
    }

    return true;
}
// il sudoku deve avere una sola soluzione. quindi questa funzione serve a verificare la validità di un sudoku in base al numero possibile di soluzioni
// se le soluzioni sono più di uno allora il sudoku non è valudo
bool verificaSudoku(int mat[DIM][DIM]) {
    int copia[DIM][DIM];
    int soluzioni = 0;

    copiaMatrice(copia, mat);

    sudokuSoluzioni(copia, soluzioni);

    return soluzioni == 1;
}