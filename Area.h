#ifndef AREA_H
#define AREA_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Splay.h"
#include "Corral.h"

using namespace std;

class Area {
private:
    string name;
    SplayTree<Corral> corrales;
    int capacity;

public:
    Area();
    Area(string, int);
    Area(string, SplayTree<Corral>, int);

    string getName();
    int getCapacity();
    string getInfo();
    vector<Corral> getCorralesVector();

    bool addCorral(const Corral&);
    Corral findCorral(string);
    bool removeCorral(string);

    bool operator==(const Area& other) const;
};

Area::Area() : name(""), capacity(0) {}

Area::Area(string _name, int _cap) : name(_name), capacity(_cap) {}

Area::Area(string _name, SplayTree<Corral> _corr, int _cap)
    : name(_name), corrales(_corr), capacity(_cap) {}

string Area::getName(){ 
    return name; 
}

int Area::getCapacity(){ 
    return capacity; 
}

string Area::getInfo(){
    stringstream aux;
    aux << "\n\nArea: " << name << "\nCorrales: ("
        << corrales.size() << " de " << capacity << ")\n";
    aux << corrales.inorder();
    return aux.str();
}

vector<Corral> Area::getCorralesVector(){
    vector<Corral> out;
    corrales.toVector(out);
    return out;
}

bool Area::addCorral(const Corral& c) {
    if (corrales.size() >= capacity) {
        return false;
    }
    corrales.add(c);
    return true;
}

Corral Area::findCorral(string _id) {
    Corral dummy(_id, "", 0, 0, 0.0f, 0);
    if (corrales.find(dummy)) {
        return corrales.getRootNode();
    }
    return Corral();
}

bool Area::removeCorral(string _id) {
    Corral dummy(_id, "", 0, 0, 0.0f, 0);
    if (corrales.find(dummy)) {
        corrales.remove(dummy);
        return true;
    }
    return false;
}

bool Area::operator==(const Area& other) const {
    return name == other.name;
}

#endif
