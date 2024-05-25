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
        cout << GREEN << "Il giocatore ha vinto!\n" << RESET;
    }
    else {
        partitePerse++;
        cout << RED <<  "Il giocatore ha perso!\n" << RESET;
    }
    fileInput.close();

    ofstream fileOutput("storico.txt");
    fileOutput << partiteVinte << '\n' << partitePerse;
    fileOutput.close();
}

void salvaPartita(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM]){
    //output mat
    ofstream fileSudoku("sudoku.txt");
    for(int i=0; i < DIM; i++){
        for(int j=0; j < DIM; j++){
            fileSudoku << sudoku[i][j] << " ";
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

void caricaPartita(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM]) {
    ifstream fileSudoku("sudoku.txt");
    ifstream fileSoluzioneSudoku("soluzioneSudoku.txt");

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            fileSudoku >> sudoku[i][j];
            fileSoluzioneSudoku >> soluzioneSudoku[i][j];
        }
    }

    fileSudoku.close();
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

void stampaStorico() {
    ifstream storico;
    int vittorie, perdite;

    storico.open("storico.txt");

    storico >> vittorie;
    storico >> perdite;

    cout << LIGHT_BLUE;
    cout << "vittorie: " << vittorie << endl;
    cout << "perdite: " << perdite << endl;
    cout << "totali: " << vittorie + perdite << endl;
    cout << RESET;
}