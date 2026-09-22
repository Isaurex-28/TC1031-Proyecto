#include "Load.h"
#include "Slime.h"
#include "Sort.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(){

    vector<Slime> corral = LoadSlimes("slimes.csv");
    bool menu = true;

    while(menu){
        int firstInt;
        cout << "Que deseas hacer?" << endl;
        cout << "1- Ver slimes" << endl;
        cout << "2- Ordenar slimes" << endl;
        cout << "3- Salir" << endl;
        cout << "Escribe el numero: ";
        cin >> firstInt;

        switch(firstInt){
            case 1: {
                for(int i = 0; i < corral.size(); i++){
                    cout << "Nombre: "<< corral[i].getNombre() << "\nTipo: " 
                    << corral[i].getTipo() <<  "\nValor del Plort: $"
                    << corral[i].getPlortVal() << "\n" << endl;
                }
                break;
            }
            case 2: {
                int secondInt;
                cout << "\nCon que parametro deseas ordenar?" << endl;
                cout << "1- Valor del Plort" << endl;
                cout << "Escribe el numero: ";
                cin >> secondInt;

                switch(secondInt){
                    case 1: {
                        vector<Slime> sorted = mergeSort(corral);
                        for(int i = 0; i < sorted.size(); i++){
                            cout << "Nombre: "<< sorted[i].getNombre() << "\nTipo: " 
                            << sorted[i].getTipo() <<  "\nValor del Plort: $"
                            << sorted[i].getPlortVal() << "\n" << endl;
                        }
                        break;
                    }
                    default: {
                        cout << "Opcion invalida." << endl;
                        break;
                    }
                }
                break;
            }
            case 3: {
                menu = false;
                break;
            }
            default: {
                cout << "Opcion invalida." << endl;
                break;
            }             

        }

    }
    return 0;
}