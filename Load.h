#ifndef  LOAD_H
#define LOAD_H

#include "Slime.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<Slime> LoadSlimes(const string& ruta){
    vector<Slime> out;
    ifstream file(ruta);
    string line;


    if(file.is_open() == false){
        cout << "No se abrio el archivo" << endl;
        return out;
    }

    while(getline(file,line)){
        if(line.empty() == true){
            continue;
        }
        else{
            stringstream ss;
            ss << line;

            string nombre;
            string tipo;
            string plortValStr;
            float plortVal;

            getline(ss, nombre, ',');
            getline(ss, tipo, ',');
            getline(ss, plortValStr, ',');

            plortVal = stof(plortValStr);

            out.push_back(Slime(nombre,tipo,plortVal));

        }
    }

    file.close();
    return out;

};

#endif