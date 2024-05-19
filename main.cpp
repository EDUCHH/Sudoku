#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

const int DIM = 9;
const int NUMPARTITEMAX=100;

struct Partita {
    int mat[DIM][DIM]; // matrice del sudoku
    string inizioPartita; // DAY/MONTH/YEAR hh:mm:ss
    int tempoTrascorso; // misurato in secondi
    bool giocatore; // true = player --- false = computer
    bool stato; // true = in corso --- false = terminata
};

// menu di gioco
void menu() {
    int min = 1, max = 4, opzione;

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

// serve per inizializzare la matrice. mettendo tutti gli elementi a 0.
// verra chiamata prima della generazione di sudoku.
void initMatrice(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            mat[i][j] = 0;
        }
    }
}

bool controlloNumeroValido(int mat[DIM][DIM], int rig, int col, int num) {
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
bool sudokuValido(int mat[DIM][DIM]) {

    // cicli for che iterano per l'intero sudoku
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {

            // se ce una casella vuota (0),
            // viene fatto un altro ciclo e 
            // viene controllato se il numero e valido o no
            if (mat[i][j] == 0) {
                for (int num = 1; num < DIM; num++) {
                    if (controlloNumeroValido(mat, i, j, num)) {

                        // se il numero e valido allora viene usato
                        mat[i][j] = num;

                        // con il nuovo numero si cerca di risolvere le caselle successive
                        // si puo chiamare la funzione stessa per continuare.
                        if (sudokuValido(mat)) {

                            // se riesce a risolvere il sudoku allora vuol dire che il numero e valido
                            return true;
                        }

                        // il numero non e valido
                        // quindi rimettere la casella a 0
                        mat[i][j] = 0;
                    }
                }

                // nessuno dei numeri e valido
                // quindi si torna all'indietro per provare altri numeri
                return false;

            }
        }
    }

    // la soluzione viene trovata
    return true;
}

int generaNumero(int mat[DIM][DIM], int rig, int col) {
    int num;

    do {
        num = rand() % 9 + 1;
    } while (sudokuValido(mat));

    return num;
}

void generaSudoku(int mat[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            int num = generaNumero(mat, i, j);
        }
    }
}

int main() {
    int mat[9][9];

    int numero_partite;


    return 0;
}
