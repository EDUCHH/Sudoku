
#include <fstream>
#include <iostream>
#include <string>
#include "costanti.h"

using namespace std;

// Questa funzione controlla se il file "storico.txt" esiste. Se non esiste crea i file "sudoku.txt", "soluzioneSudoku.txt" e "storico.txt"
// Il file "storico.txt" viene inizializzato con valore 0 0;
// I file creati sono "sudoku.txt" per la griglia di gioco, "soluzioneSudoku.txt" per la soluzione del Sudoku e "storico.txt" per lo storico delle partite.
void creazioneFile() {
    ifstream fileInput("storico.txt");

    if(!fileInput.is_open()){
        ofstream fileOutput;
        
        fileOutput.open("sudoku.txt");
        fileOutput.close();

        fileOutput.open("soluzioneSudoku.txt");
        fileOutput.close();

        fileOutput.open("modificheSudoku.txt");
        fileOutput.close();

        fileOutput.open("suggerimentiDisponibili.txt");
        fileOutput.close();

        fileOutput.open("storico.txt");
        fileOutput << "0\n0";
        fileOutput.close();

    } else {
        fileInput.close();
    }
}

// Questa funzione legge il numero di partite vinte e perse dal file "storico.txt", aggiorna i contatori in base al risultato dell'ultima partita
// e sovrascrive i valori nel file "storico.txt" con i nuovi conteggi.
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

// Questa funzione salva la griglia di gioco attuale 'sudoku' e la sua soluzione 'soluzioneSudoku' nei file "sudoku.txt" e "soluzioneSudoku.txt" rispettivamente.
// Ogni numero della griglia viene separato da uno spazio e ogni riga termina con un carattere di nuova linea.
void salvaPartita(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM], int modificheSudoku[DIM][DIM], int suggerimentiDisponibili){
    //output mat
    ofstream fileSudoku("sudoku.txt");
    ofstream fileSoluzioneSudoku("soluzioneSudoku.txt");
    ofstream fileModificheSudoku("modificheSudoku.txt");

    for(int i=0; i < DIM; i++){
        for(int j=0; j < DIM; j++){
            fileSudoku << sudoku[i][j] << " ";
            fileSoluzioneSudoku << soluzioneSudoku[i][j] << " ";
            fileModificheSudoku << modificheSudoku[i][j] << " ";
        }
        fileSudoku << '\n';
        fileSoluzioneSudoku << '\n';
        fileModificheSudoku << '\n';
    }
    
    fileSudoku.close();
    fileSoluzioneSudoku.close();
    fileModificheSudoku.close();

    ofstream fileSuggerimentiDisponibili("suggerimentiDisponibili.txt");
    fileSuggerimentiDisponibili << suggerimentiDisponibili;
    fileSuggerimentiDisponibili.close();
}

// Questa funzione carica la griglia di gioco salvata nel file "sudoku.txt" nella matrice 'sudoku' e la relativa soluzione salvata in "soluzioneSudoku.txt"
// nella matrice 'soluzioneSudoku'.
void caricaPartita(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM], int modificheSudoku[DIM][DIM], int suggerimentiDisponibili) {
    ifstream fileSudoku("sudoku.txt");
    ifstream fileSoluzioneSudoku("soluzioneSudoku.txt");
    ifstream fileModificheSudoku("modificheSudoku.txt");

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            fileSudoku >> sudoku[i][j];
            fileSoluzioneSudoku >> soluzioneSudoku[i][j];
            fileModificheSudoku >> modificheSudoku[i][j];
        }
    }

    fileSudoku.close();
    fileSoluzioneSudoku.close();
    fileModificheSudoku.close();

    ifstream fileSuggerimentiDisponibili("suggerimentiDisponibili.txt");
    fileSuggerimentiDisponibili >> suggerimentiDisponibili;
    fileSuggerimentiDisponibili.close();
}

// Questa funzione carica la soluzione del Sudoku dalla matrice salvata nel file "soluzioneSudoku.txt" nella matrice 'soluzioneSudoku'.
void caricaSoluzione(int soluzioneSudoku[DIM][DIM]){
    ifstream fileSoluzioneSudoku("soluzioneSudoku.txt");

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            fileSoluzioneSudoku >> soluzioneSudoku[i][j];
        }
    }

    fileSoluzioneSudoku.close();
}

// Questa funzione stampa il contetune del file.
// Il nome del file è contenuto nella variabile nomeFile di tipo string.
// I file che vengono stampati attraverso questa funzione sono: regole.txt e asciiArt.txt.
// regole.txt contiene le regole del sudoku.
// asciiArt.txt contiene la parola "sudoku" stilizzato sottoforma di ascii art. 
void stampaFile(string nomeFile) {
    ifstream file;
    string testo;

    file.open(nomeFile);

    cout << endl;
    getline(file, testo);
    while (!file.eof()) {
        cout << testo << endl;
        getline(file, testo);
    }
    cout << endl;

    file.close();
}

// Funzione per stampare lo storico delle partite con il numero di vittorie, perdite e partite totali.
// Questa funzione apre il file "storico.txt" che contiene il numero di partite vinte e perse, e stampa queste informazioni a schermo.
// In base alle vincite e alle perdite viene calcolato e stampato il numero di partite totali.
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
