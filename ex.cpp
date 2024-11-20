#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
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

int funcionU(int** matrizU, char caracter_s, char caracter_t){
    int indice_s;
    int indice_t;

    if(caracter_s == 'A'){
        indice_s = 0;
    }else if(caracter_s == 'C'){
        indice_s = 1;
    }else if(caracter_s == 'G'){
        indice_s = 2;
    }else if(caracter_s == 'T'){
        indice_s = 3;
    }

    if(caracter_t == 'A'){
        indice_t = 0;
    }else if(caracter_t == 'C'){
        indice_t = 1;
    }else if(caracter_t == 'G'){
        indice_t = 2;
    }else if(caracter_t == 'T'){
        indice_t = 3;
    }

    return matrizU[indice_s][indice_t];
}

int** generarMatrizAlineamiento(string cadena_S, string cadena_t, int** matriz_U, int valor_penalidad){
    int n = cadena_S.size();
    int m = cadena_t.size();
    //cout << n;
    n++;
    m++;

    cout << "matri1";

    //crear una matriz dinámica de tamaño n x m -> para el algoritmo
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[m];
    }

    cout << "matri2";


    //se rellenar la matriz segun el algoritmo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                matriz[i][j] = 0;
            } else if (i > 0 && j == 0) {
                matriz[i][j] = matriz[i - 1][j] + valor_penalidad;
            } else if (i == 0 && j > 0) {
                matriz[i][j] = matriz[i][j - 1] + valor_penalidad;
            } else {
                int a = matriz[i - 1][j] + valor_penalidad;   //No emparejar S[i]
                int b = matriz[i][j - 1] + valor_penalidad;   //No emparejar T[j]
                    cout << "matri3";

                char caracter_s = cadena_S[i - 1];
                char caracter_t = cadena_t[j - 1];

                int c = matriz[i - 1][j - 1] + funcionU(matriz_U, caracter_s, caracter_t); // Emparejar S[i] y T[j]
                    cout << "matri4";

                matriz[i][j] = max(a, max(b, c)); // Máximo de las opciones
            }
        }
    }

    cout << endl;

    return matriz;
}

void reconstruirAlineamiento(string cadenaS, string cadenaT, int** matrizAlineamiento, int n, int m, int v){
    string alineamientoS = "";
    string alineamientoT = "";

    int i = n;
    int j = m;

    while(i > 0 || j > 0) {
        if(i > 0 && j == 0) {
            alineamientoS = cadenaS[i-1] + alineamientoS;
            alineamientoT = "-" + alineamientoT;
            i--;
        }else if(i == 0 && j > 0){
            alineamientoS = "-" + alineamientoS;
            alineamientoT = cadenaT[j-1] + alineamientoT;
            j--;
        }else if(i>0 && j>0 && matrizAlineamiento[i][j] == matrizAlineamiento[i-1][j] + v){
            alineamientoS = cadenaS[i-1] + alineamientoS;
            alineamientoT = "-" + alineamientoT;
            i--;
        }else if(i>0 && j>0 && matrizAlineamiento[i][j] == matrizAlineamiento[i][j-1] + v) {
            alineamientoS = "-" + alineamientoS;
            alineamientoT = cadenaT[j-1] + alineamientoT;
            j--;
        }else{
            alineamientoS = cadenaS[i-1] + alineamientoS;
            alineamientoT = cadenaT[j-1] + alineamientoT;
            i--;
            j--;
        }
    }

    cout << "\nAlineamientos\n\n" << alineamientoS << "\n" << alineamientoT << endl;
}

int main(int argc, char *argv[]){
    
    //leer archivo -> entrada_ejemplo = -C1 S.tex -C2 T.tex -u funU.tex -V -2
    ifstream file1(argv[2]);
    ifstream file2(argv[4]);
    ifstream file3(argv[6]);

    string cadena1;
    file1 >> cadena1;
    file1.close();

    string cadena2;
    file2 >> cadena2;
    file2.close();

    string v;
    file3 >> v;
    file3.close();

    int valor_penalidad = stoi(v);
    valor_penalidad = valor_penalidad * -1;
    cout << "valor penalidad ~~ " << valor_penalidad;

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

    int** matriz_alineamiento = generarMatrizAlineamiento(cadena1, cadena2, funcionU, valor_penalidad);

    int n = ((cadena1.size()) + 1);
    int m = ((cadena2.size()) + 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matriz_alineamiento[i][j] << ", ";
        }
        cout << endl;
    }

    reconstruirAlineamiento(cadena1, cadena2, matriz_alineamiento, n - 2, m - 2, valor_penalidad);
    

    return 0;
}