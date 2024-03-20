#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <math.h>

using namespace std;

double cambioIntervallo(double numFileInput)
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
    const int N = 8000;
    bool dimFile = true;
    double valFileInput = 0;
    double numFileIn[N];
    double numCambioIntervalloOut[N];
    double sommaOut[N];
    double mediaOut[N];

    ifstream nomeFileInput("data.csv"); // apro il file di input

    if(nomeFileInput.is_open()){

        while(nomeFileInput >> fixed >> setprecision (16) >> scientific >> valFileInput){ // leggo dal file di input tutti i valori

            if(numeroRigheFileInput < N && dimFile == true){
               numFileIn[numeroRigheFileInput] = valFileInput; // copio i valori che ho letto in un vettore
                                                               // se il numero di righe del file è minore della costante intera (const int) N
                                                               // che rappresenta la dimensione dei vettori (double) dichiarata all'inizio del file

            }else{
               dimFile = false;
            }
            numeroRigheFileInput++;
        }

    }else{

        cerr << "Il file di input che hai inserito non e' stato trovato\n" << endl;
        return 1;
    }

    if(dimFile == false){
        cout << "Il numero di righe del file ha una dimensione piu' grande della dimensione del vettore\n" << endl;

    }else{

        for(int i = 0; i < numeroRigheFileInput; i++){
            numCambioIntervalloOut[i] = cambioIntervallo(numFileIn[i]); // funzione che fa passare i valori dall'intervallo [1,5] all'intervallo [-1,2]
        }
    }

    nomeFileInput.close(); // chiudo il file di input

    ofstream nomeFileOutput("result.csv"); // apro il file di output

    if(nomeFileOutput.is_open() && dimFile == true){

        string header;
        nomeFileOutput << header << "# N mean\n";

        for(int i = 0; i < numeroRigheFileInput; i++){ // inserisco la media dei valori che adesso sono nell'intervallo [-1,2] nel vettore mediaOut

            // if(i == 0){
            //    mediaOut[i] = numCambioIntervalloOut[i]; // il primo valore della media rimane uguale
            // }

            // if(i == 1){
            //    mediaOut[i] = 1./2. * (numCambioIntervalloOut[i] + numCambioIntervalloOut[i-1]); // il secondo valore della media è dato dalla somma dei primi due valori divisa per 2
            // }

            // if(i > 1){
            //    mediaOut[i] = abs(1./4. * (numCambioIntervalloOut[i-2] + numCambioIntervalloOut[i-1] + 2 * numCambioIntervalloOut[i])); // tutti gli altri valori seguono la seguente formula
            //     }

            if(i == 0){

                 mediaOut[i] = numCambioIntervalloOut[i]; // il primo valore della media rimane uguale

                 sommaOut[i] = numCambioIntervalloOut[i];
            }

            if(i == 1){

                mediaOut[i] = 1./2. * (numCambioIntervalloOut[i] + numCambioIntervalloOut[i-1]); // il secondo valore della media è dato dalla somma dei primi due valori divisa per 2

                sommaOut[i] = numCambioIntervalloOut[i-1] + numCambioIntervalloOut[i];

            }

           if(i > 1){
               sommaOut[i] = sommaOut[i-1] + numCambioIntervalloOut[i];
               mediaOut[i] = sommaOut[i]/(i+1);
           }

            cout << i+1 << " " << fixed <<  setprecision (16) << scientific << mediaOut[i] << "\n"; // scrivo sul file di output tutti i valori che ho calcolato e che ho messo all'interno del vettore mediaOut
        }
    }

    nomeFileOutput.close(); // chiudo il file di output

    return 0;
}
