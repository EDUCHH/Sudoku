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

## Licenza
Il progetto è distribuito con **licenza SBD0**. Controllare il file **LICENSE** per i dettagli