#include <iostream>
using namespace std;
#include <fstream>

//parametros de entrada ->  -C1 cad1.tex -C2 cad2.tex -U funU.tex -V val
//                          -C1 S.tex -C2 cad.tex -u funU.tex -V val

int** generar_funcionU(ifstream file){

}

int main(int argc, char *argv[]){
    
    //leer archivo
    ifstream file1(argv[2]);
    ifstream file2(argv[4]);
    ifstream file3(argv[6]);

    string cadena1;
    file1 >> cadena1;
    file1.close();

    string cadena2;
    file2 >> cadena2;
    file2.close();

    int funcionU[4][4] = generar_funcionU(file3);

    cout << "-c1 " << cadena1 << " -c2 " << cadena2;


    return 0;
}