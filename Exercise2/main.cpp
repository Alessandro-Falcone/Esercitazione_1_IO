#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

double cambioIntervallo(double numFileInput) // funzione che fa passare i valori dall'intervallo [1,5] all'intervallo [-1,2]
{
    double numFileOutput;

    numFileOutput = (3./4. * numFileInput) - 7./4.;

    // per costruire la funzione di cambio intervallo ho fatto in questo modo
    // [a,b] = [1,5] -> [-1,1] -> [c,d] = [-1,2]
    // dove per passare dall'intervallo [1,5] a [-1,1] (prima freccia) ho usato
    // la funzione di cambio intervallo x = ((b-a) * t) + (b+a)/2 dove t = (2 * x - (b+a)) / (b-a)
    // mentre per passare dall'intervallo [-1,1] a [-1,2] (seconda freccia) ho usato
    // la funzione di cambio di intervallo y = ((d-c) * t) + (d+c)/2
    // a questo punto sono andato a sostituire l'espressione di t nella funzione y = ((d-c) * t) + (d+c)/2 in quanto
    // i valori di t sono rappresentati dall'intervallo [-1,1] quindi la t è la stessa sia per x = ((b-a) * t) + (b+a)/2
    // sia per y = ((d-c) * t) + (d+c)/2 e infine ho ottenuto
    // la funzione di cambio intervallo y = (((d-c)/2) * (((2 * x) - (b+a))/(b-a))) + (d+c)/2
    // dove ho sostituito i valori [a,b] = [1,5] e i valori [c,d] = [-1,2] e
    // ho chiamato la variabile x numFileInput e la variabile y numFileOutput

    return numFileOutput;
}


int main(){

    int numeroRigheFileInput = 0;
    double valFileInput = 0;
    double numCambioIntervalloOut = 0;
    double sommaOut = 0;
    double mediaOut = 0;

    ifstream nomeFileInput("data.csv"); // apro il file di input

    ofstream nomeFileOutput("result.csv"); // apro il file di output

    if(nomeFileInput.fail()){
        cerr << "il file di input che hai inserito non è stato trovato\n" << endl; // Il file di input che hai inserito non e' stato trovato\n
        return 1;
    }

    string header;
    nomeFileOutput << header << "# N mean\n";

    while(nomeFileInput >> fixed >> setprecision (16) >> scientific >> valFileInput){ // leggo dal file di input tutti i valori

        numCambioIntervalloOut = cambioIntervallo(valFileInput);
        // attraverso la funzione cambioIntervallo i valori del file in input (valFileInput)
        // che sono nell'intervallo [1,5] passano nell'intervallo [-1,2]
        // e una volta fatto questo vado a mettere i valori, che adesso sono nell'intervallo [-1,2], nella variabile numCambioIntervalloOut

        sommaOut += numCambioIntervalloOut;
        // prende ogni valore nuovo che è nell'intervallo [-1,2] e fa la somma con la sommaOut precedente

        mediaOut = sommaOut/(numeroRigheFileInput+1);
        // divide la sommaOut (valori sommati) per il numero di valori di cui è stata fatta la somma e inserisce il risultato nella variabile mediaOut
        // è necessario fare numeroRigheFileInput+1 in quanto si parte a contare da 0

        nomeFileOutput << numeroRigheFileInput+1 << " " << fixed <<  setprecision (16) << scientific << mediaOut << "\n";
        // scrivo sul file di output tutti i valori che ho calcolato e che ho messo all'interno del variabile mediaOut

        numeroRigheFileInput++; // contatore delle righe del file

    }

    nomeFileInput.close(); // chiudo il file di input

    nomeFileOutput.close(); // chiudo il file di output

    return 0;
}
