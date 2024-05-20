#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int DIM = 9;
const int NUMPARTITEMAX = 100;

struct Partita {
    int mat[DIM][DIM]; // matrice del sudoku
    string inizioPartita; // DAY/MONTH/YEAR hh:mm:ss
    int tempoTrascorso; // misurato in secondi
    bool giocatore; // true = player --- false = computer
    bool stato; // true = in corso --- false = terminata
};

// menu di gioco
void menu() {
    int min = 1, max = 5, opzione;

    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Vedere le regole \n";
    cout << "4. Storico delle partite \n";
    cout << "5. Esci dal gioco \n";

    do {
        cout << "Inserisci un'opzione: ";
        cin >> opzione;

        if (opzione < min || opzione > max){
            cout << "Input errato! \n";
        }
    } while (opzione < min || opzione > max);

    switch (opzione) {
        case 1:
            // Avvia una partita

            break;
        case 2:
            // Carica una partita
            break;
        case 3:
            // Vedere le regole
            break;
        case 4:
            // Esci dal gioco
            exit(EXIT_SUCCESS);
            break;
    }
}

void stampaSudoku(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            cout << mat[i][j] << " ";
        }

        cout << endl;
    }
}

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

// utilizza il backtracking per cercare di risolvere il sudoku.
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

    int numeri[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
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

int main() {
    int mat[9][9];

    int numero_partite;

    initMatrice(mat);
    generaSudoku(mat);

    stampaSudoku(mat);


    return 0;
}
