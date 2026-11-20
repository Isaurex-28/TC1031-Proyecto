#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Load.h"
#include "Sort.h"

using namespace std;

int main() {
    DList<Area> rancho = LoadRancho("slimes.csv");
    bool menu = true;

    while (menu) {
        int op;
        cout << "\n===== SLIME RANCHER MANAGER =====\n";
        cout << "1- Ver areas y corrales\n";
        cout << "2- Ordenar corrales\n";
        cout << "3- Buscar corral\n";
        cout << "4- Agregar nuevo corral\n";
        cout << "5- Eliminar corral\n";
        cout << "6- Guardar rancho en archivo\n";
        cout << "7- Salir\n";
        cout << "Escribe el numero: ";
        cin >> op;

        switch (op) {
            case 1: {
                if (rancho.empty()) {
                    cout << "\nNo hay datos\n";
                } else {
                    cout << "\n";
                    DListIterator<Area> itr(&rancho);
                    for (itr.begin(); !itr.end(); ++itr) {
                        cout << itr().getInfo() << "\n";
                    }
                }
                break;
            }
            case 2: {
                vector<Corral> todos;
                DListIterator<Area> itr(&rancho);
                for (itr.begin(); !itr.end(); ++itr) {
                    vector<Corral> temp = itr().getCorralesVector();
                    todos.insert(todos.end(), temp.begin(), temp.end());
                }

                if (todos.empty()) {
                    cout << "\nNo hay corrales para ordenar.\n";
                    break;
                }

                int criterio;
                cout << "\nOrdenar corrales por:\n";
                cout << "1- Valor total de Plorts\n";
                cout << "2- Comida total necesaria\n";
                cout << "3- Cantidad de Slimes\n";
                cout << "Elige una opcion: ";
                cin >> criterio;

                if (criterio < 1 || criterio > 3) {
                    cout << "Criterio invalido.\n";
                    break;
                }

                vector<Corral> ordenados = mergeSort(todos, criterio);
                cout << "\n--- Corrales Ordenados ---\n";
                for (size_t i = 0; i < ordenados.size(); i++) {
                    cout << ordenados[i].getInfo();
                }
                break;
            }
            case 3: {
                string searchID;
                cout << "Ingresa el ID del corral a buscar (ej. C04): ";
                cin >> searchID;

                bool encontrado = false;
                DListIterator<Area> itr(&rancho);
                for (itr.begin(); !itr.end(); ++itr) {
                    Corral res = itr().findCorral(searchID);
                    if (res.getID() != "") {
                        cout << "\nEncontrado en [" << itr().getName() << "]:\n"
                             << res.getInfo();
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    cout << "\nNo existe ningun corral con el ID " << searchID << ".\n";
                }
                break;
            }
            case 4: {
                string areaName, id, type;
                int quan, cap, food;
                float plort;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nombre del Area (ej. The Ranch): ";
                getline(cin, areaName);
                cout << "ID del Corral (ej. C11): ";
                getline(cin, id);
                cout << "Tipo de Slime: ";
                getline(cin, type);
                cout << "Cantidad de Slimes: ";
                cin >> quan;
                cout << "Capacidad del Corral: ";
                cin >> cap;
                cout << "Valor del Plort ($): ";
                cin >> plort;
                cout << "Comida por Slime: ";
                cin >> food;

                Corral nuevo(id, type, quan, cap, plort, food);
                bool encontrado = false;
                DListIterator<Area> itr(&rancho);
                for (itr.begin(); !itr.end(); ++itr) {
                    if (itr().getName() == areaName) {
                        if (itr().addCorral(nuevo)) {
                            cout << "Corral agregado a " << areaName << ".\n";
                        } else {
                            cout << "El area esta llena.\n";
                        }
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    Area nuevaArea(areaName, getDefaultAreaCapacity(areaName));
                    nuevaArea.addCorral(nuevo);
                    rancho.add(nuevaArea);
                    cout << "Area creada y corral agregado.\n";
                }
                break;
            }
            case 5: {
                string delID;
                cout << "Ingresa el ID del corral a eliminar: ";
                cin >> delID;

                bool eliminado = false;
                DListIterator<Area> itr(&rancho);
                for (itr.begin(); !itr.end(); ++itr) {
                    if (itr().removeCorral(delID)) {
                        cout << "Corral " << delID << " eliminado de "
                             << itr().getName() << ".\n";
                        eliminado = true;
                        break;
                    }
                }
                if (!eliminado) {
                    cout << "No se encontro el corral " << delID << ".\n";
                }
                break;
            }
            case 6: {
                string archivoSalida;
                cout << "Nombre del archivo para guardar (ej. slimes_guardado.csv): ";
                cin >> archivoSalida;
                SaveRancho(rancho, archivoSalida);
                break;
            }
            case 7: {
                menu = false;
                break;
            }
            default: {
                cout << "Opcion invalida.\n";
                break;
            }
        }
    }
    return 0;
}