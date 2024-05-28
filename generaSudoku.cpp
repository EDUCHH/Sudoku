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

// copia i numeri da mat2 a mat1
void copiaMatrice(int mat1[DIM][DIM], int mat2[DIM][DIM]) {
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++){
            mat1[i][j] = mat2[i][j];
        }
    }
}

// da i valori alla matrice che serve a verificare se un numero era già presente all'inizio o meno
// true = riempita inizialmente ----- false = non riempita inizialmente
void setBoolMatSudokuIniziale(int sudoku[DIM][DIM], bool sudokuIniziale[DIM][DIM]){
    for(int i=0; i < DIM; i++){
        for(int j=0; j < DIM; j++){
            if(sudoku[i][j] == 0) {
                sudokuIniziale[i][j] = false;
            } else {
                sudokuIniziale[i][j] = true;
            }
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

// ritorna le indici di riga e colonna della prima cella vuota
// se la matrice è piena la funzione restituisce false
// i parametri di output rig e col = -1
bool verificaMatriceVuota(int mat[DIM][DIM], int& rig, int& col) {
    // cicli for che servono per vedere se c'è una cella vuota
    for (rig = 0; rig < DIM; rig++) {
        for (col = 0; col < DIM; col++) {
            if (mat[rig][col] == 0) {
                // una volta identificata una cella vuota si restituisce true
                return true;
            }
        }
    }

    // la matrice non è vuota quindi viene restituito false
    // le variabili rig e col sono impostati a -1 per indicare che non è stata trovata la cella vuota
    rig = -1;
    col = -1;
    return false;
}

// utilizza il backtracking per cercare di generare il sudoku.
// può essere usato anche per risolvere un sudoku
// è una funzione ricorsiva, vuol dire che la funzione chiama se stessa.
bool risolviSudoku(int mat[DIM][DIM], bool risoluzioneCPU) {
    int rig, col;

    // verificare che la matrice sia piena
    // se è piena si esce dalla funzione perché vuol dire che è stata trovata la soluzione
    if (!verificaMatriceVuota(mat, rig, col)) {
        return true;
    }

    int numeri[DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // i numeri vengono messi a caso solo quando c'è la generazione del sudoku
    if (!risoluzioneCPU) {
        for (int i = 0; i < DIM; i++) {
            int j = rand() % 9;
            swap(numeri[i], numeri[j]);
        }
    }

    // si prova ad inserire i numeri nella cella vuota seguendo le regole del sudoku
    for (int i = 0; i < DIM; i++) {
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

// funzione che cancella i numeri dalle celle in modo da rendere il sudoku giocabile 
// mat è un sudoku completo già risolto
// num è il numero dei numeri da togliere dalla matrice
void cavaNumeri(int mat[DIM][DIM], int num) {
    do {
        // genera numeri da 0 a 8
        int rig = rand() % 9;
        int col = rand() % 9;

        // cancella solo celle con numeri diversi da 0
        // la cancellazione avviene inserendo lo 0.
        if (mat[rig][col] != 0) {
            mat[rig][col] = 0;
            num--;
        }

        // continua a cancellare numeri finché non arriva a 0
    } while (num > 0);
}

// funzione ricorsiva che viene chiamata da verificaSudoku()
// restituisce un booleano che indica se il sudoku ha più di una soluzione oppure no.
bool sudokuSoluzioni(int mat[DIM][DIM], int& soluzioni) {
    int rig, col;

    // se la matrice non contiene celle vuote, allora vuol dire che il sudoku è valido
    if (!verificaMatriceVuota(mat, rig, col)) {
        // il sudoku è valido quindi la variabile soluzione viene incrementato
        soluzioni++;
        
        // restituisce un bool in base alla variabile soluzioni
        if (soluzioni <= 1) {
            // soluzione minore o uguale a 1
            // in questo modo continua a cercare di trovare altre soluzioni
            return true;
        } else {
            // soluzione maggiore di 1
            // siccome la soluzione è già maggiore di 1 quindi il sudoku è già invalido
            // non bisogna più cercare altre soluzioni quindi la funzione restituisce false
            return false;
        }
    }

    // Una volta identificata la cella vuota, si tenta di inserire i numeri da 1 a 9
    for (int num = 1; num <= DIM; num++) {
        // Viene effettuato il controllo per vedere se si può o meno inserire il numero nella cella vuota senza violare le regole
        if (controlloNumero(mat, rig, col, num)) {
            // Il numero è valido, quindi va inserito nella cella vuota
            mat[rig][col] = num;

            // Con il nuovo numero, si prova a chiamare la stessa funzione per ripetere gli stessi passaggi per le celle vuote successive
            if (!sudokuSoluzioni(mat, soluzioni)) {
                // Quando in una cella non si può inserire nessun numero, allora si torna alla cella precedente per cambiare il numero.
                // Quindi, qui si restituisce false per indicare che la soluzione non è stata trovata.
                return false;
            }

            // Reset della cella dopo la ricorsione
            // Necessario per ripristinare il valore della cella a 0 (vuota) e permettere all'algoritmo
            // di backtracking di esplorare tutte le possibili soluzioni
            mat[rig][col] = 0;
        }
    }

    // Se si è arrivati a questo punto, significa che i il numero inserito ha superato tutti i controllo e che i numeri successivi sono anche essi validi
    // quindi si restituisce true per indicare che la soluzione è stata trovata.
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