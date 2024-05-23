#include <fstream>
#include <iostream>
#include <string>
#include "costanti.h"

using namespace std;

void creazioneFile(){
    ifstream fileInput("storico.txt");

    if(!fileInput.is_open()){
        ofstream fileOutput;
        
        fileOutput.open("sudoku.txt");
        fileOutput.close();

        fileOutput.open("soluzioneSudoku.txt");
        fileOutput.close();

        fileOutput.open("storico.txt");
        fileOutput << "0\n0";
        fileOutput.close();

    } else {
        fileInput.close();
    }
}

void aggiornaStorico(bool soluzione){
    int partiteVinte, partitePerse;

    ifstream fileInput("storico.txt");

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

    ofstream fileOutput("storico.txt");
    fileOutput << partiteVinte << '\n' << partitePerse;
    fileOutput.close();
}

void salvaPartita(int mat[DIM][DIM], int soluzioneSudoku[DIM][DIM]){
    //output mat
    ofstream fileSudoku("sudoku.txt");
    for(int i=0; i < DIM; i++){
        for(int j=0; j < DIM; j++){
            fileSudoku << mat[i][j] << " ";
        }
        fileSudoku << '\n';
    }
    fileSudoku.close();

    //output soluzioneSudoku
    ofstream fileSoluzioneSudoku("soluzioneSudoku.txt");
    for(int i=0; i < DIM; i++){
        for(int j=0; j < DIM; j++){
            fileSoluzioneSudoku << soluzioneSudoku[i][j] << " ";
        }
        fileSoluzioneSudoku << '\n';
    }
    fileSoluzioneSudoku.close();
}

void stampaRegole() {
    ifstream regole;
    string testo;

    regole.open("regole.txt");

    cout << endl;
    getline(regole, testo);
    while (!regole.eof()) {
        cout << testo << endl;
        getline(regole, testo);
    }
    cout << endl;

    regole.close();
}
