#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "generaSudoku.cpp"

using namespace std;


//cose
void stampaSudoku(int mat[DIM][DIM]){
    cout << "+-------------------------+\n";
    cout << "| " << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " || " << mat[0][3] << " " << mat[0][4] << " " << mat[0][5] << " || " << mat[0][6] << " " << mat[0][7] << " " << mat[0][8] << " |\n";
    cout << "| " << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " || " << mat[1][3] << " " << mat[1][4] << " " << mat[1][5] << " || " << mat[1][6] << " " << mat[1][7] << " " << mat[1][8] << " |\n";
    cout << "| " << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " || " << mat[2][3] << " " << mat[2][4] << " " << mat[2][5] << " || " << mat[2][6] << " " << mat[2][7] << " " << mat[2][8] << " |\n";
    cout << "|-------++-------++-------|\n";
    cout << "| " << mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " || " << mat[3][3] << " " << mat[3][4] << " " << mat[3][5] << " || " << mat[3][6] << " " << mat[3][7] << " " << mat[3][8] << " |\n";
    cout << "| " << mat[4][0] << " " << mat[4][1] << " " << mat[4][2] << " || " << mat[4][3] << " " << mat[4][4] << " " << mat[4][5] << " || " << mat[4][6] << " " << mat[4][7] << " " << mat[4][8] << " |\n";
    cout << "| " << mat[5][0] << " " << mat[5][1] << " " << mat[5][2] << " || " << mat[5][3] << " " << mat[5][4] << " " << mat[5][5] << " || " << mat[5][6] << " " << mat[5][7] << " " << mat[5][8] << " |\n";
    cout << "|-------++-------++-------|\n";
    cout << "| " << mat[6][0] << " " << mat[6][1] << " " << mat[6][2] << " || " << mat[6][3] << " " << mat[6][4] << " " << mat[6][5] << " || " << mat[6][6] << " " << mat[6][7] << " " << mat[6][8] << " |\n";
    cout << "| " << mat[7][0] << " " << mat[7][1] << " " << mat[7][2] << " || " << mat[7][3] << " " << mat[7][4] << " " << mat[7][5] << " || " << mat[7][6] << " " << mat[7][7] << " " << mat[7][8] << " |\n";
    cout << "| " << mat[8][0] << " " << mat[8][1] << " " << mat[8][2] << " || " << mat[8][3] << " " << mat[8][4] << " " << mat[8][5] << " || " << mat[8][6] << " " << mat[8][7] << " " << mat[8][8] << " |\n";
    cout << "+-------------------------+\n";
}
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
} //0: CPU ----- 1: PLAYER

//partita
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
bool partitaTerminata(int mat[DIM][DIM]){
    for(int i=0; i < DIM; i++){
        for(int p=0; p < DIM; p++){
            if(mat[i][p] == 0) return false;
        }
    }

    return true;
} //FALSE: SUDOKU NON COMPLETO ----- TRUE: SUDOKU COMPLETO
void inputMossa(int mat[DIM][DIM]){
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
} //POS[0]: RIGA ----- POS[1]: COLONNA
bool verificaVittoria(int soluzioneSudoku[DIM][DIM], int mat[DIM][DIM]){
    for(int i=0; i < DIM; i++){
        for(int p=0; p < DIM; p++){
            if(soluzioneSudoku[i][p] != mat[i][p]) {
                return false;
            }
        }
    }

    return true;
} //TRUE: SUDOKU CORRETTO ----- FALSE: SUDOKU SBAGLIATO

void avviaPartita(){
    int soluzioneSudoku[DIM][DIM];

    initMatrice(soluzioneSudoku);
    generaSudoku(soluzioneSudoku);

    //copia matrice
    int mat[DIM][DIM];
    //copiaMatrice(mat, soluzioneSudoku);
    //cavaNumeri(mat);

    if(sceltaGiocatore()){
        //player
        while(!partitaTerminata(mat)){
            inputMossa(mat);
            if(exitPartita()){
                return;
            }
        }
        if(verificaVittoria(soluzioneSudoku, mat)){
            //+1 partite vinte
            int pariteVinte, partitePerse;
            ifstream fileInput("./Salvataggio/storico");
            fileInput >> partiteVinte >> partitePerse;
            fileInput.close();

            pariteVinte++;

            ofstream fileOutput("./Salvataggio/storico");
            fileOutput << partiteVinte << '\n' << partitePerse;
        }
        else{
            //+1 partite perse
            int pariteVinte, partitePerse;
            ifstream fileInput("./Salvataggio/storico");
            fileInput >> partiteVinte >> partitePerse;
            fileInput.close();

            paritePerse++;

            ofstream fileOutput("./Salvataggio/storico");
            fileOutput << partiteVinte << '\n' << partitePerse;
        }
    } else{
        //cpu
    }
}
int menu(){
    int min=1, max=6, opzione;

    cout << "1. Avvia una partita \n";
    cout << "2. Carica una partita \n";
    cout << "3. Salva ultima partita \n";
    cout << "4. Vedere le regole \n";
    cout << "5. Storico delle partite \n";
    cout << "6. Esci dal gioco \n";

    do{
        cout << "Inserisci un'opzione: ";
        cin >> opzione;

        if(opzione < min || opzione > max){
            cout << "Input errato! \n";
        }
    }while(opzione < min || opzione > max);

    return opzione;
}

int main(){
    while(true){
        int opzione = menu();

        switch (opzione) {
            case 1:
                //Avvia una partita
                avviaPartita();
                break;
            case 2:
                //Carica una partita
                break;
            case 3:
                //Salva ultima partita
                break;
            case 4:
                //Vedere le regole
                break;
            case 5:
                //Storico delle partite
                break;
            case 6:
                //Esci dal gioco
                return 0;
        }
    }
}