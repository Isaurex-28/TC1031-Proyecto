#ifndef AREA_H
#define AREA_H

#include <iostream>
#include <string>
#include <sstream>
#include "Dllist.h"
#include "Corral.h"

using namespace std;

class Area{
    private:
        string name;
        DList<Corral> corrales;
        int capacity;

    public:
        Area();
        Area(string,DList<Corral>,int);

        string getName();
        string getInfo();
        int getCapacity();

        void addCorral(const Corral&);

};

Area::Area() : name(""), capacity(0) {}

Area::Area(string _name, DList<Corral> _corr, int _cap) : 
name(_name), capacity(_cap) {}

string Area::getName(){
    return name;
}

string Area::getInfo(){
    
    stringstream aux;
    DListIterator<Corral> itr(&corrales);

    aux << "Nombre: " << name << endl;
    aux << "Capacidad: " << capacity << endl;

    for (itr.begin(); !itr.end(); ++itr) {
        aux << itr().getInfo();
    }

    return aux.str();
}

int Area::getCapacity(){
    return capacity;
}

void Area::addCorral(const Corral& c){
    corrales.add(c);
}

#endif