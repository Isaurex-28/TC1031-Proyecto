#ifndef SLIME_H
#define SLIME_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Slime{
    private:
        string nombre;
        string tipo;
        double plortVal;
    public:
        void setNombre(string);
        string getNombre();
        string getTipo();
        double getPlortVal();

        Slime() : nombre("") , tipo("") , plortVal(0.0){}
        Slime(string, string, double);
};

Slime::Slime(string nom, string typ, double val){
    nombre = nom;
    tipo = typ;
    plortVal = val;
}

void Slime::setNombre(string nom){
    nombre = nom;
}

string Slime::getNombre(){
    return nombre;
}

string Slime::getTipo(){
    return tipo;
}

double Slime::getPlortVal(){
    return plortVal;
}

#endif