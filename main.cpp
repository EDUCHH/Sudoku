#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int dim=9;
const int numPartiteMax=100;

struct partita{
    int mat[dim][dim]; //matrice del sudoku
    string inizioPartita; // DAY/MONTH/YEAR hh:mm:ss
    int tempoTrascorso; //misurato in secondi
    bool giocatore; //true = player --- false = computer
    bool stato; //true = in corso --- false = terminata
};

//menu di gioco
void menu(){
    int min=1, max=4, opzione;

    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Vedere le regole \n";
    cout << "4. Storico delle partite \n";
    cout << "5. Esci dal gioco \n";

    do{
        cout << "Inserisci un'opzione: ";
        cin >> opzione;

        if(opzione < min || opzione > max){
            cout << "Input errato! \n";
        }
    }while(opzione < min || opzione > max);

    switch (opzione) {
        case 1:
            //Avvia una partita

            break;
        case 2:
            //Carica una partita
            break;
        case 3:
            //Vedere le regole
            break;
        case 4:
            //Esci dal gioco
            exit(EXIT_SUCCESS);
            break;
    }
}


int main() {
    int sudoku[9][9];

    int numero_partite;


    return 0;
}
