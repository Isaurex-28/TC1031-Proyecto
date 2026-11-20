#ifndef CORRAL_H
#define CORRAL_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Corral {
private:
    string id;
    string type;
    int quantity;
    int capacity;
    float plortVal;
    int foodPerSlime;

public:
    Corral();
    Corral(string, string, int, int, float, int);

    string getID();
    string getType();
    int getQuantity() const;
    int getCapacity();
    float getPlortVal();
    int getFoodPerSlime();

    float getTotalPlortValue() const;
    int getTotalFoodNeeded() const;
    string getInfo() const;

    bool operator==(Corral other);
    bool operator<(Corral other);
    bool operator>(Corral other);
};

Corral::Corral() : id(""), type(""), quantity(0), capacity(0), plortVal(0.0f), foodPerSlime(0) {}

Corral::Corral(string _id, string _type, int _quan, int _cap, float _plortVal, int _food)
    : id(_id), type(_type), quantity(_quan), capacity(_cap), plortVal(_plortVal), foodPerSlime(_food) {}

string Corral::getID() {
    return id;
}

string Corral::getType() {
    return type;
}

int Corral::getQuantity() const {
    return quantity;
}

int Corral::getCapacity() {
    return capacity;
}

float Corral::getPlortVal() {
    return plortVal;
}

int Corral::getFoodPerSlime() {
    return foodPerSlime;
}

float Corral::getTotalPlortValue() const {
    return quantity * plortVal;
}

int Corral::getTotalFoodNeeded() const {
    return quantity * foodPerSlime;
}

string Corral::getInfo() const {
    stringstream aux;
    aux << "\nCorral [" << id << "]\nSlime: " << type
        << "\nCantidad: " << quantity << "/" << capacity
        << "\nPrecio del Plort: $" << plortVal
        << "\nPrecio Total: $" << getTotalPlortValue()
        << "\nComida total: " << getTotalFoodNeeded() << "\n";
    return aux.str();
}

bool Corral::operator==(Corral other) {
    return id == other.id;
}

bool Corral::operator<(Corral other) {
    return id < other.id;
}

bool Corral::operator>(Corral other) {
    return id > other.id;
}


#endif
