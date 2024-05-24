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
bool risolviSudoku(int mat[DIM][DIM], bool risoluzioneCPU) {
    int rig, col;
    bool matriceVuota = false;

    for (rig = 0; rig < DIM; rig++) {
        for (col = 0; col < DIM; col++) {
            if (mat[rig][col] == 0) {
                matriceVuota = true;
                break;
            }
        }
        if (matriceVuota) {
            break;
        }
    }

    if (!matriceVuota) {
        return true;
    }

    int numeri[DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (!risoluzioneCPU) {
        for (int i = 0; i < DIM; i++) {
            int j = rand() % 9;
            swap(numeri[i], numeri[j]);
        }
    }

    for (int i = 0; i < 9; i++) {
        if (controlloNumero(mat, rig, col, numeri[i])) {
            mat[rig][col] = numeri[i];

            if (risolviSudoku(mat, risoluzioneCPU)) {
                return true;
            }

            mat[rig][col] = 0;
        }
    }

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

void cavaNumeri(int mat[DIM][DIM], int num) {
    do {
        // genera numeri da 0 a 8
        int rig = rand() % 9;
        int col = rand() % 9;

        if (mat[rig][col] != 0) {
            mat[rig][col] = 0;
            num--;
        }
    } while (num > 0);
}


bool sudokuSoluzioni(int mat[DIM][DIM], int& soluzioni, bool continuaRicerca = false) {
    int rig, col;
    bool matriceVuota = false;

    for (rig = 0; rig < DIM; rig++) {
        for (col = 0; col < DIM; col++) {
            if (mat[rig][col] == 0) {
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

            if (sudokuSoluzioni(mat, soluzioni, continuaRicerca)) {
                mat[rig][col] = 0;
            } else {
                return true;
            }
        }
    }

    return false;
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