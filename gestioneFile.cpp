#include <fstream>
#include <iostream>
#include "costanti.h"

using namespace std;

void creazioneFile(){
    ifstream fileInput("./Salvataggio/regole");

    if(!fileInput.is_open()){
        ofstream fileRegole("./Salvataggio/regole");
        fileRegole.close();

        ofstream fileSudoku("./Salvataggio/sudoku");
        fileSudoku.close();

        ofstream fileSoluzioneSudoku("./Salvataggio/soluzioneSudoku");
        fileSoluzioneSudoku.close();

        ofstream fileStorico("./Salvataggio/storico");
        fileStorico << "0\n0";
        fileStorico.close();
    } else {
        fileInput.close();
    }
}

void aggiornaStorico(bool soluzione){
    int partiteVinte, partitePerse;

    ifstream fileInput("./Salvataggio/storico");

    fileInput >> partiteVinte >> partitePerse;

    if(soluzione) {
        partiteVinte++;
        cout << "Il giocatore ha vinto!\n";
    }
    else {
        partitePerse++;
        cout << "Il giocatore ha perso!\n";
    }
    fileInput.close();

    ofstream fileOutput("./Salvataggio/storico");
    fileOutput << partiteVinte << '\n' << partitePerse;
    fileOutput.close();
}

void salvaPartita(int mat[DIM][DIM], int soluzioneSudoku[DIM][DIM]){
    //output mat
    ofstream fileSudoku("./Salvataggio/sudoku");
    for(int i=0; i < DIM; i++){
        for(int p=0; p < DIM; p++){
            fileSudoku << mat[i][p] << " ";
        }
        fileSudoku << '\n';
    }
    fileSudoku.close();

    //output soluzioneSudoku
    ofstream fileSoluzioneSudoku("./Salvataggio/soluzioneSudoku");
    for(int i=0; i < DIM; i++){
        for(int p=0; p < DIM; p++){
            fileSoluzioneSudoku << soluzioneSudoku[i][p] << " ";
        }
        fileSoluzioneSudoku << '\n';
    }
    fileSoluzioneSudoku.close();
}