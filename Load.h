#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Dllist.h"
#include "Area.h"
#include "Corral.h"

using namespace std;

int getDefaultAreaCapacity(const string& areaName) {
    if (areaName == "The Ranch") return 8;
    if (areaName == "The Grotto" || areaName == "The Lab") return 5;
    if (areaName == "The Overgrowth" || areaName == "The Docks") return 4;
    return 8;
}

DList<Area> LoadRancho(const string& ruta) {
    DList<Area> areas;
    ifstream file(ruta);
    string line;

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << ruta << endl;
        return areas;
    }

    getline(file, line); // Saltar encabezado

    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back();

        stringstream ss(line);
        string areaName, id, type, quanStr, capStr, plortStr, foodStr;

        getline(ss, areaName, ',');
        getline(ss, id, ',');
        getline(ss, type, ',');
        getline(ss, quanStr, ',');
        getline(ss, capStr, ',');
        getline(ss, plortStr, ',');
        getline(ss, foodStr, ',');

        if (areaName.empty() || id.empty()) continue;

        Corral c(id, type, stoi(quanStr), stoi(capStr), stof(plortStr), stoi(foodStr));

        bool found = false;
        DListIterator<Area> itr(&areas);
        for (itr.begin(); !itr.end(); ++itr) {
            if (itr().getName() == areaName) {
                itr().addCorral(c);
                found = true;
                break;
            }
        }

        if (!found) {
            Area nuevaArea(areaName, getDefaultAreaCapacity(areaName));
            nuevaArea.addCorral(c);
            areas.add(nuevaArea);
        }
    }

    file.close();
    return areas;
}

void SaveRancho(DList<Area>& areas, const string& ruta) {
    ofstream file(ruta);

    if (!file.is_open()) {
        cout << "No se pudo crear o abrir el archivo: " << ruta << endl;
        return;
    }

    file << "Area,CorralID,TipoSlime,Cantidad,Capacidad,ValorPlort,ComidaPorSlime\n";

    DListIterator<Area> itr(&areas);
    for (itr.begin(); !itr.end(); ++itr) {
        string areaName = itr().getName();
        vector<Corral> corrales = itr().getCorralesVector();

        for (size_t i = 0; i < corrales.size(); i++) {
            file << areaName << ","
                 << corrales[i].getID() << ","
                 << corrales[i].getType() << ","
                 << corrales[i].getQuantity() << ","
                 << corrales[i].getCapacity() << ","
                 << corrales[i].getPlortVal() << ","
                 << corrales[i].getFoodPerSlime() << "\n";
        }
    }

    file.close();
    cout << "Datos guardados correctamente en: " << ruta << endl;
}

#endif