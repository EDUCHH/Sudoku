#include <iostream>

using namespace  std;

const int DIM3 = 9;

int sceltaGiocatore(){
    int min=0, max = 1;
    int giocatore;

    do{
        cout << "Inserisci il giocatore (0-CPU // 1-Player): \n";
        cin >> giocatore;

        if(giocatore < min || giocatore > max){
            cout << "Input errato!\n";
        }
    }while(giocatore < min || giocatore > max);

    return giocatore;
}
//0: CPU ----- 1: PLAYER

bool exitPartita(){
    char input;

    do{
        cout << "Vuoi uscire dalla partita? (S/n)\n";
        cin >> input;

        if(input != 'S' && input != 'n'){
            cout << "Input errato!\n";
        }
    }while(input != 'S' && input != 'n');

    if(input == 'S'){
        return true;
    } else{
        return false;
    }
}

bool partitaTerminata(int mat[DIM3][DIM3]){
    for(int i=0; i < DIM3; i++){
        for(int p=0; p < DIM3; p++){
            if(mat[i][p] == 0) return false;
        }
    }

    return true;
}
//FALSE: SUDOKU NON COMPLETO ----- TRUE: SUDOKU COMPLETO

void inputMossa(int mat[DIM3][DIM3]){
    int numero;
    int min, max;
    bool restart;
    int pos[2];

    //Input numero
    min = 1; max = 9;
    do{
        cout << "Inserisci un numero: \n";
        cin >> numero;

        if(numero < min || numero > max){
            cout << "Input errato!\n";
        }
    }while(numero < min || numero > max);

    //posizione numero
    min = 0; max = 8;
    do{
        restart=false;
        cout << "Inserisci la posizione in cui vuoi inserire il numero (r-c): \n";
        cin >> pos[0] /*righe*/ >> pos[1] /*colonne*/;

        if((pos[0] < min || pos[0] > max) || (pos[1] < min || pos[1] > max)){ //controllo dati dentro alla tabella
            cout << "Input errato!\n";
            restart = true;
        } else{
            if(mat[pos[0]][pos[1]] != 0){
                cout << "Cella gia' occupata!\n";
                restart = true;
            }
            else{
                mat[pos[0]][pos[1]] = numero;
            }
        }

    }while(restart);
}
//POS[0]: RIGA ----- POS[1]: COLONNA

bool verificaVittoria(int soluzioneSudoku[DIM3][DIM3], int mat[DIM3][DIM3]){
    for(int i=0; i < DIM3; i++){
        for(int p=0; p < DIM3; p++){
            if(soluzioneSudoku[i][p] != mat[i][p]) {
                return false;
            }
        }
    }

    return true;
}
//TRUE: SUDOKU CORRETTO ----- FALSE: SUDOKU SBAGLIATO