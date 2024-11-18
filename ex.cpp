#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//parametros de entrada ->  -C1 cad1.tex -C2 cad2.tex -U funU.tex -V val
//                          -C1 S.tex -C2 cad.tex -u funU.tex -V val

int** generar_funcionU(string input){
    ifstream file(input);

    string linea;
    /* definirla de la manera: int matriz[4][4]; hace que tenga un tiempo de vida limitado
    asi que se se opta por hacer una matriz de tamaño dinamico pero que será de 4x4*/

    //matriz dinamica
    int** matriz = new int*[4];
    for (int i = 0; i < 4; i++) {
        matriz[i] = new int[4];
    }

    int z = 0;
    int j = 0;
    
    while (getline(file, linea)) {  //leer línea por línea
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

    file.close();

    return matriz;
}

int main(int argc, char *argv[]){
    
    //leer archivo -> entrada_ejemplo = -C1 S.tex -C2 T.tex -u funU.tex -V -2
    ifstream file1(argv[2]);
    ifstream file2(argv[4]);

    string cadena1;
    file1 >> cadena1;
    file1.close();

    string cadena2;
    file2 >> cadena2;
    file2.close();

    //funcionU -> [4][4] ~ matriz de tamaño dinamico porque sino c++ kaput
    int** funcionU = generar_funcionU(argv[6]);

    cout << "Cadenas\n-c1 " << cadena1 << " -c2 " << cadena2 << endl << "Matriz de coincidencia\n";

    // Imprimir la matriz
    char nucleotidos[4] = {'A', 'G', 'C', 'T'};

    cout << " ~";
    for (int i = 0; i < 4; i++) {
        cout << " " << nucleotidos[i] << " ";
    }
    cout << "\n";

    //recorrer las filas
    for (int i = 0; i < 4; i++) {
        cout << nucleotidos[i] << " ";
        //reecorrer las columnas
        for (int j = 0; j < 4; j++) {     
            //imprimir el valor en la posición (i, j)
            cout << funcionU[i][j] << ", ";
        }
        cout << endl;
    }

    return 0;
}