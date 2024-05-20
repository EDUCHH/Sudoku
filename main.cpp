#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "generaSudoku.cpp"

using namespace std;

const int NUMPARTITEMAX = 100;

// menu di gioco
void menu() {
    int min = 1, max = 6, opzione;

    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Salvare una partita \n";
    cout << "4. Vedere le regole \n";
    cout << "5. Storico delle partite \n";
    cout << "6. Esci dal gioco \n";

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
            // Salvare una partita
            break;
        case 4:
            // Vedere le regole
            break;
        case 5:
            // Storico delle partite
            break;
        case 6:
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


int main() {
    srand(time(NULL));

    int soluzioneSudoku[DIM][DIM];
    int mat[DIM][DIM];
    
    initMatrice(soluzioneSudoku);
    generaSudoku(soluzioneSudoku);

    stampaSudoku(soluzioneSudoku);


    return 0;
}
