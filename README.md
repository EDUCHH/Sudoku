# Sudoku
Sudoku implementato utilizzando il linguaggio di programmazione c++.

## Come installare ed eseguire il programma
A seconda del sistema operativo in uso, i passaggi possono essere leggermente diversi.

### GNU/Linux
1. Assicurare di avere **git** installato: `git version`
2. Assicurare di avere **gcc** installato: `gcc --version` 
3. Clonare il repo usando **git**: `git clone https://github.com/EDUCHH/Sudoku.git`
4. Entrare nella directory `Sudoku`: `cd Sudoku`
5. Compilare il programma usando **g++**: `g++ -o sudoku.out main.cpp`
6. Eseguire il programma: `./sudoku.out`

#### Installare git e gcc
Se non hai questi programmi installati, puoi installarli con il gestore di pacchetti.

**Arch Linux**: `sudo pacman -S git gcc`

**Debian**: `sudo apt install git gcc`

### Windows
1. Assicurare di avere **git** installato: `git version`
2. Assicurare di avere **gcc** installato: `gcc --version` 
3. Clonare il repo usando **git**: `git clone https://github.com/EDUCHH/Sudoku.git`
4. Entrare nella directory `Sudoku`: `cd Sudoku`
5. Compilare il programma usando **g++**: `g++ -o sudoku.exe main.cpp`
6. Eseguire il programma: `./sudoku.exe`

#### Installare git e gcc
Se non hai questi programmi installati, puoi installarli accedendo al sito ufficiale di [git](https://git-scm.com/) e di [mingw-64](https://www.mingw-w64.org/).

## Inserimento numero
Per inserire il numero, scrivere prima la riga poi la colonna.

Fare attenzione che le indici della matrice sono da 0 a 8, invece che da 1 a 9.

Quando si sta inserendo un numero -1 per uscire.

Quando si sta inserendo un numero -2 per avere un suggerimento, c'è un suggerimento disponibile ogni 10 numeri da inserire.

Quando si sta inserendo le coordinate inserire -1 per tornale alla fase di inserimento del numero.

## Storico
Lo storico viene aggiornato solo quando il giocatore completa un sudoku. Di conseguenza, se la CPU risolve il sudoku, lo storico non viene aggiornato.

## Doxygen
Doxygen può essere utilizzato per generare le documentazioni di questo progetto.
Le documentazioni una volta generate sono salvati nella cartella `./doxygen`

Comando da usare per generare le documentazioni: `doxygen Doxyfile`

## Licenza
Il progetto è distribuito con **licenza 0BSD**. Controllare il file **[LICENSE](LICENSE)** per i dettagli.
