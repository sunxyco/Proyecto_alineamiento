#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    cout << "Hola, Mundo!" << endl;
    
    ifstream archivo("U.tex");
    
    string linea;
    int matriz[4][4];
    int z = 0;
    int j = 0;

    while (getline(archivo, linea)) {  //leer línea por línea
        cout << linea << endl;  //imprimir cada línea
        j = 0;
        //se extraen los numeros del string
        //int i = 0;
        string::size_type i = 0; 
        string s;
        while (i <= linea.length())
        {
            if(linea[i] == ',') {
                cout << stoi(s)<< endl;
                matriz[z][j] = stoi(s);
                s.clear();
                j ++;
            } else {
                s += linea[i];
            }

            i ++;
        }

        z++;
    }
    
    archivo.close();
    
    //cout << cadena;

    //indices -> A, G, C, T
    // A = 0, G = 1, C = 2, T = 3
    // Imprimir la matriz
    char nucleotidos[4] = {'A', 'G', 'C', 'T'};

    cout << " ~";
    for (int i = 0; i < 4; i++) {
        cout << " " << nucleotidos[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < 4; i++) {     // Recorrer las filas
        cout << nucleotidos[i] << " ";
        for (int j = 0; j < 4; j++) {      // Recorrer las columnas
            cout << matriz[i][j] << ", ";   // Imprimir el valor en la posición (i, j)
        }
        cout << endl;  // Salto de línea al final de cada fila
    }
    
    return 0;
}