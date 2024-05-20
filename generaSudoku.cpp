#include <cstdlib>
#include <utility>

const int DIM2 = 9;

using namespace std;

// Inizializza il sudoku con zeri
// verra chiamata prima della generazione di sudoku.
void initMatrice(int mat[DIM2][DIM2]) {
    for (int i = 0; i < DIM2; i++) {
        for (int j = 0; j < DIM2; j++) {
            mat[i][j] = 0;
        }
    }
}

bool controlloNumero(int mat[DIM2][DIM2], int rig, int col, int num) {
    // controllo riga
    for (int i = 0; i < DIM2; i++) {
        if (mat[rig][i] == num) {
            return false;
        }
    }

    // controllo colonna
    for (int i = 0; i < DIM2; i++) {
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
bool generaSudoku(int mat[DIM2][DIM2]) {
    int rig, col;
    bool matriceVuota = false;

    for (rig = 0; rig < DIM2; rig++) {
        for (col = 0; col < DIM2; col++) {
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

    int numeri[DIM2] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < DIM2; i++) {
        int j = rand() % 9;
        swap(numeri[i], numeri[j]);
    }

    for (int i = 0; i < 9; i++) {
        if (controlloNumero(mat, rig, col, numeri[i])) {
            mat[rig][col] = numeri[i];

            if (generaSudoku(mat)) {
                return true;
            }

            mat[rig][col] = 0;
        }
    }

    return false;
}

//copia la matrice soluzioneSudoku in mat
void copiaMatrice(int mat[DIM2][DIM2], int soluzioneSudoku[DIM2][DIM2]) {
    for(int i = 0; i < DIM2; i++) {
        for(int j = 0; j < DIM2; j++){
            mat[i][j] = soluzioneSudoku[i][j];
        }
    }
}