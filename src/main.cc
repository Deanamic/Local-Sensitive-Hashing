#include <iostream>
#include <fstream>
#include "Parser.h"
using namespace std;

int main(int argc, char *argv[]) {
    string nombre;
    if(argc!=2) {
        cout << "Dime el nombre de la familia de fichero (sin .txt): ";
        getline(cin,nombre);
    }
    else nombre = argv[1];
    nombre += ".txt";
    return 0;
}
