# Sudoku
## Salvataggio partite
### Struttura partita
```c++
struct partita{
    int mat[dim][dim]; //matrice del sudoku
    string inizioPartita; // DAY/MONTH/YEAR hh:mm:ss
    int tempoTrascorso; //misurato in secondi
    bool giocatore; //true = player --- false = computer
    bool stato; //true = in corso --- false = terminata
};
```
### Matrice partita
```c++
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
[0][0][0][0][0][0][0][0][0]
```
### File di salvataggio (/partita/storico)
```
Riga 1: Partitte vinte
Riga 2: Partite perse
```
### Ultima partita - Matrice (/partita/ultimaPartita/matrice)
```
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
```
### Ultima partita - Dati (/partita/ultimaPartita)
```
Riga 1: inizioPartita
Riga 2: tempoTrascorso
Riga 3: giocatore
Riga 4: stato
```
