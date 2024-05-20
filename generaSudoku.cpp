#include <cstdlib>
#include <utility>

using namespace std;

const int DIM = 9;

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
bool generaSudoku(int mat[DIM][DIM]) {
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
    for (int i = 0; i < DIM; i++) {
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
void copiaMatrice(int mat[DIM][DIM], soluzioneSudoku[DIM][DIM]){
    for(int i=0; i < DIM; i++){
        for(int p=0; p < DIM; p++){
            mat[i][p] = soluzioneSudoku[i][p];
        }
    }
}