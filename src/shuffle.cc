#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Parser.h"
using namespace std;


void shuffle(string nombre) {
	string archivo0 = "./data/" + nombre + ".dat";
	
	Parser doc0(archivo0);
	string document0 = doc0.getDocument();
	
	vector<string> palabras;
	string aux;
	for (int i = 0; i < (int)document0.size(); ++i) {
		if (document0[i] != ' ') aux.push_back(document0[i]);
		else {
			palabras.push_back(aux);
			aux = "";
		}
	}
	palabras.push_back(aux);
	
	int numPerm = 20;
	srand (unsigned(time(0)));
	for (int i = 0; i < numPerm; ++i) {
		random_shuffle(palabras.begin(), palabras.end());
		string archivoI = "./data/Shuffle/" + nombre + to_string(i) + ".dat";
		ofstream fs(archivoI);
		fs << palabras[0];
		for (int j = 1; j < (int)palabras.size(); ++j) {
			fs << ' ' + palabras[j];
		}
		fs << endl;
		fs.close();
	}	
}

void mix(string nombre0, string nombre1) {
	string archivo0 = "./data/" + nombre0 + ".dat";
	Parser doc0(archivo0);
	string document0 = doc0.getDocument();
	string archivo1 = "./data/" + nombre1 + ".dat";
	Parser doc1(archivo1);
	string document1 = doc1.getDocument();
	
	vector<string> palabras0;
	string aux;
	for (int i = 0; i < (int)document0.size(); ++i) {
		if (document0[i] != ' ') aux.push_back(document0[i]);
		else {
			palabras0.push_back(aux);
			aux = "";
		}
	}
	palabras0.push_back(aux);
	
	vector<string> palabras1;
	aux = "";
	for (int i = 0; i < (int)document1.size(); ++i) {
		if (document1[i] != ' ') aux.push_back(document1[i]);
		else {
			palabras1.push_back(aux);
			aux = "";
		}
	}
	palabras1.push_back(aux);
	
	
	int numPerm = 40;
	for (int i = 0; i <= numPerm; ++i) {
		srand (unsigned(time(0)));
		random_shuffle(palabras0.begin(), palabras0.end());
		random_shuffle(palabras1.begin(), palabras1.end());
		vector<string> unionPalabras;
		
		int numPalabras0 = float(i)/numPerm*palabras0.size();
		int numPalabras1 = float(numPerm-i)/numPerm*palabras1.size();
		for (int j = 0; j < numPalabras0; ++j) {
			unionPalabras.push_back(palabras0[j]);
			cout << palabras0[j] << endl;
		}
		for (int j = 0; j < numPalabras1; ++j) {
			unionPalabras.push_back(palabras1[j]);
			cout << palabras1[j] << endl;
		}

		cout << numPalabras0 << " y " << numPalabras1 << endl;
		random_shuffle(unionPalabras.begin(), unionPalabras.end());
		
		string archivoI = "./data/Mix/" + to_string(i) + "-" + to_string(numPerm) + nombre0 + "_" +nombre1 + ".dat";
		ofstream fs(archivoI);
		fs << unionPalabras[0];
		for (int j = 1; j < (int)unionPalabras.size(); ++j) {
			fs << ' ' + unionPalabras[j];
		}
		fs << endl;
		fs.close();
	}	
}


int main() {
	shuffle("Luna");
	mix("Lion", "Onion");
}
