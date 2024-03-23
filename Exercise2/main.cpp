#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

double cambioIntervallo(double numFileInput) // Funzione che fa passare i valori dall'intervallo [1,5] all'intervallo [-1,2]
{
    double numFileOutput = 0;

    numFileOutput = (3./4. * numFileInput) - 7./4.;

    // Per costruire la funzione di cambio intervallo ho fatto in questo modo
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

    unsigned int numeroRigheFileInput = 0;
    double valFileInput = 0;
    double numCambioIntervalloOut = 0;
    double sommaOut = 0;
    double mediaOut = 0;

    ifstream fileInput("data.csv"); // Apro il file di input in modalità lettura

    ofstream fileOutput("result.csv"); // Apro il file di output in modalità scrittura

    if(fileInput.fail()){ // Controllo che il file di input esista e sia stato aperto correttamente

        cerr << "il file di input che hai inserito non e' stato trovato\n" << endl;
        // Messaggio di errore che dice che il file di input inserito non e' stato trovato

        return 1;
    }

    string header;
    fileOutput << header << "# N mean\n"; // Inserisco stringa all'inizio del file di output

    while(fileInput >> fixed >> setprecision (16) >> scientific >> valFileInput){ // Leggo dal file di input tutti i valori

        numCambioIntervalloOut = cambioIntervallo(valFileInput);
        // Attraverso la funzione cambioIntervallo i valori del file in input (valFileInput)
        // che sono nell'intervallo [1,5] passano nell'intervallo [-1,2],
        // una volta fatto questo inserisco i valori appena calcolati, che adesso sono nell'intervallo [-1,2],
        // nella variabile numCambioIntervalloOut.
        // Ripeto questa operazione fino a che non ho raggiunto la fine del file che sto leggendo

        sommaOut += numCambioIntervalloOut;
        // Nella variabile sommaOut vado ad inserire la somma tra ogni valore nuovo (numCambioIntervalloOut), che è nell'intervallo [-1,2],
        // e la sommaOut precedente.
        // Ripeto questa operazione fino a che non ho raggiunto la fine del file che sto leggendo

        mediaOut = sommaOut/(numeroRigheFileInput+1);
        // Nella variabile mediaOut inserisco il risultato della divisione tra la sommaOut (valori sommati)
        // e il numero di valori di cui è stata fatta la somma.
        // E' necessario sommare numeroRigheFileInput+1 in quanto si parte a contare da 0
        // Ripeto questa operazione fino a che non ho raggiunto la fine del file che sto leggendo

        fileOutput << numeroRigheFileInput+1 << " " << fixed <<  setprecision (16) << scientific << mediaOut << "\n";
        // Scrivo sul file di output tutti i valori che ho calcolato, che sono stati inseriti all'interno del variabile mediaOut
        // Ripeto questa operazione fino a che non ho raggiunto la fine del file che sto leggendo

        numeroRigheFileInput++; // Contatore delle righe del file
    }

    // Esco dal ciclo while ho letto tutto il file di input "data.csv" e ho finito di scrivere sul file di output "result.csv"

    fileInput.close(); // Chiudo il file di input

    fileOutput.close(); // Chiudo il file di output

    return 0;
}

// Finisce il programma
// Apro il file "result.csv" e verifico che i valori siano corretti,
// se gli ultimi numeri convergono verso il punto medio dell'intervallo [-1,2] ovvero (-1+2)/2 = 0.5 sono corretti
