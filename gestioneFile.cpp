#include <fstream>
#include <iostream>
#include <string>
#include "costanti.h"

using namespace std;

/**
 * @brief Controlla l'esistenza del file "storico.txt" e crea i file necessari per il gioco del Sudoku se non esiste.
 *
 * Se il file "storico.txt" non esiste, vengono creati i file "sudoku.txt", "soluzioneSudoku.txt", "modificheSudoku.txt", "suggerimentiDisponibili.txt" e "storico.txt".
 * Il file "storico.txt" viene inizializzato con i valori 0 0.
 */
void creazioneFile() {
    ifstream fileInput("storico.txt");

    if (!fileInput.is_open()) {
        ofstream fileOutput;

        // Crea i file necessari per il gioco del Sudoku se non esistono.
        fileOutput.open("sudoku.txt");
        fileOutput.close();

        fileOutput.open("soluzioneSudoku.txt");
        fileOutput.close();

        fileOutput.open("modificheSudoku.txt");
        fileOutput.close();

        fileOutput.open("suggerimentiDisponibili.txt");
        fileOutput.close();

        // Inizializza il file "storico.txt" con i valori 0 0.
        fileOutput.open("storico.txt");
        fileOutput << "0\n0";
        fileOutput.close();
    } else {
        fileInput.close();
    }
}

/**
 * @brief Aggiorna i contatori delle partite vinte e perse nel file "storico.txt" in base al risultato dell'ultima partita.
 * Legge i contatori attuali dal file, incrementa il contatore corretto in base al risultato della partita e sovrascrive i valori nel file.
 *
 * @param soluzione Booleano che indica se il giocatore ha vinto (true) o perso (false) l'ultima partita.
 */
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

/**
 * @brief Salva la partita attuale.
 *
 * sudoku >> "sudoku.txt".
 *
 * soluzioneSudoku >> "soluzioneSudoku.txt".
 *
 * modificheSudoku >> "modificheSudoku.txt".
 *
 * suggerimentiDisponibili >> "suggerimentiDisponibili.txt".
 *
 * @param sudoku La griglia di gioco attuale da salvare.
 * @param soluzioneSudoku La soluzione del Sudoku da salvare.
 * @param modificheSudoku Le modifiche apportate alla griglia di gioco da salvare.
 * @param suggerimentiDisponibili Il numero di suggerimenti disponibili da salvare.
 */
void salvaPartita(int sudoku[DIM][DIM], int soluzioneSudoku[DIM][DIM], int modificheSudoku[DIM][DIM], int suggerimentiDisponibili){
    // Output per la griglia di gioco, la soluzione del Sudoku e le modifiche.
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

    // Output per i suggerimenti disponibili.
    ofstream fileSuggerimentiDisponibili("suggerimentiDisponibili.txt");
    fileSuggerimentiDisponibili << suggerimentiDisponibili;
    fileSuggerimentiDisponibili.close();
}

/**
 * @brief Carica la partita da file.
 *
 * "sudoku.txt" >> sudoku.
 *
 * "soluzioneSudoku.txt" >> soluzioneSudoku.
 *
 * "modificheSudoku.txt" >> modificheSudoku.
 *
 * "suggerimentiDisponibili.txt" >> suggerimentiDisponibili.
 *
 * @param sudoku La matrice in cui caricare la griglia di gioco.
 * @param soluzioneSudoku La matrice in cui caricare la soluzione del Sudoku.
 * @param modificheSudoku La matrice in cui caricare le modifiche alla griglia di gioco.
 * @param suggerimentiDisponibili Il numero di suggerimenti disponibili da caricare.
 */
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

/**
 * @brief Carica la soluzione del Sudoku dalla matrice salvata nel file "soluzioneSudoku.txt" nella matrice 'soluzioneSudoku'.
 *
 * @param soluzioneSudoku La matrice in cui caricare la soluzione del Sudoku.
 */
void caricaSoluzione(int soluzioneSudoku[DIM][DIM]){
    ifstream fileSoluzioneSudoku("soluzioneSudoku.txt");

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            fileSoluzioneSudoku >> soluzioneSudoku[i][j];
        }
    }

    fileSoluzioneSudoku.close();
}

/**
 * @brief Stampa il contenuto di un file specificato.
 * I file che possono essere stampati sono: "regole.txt" e "asciiArt.txt".
 * regole.txt contiene le regole del Sudoku.
 * asciiArt.txt contiene la parola "sudoku" stilizzata sotto forma di ASCII art.
 *
 * @param nomeFile Il nome del file da stampare.
 */
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

/**
 * @brief Questa funzione apre il file "storico.txt" che contiene il numero di partite vinte e perse, e stampa queste informazioni a schermo.
 * In base alle vincite e alle perdite viene calcolato e stampato il numero totale di partite.
 */
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

/**
 * @brief Questa funzione chiede all'utente la conferma prima di eliminare il file "storico.txt".
 * Se l'utente conferma, il file viene eliminato e ricreato con i valori iniziali di vittorie e perdite impostati a 0.
 */
void resetStorico() {
    char scelta;

    do {
        cout << RED << "Sei sicuro di resettare lo storico? [s/n]: " << RESET;
        cin >> scelta;
    } while (scelta != 's' && scelta != 'n');
    
    if (scelta == 's') {
        remove("storico.txt");

        ofstream storico("storico.txt");

        storico << "0\n0";
        storico.close();

        cout << RED << "Lo storico è stato resettato \n" << RESET;
    }    
}
