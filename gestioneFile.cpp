#include <fstream>

void creazioneFile(){
    ifstream fileInput("./Salvataggio/regole");

    if(!fileInput.is_open()){
        ofstream fileRegole("./Salvataggio/regole");
        fileRegole.close();

        ofstream filePartita("./Salvataggio/partita");
        filePartita.close();

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
    }
    else {
        partitePerse++;
    }
    fileInput.close();

    ofstream fileOutput("./Salvataggio/storico");
    fileOutput << partiteVinte << '\n' << partitePerse;
    fileOutput.close();
}