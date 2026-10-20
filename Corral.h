#ifndef CORRAL_H
#define CORRAL_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Corral{
    private:
        string id;
        string type;
        int quantity;
        int capacity;
    public:
        Corral();
        Corral(string,string,int,int);

        string getID();
        string getType();
        int getQuantity();
        int getCapacity();
        string getInfo();
};

Corral::Corral() : id(""), type(""), quantity(0), capacity(0) {}

Corral::Corral(string _id, string _type, int _quan, int _cap) : 
id(_id), type(_type), quantity(_quan), capacity(_cap) {}

string Corral::getID(){
    return id;
}

string Corral::getType(){
    return type;
}

int Corral::getQuantity(){
    return quantity;
}
int Corral::getCapacity(){
    return capacity;
}

string Corral::getInfo(){
    stringstream aux;
    aux << "ID: " << id << endl;
    aux << "Tipo de Slime: " << type << endl;
    aux << "Cantidad: " << quantity << endl;
    aux << "Capacidad: " << capacity << endl;
    return aux.str();
}
#endif