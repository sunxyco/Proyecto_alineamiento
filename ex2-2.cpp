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



//.........................................................................................................

void reconstruirAlineamiento(string cadenaS, string cadenaT, int** matrizAlineamiento, int n, int m, int v, string& alineamientoS, string& alineamientoT){
    //string alineamientoS = "";
    //string alineamientoT = "";

    int i = n;
    int j = m;

    while(i >= 0 || j >= 0) {
        if(i > 0 && j == 0) {
            alineamientoS = cadenaS[i] + alineamientoS;
            alineamientoT = "-" + alineamientoT;
            cout<<"c1 | "<< alineamientoS<<"\n";
            cout<<"c2 |"<< alineamientoT<<"\n";
            cout<<"\n";
            i--;
        }else if(i == 0 && j > 0){
            alineamientoS = "-" + alineamientoS;
            alineamientoT = cadenaT[j] + alineamientoT;
            cout<<"c1 | "<< alineamientoS<<"\n";
            cout<<"c2 | "<< alineamientoT<<"\n";
            cout<<"\n";
            j--;
        }else if(i>0 && j>0 && matrizAlineamiento[i][j] == matrizAlineamiento[i-1][j] + v){
            alineamientoS = cadenaS[i] + alineamientoS;
            alineamientoT = "-" + alineamientoT;
            cout<<"c1 | "<< alineamientoS<<"\n";
            cout<<"c2 | "<< alineamientoT<<"\n";
            cout<<"\n";
            i--;
        }else if(i>0 && j>0 && matrizAlineamiento[i][j] == matrizAlineamiento[i][j-1] + v) {
            alineamientoS = "-" + alineamientoS;
            alineamientoT = cadenaT[j] + alineamientoT;
            cout<<"c1 | "<< alineamientoS<<"\n";
            cout<<"c2 | "<< alineamientoT<<"\n";
            cout<<"\n";
            j--;
        }else{
            alineamientoS = cadenaS[i] + alineamientoS;
            alineamientoT = cadenaT[j] + alineamientoT;
            cout<<"c1 | "<< alineamientoS<<"\n";
            cout<<"c2 | "<< alineamientoT<<"\n";
            cout<<"\n";
            i--;
            j--;
        }
    }


    cout << "\nAlineamientos\n\n" << "C1 | "<< alineamientoS << "\n" << "C2 | " <<alineamientoT << endl;
}

//.........................................................................................................

void visualizarAlineamiento(string alineamientoS, string alineamientoT){

    int n = alineamientoS.size();
    int m = alineamientoT.size();

    // crear el archivo de salida
    std::ofstream fp("bbb.txt");

    // manejo errores
    if (!fp.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir el grafo.\n";
        return;
    }


    // escribir el grafo en formato DOT
    fp << "digraph grafo {\n";
    fp << "graph [layout=neato, splines=false]\n";
    fp << "node [shape=box]\n";


    //in beetween ----------------------------------------------------------------------------------------

    //cadena 1 - S
    for(int i = 0; i < n; i++){
        fp << "S" << i << " [label = \"" << alineamientoS[i] << "\", pos=\"" << (i * 1.5) << ",2!\", width=1.5, style=filled, fillcolor=bisque1, group=" << i << "];\n";

    }

    //cadena 2 - T
    for(int j = 0; j < m; j++){
        fp << "T" << j << " [label = \"" << alineamientoT[j] << "\", pos=\"" << (j * 1.5) << ",1!\", width=1.5, style=filled, fillcolor=bisque1, group=" << j << "];\n";
    }


    fp << "}\n";

    fp.close();

    std::cout << "\nArchivo 'bbb.txt' generado correctamente.\n";

}

void visualizarBonito(string alineamientoS, string alineamientoT){

    int n = alineamientoS.size();
    int m = alineamientoT.size();

    // crear el archivo de salida
    std::ofstream fp("bonito.txt");

    // manejo errores
    if (!fp.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir el grafo.\n";
        return;
    }

    // escribir el grafo en formato DOT
    fp << "graph bonito {\n";


    fp << "rankdir=HR;\n";        // Orientación horizontal
    fp << "splines=false;\n";     // Fuerza líneas completamente rectas
    fp << "node [shape=circle];\n\n";

    
    //in beetween ----------------------------------------------------------------------------------------

    int contador_gaps = 0;

    
    //cadena 1 - S
    fp << "\n// Nodos para la primera cadena\n";

    int contador_bases_S = 0;

    for(int i = 0; i < n; i++){
        contador_bases_S++;
        fp << "S" << contador_bases_S << " [label = \"" << alineamientoS[i] << "\" ];\n";            
    }


    //cadena 2 - T
    fp << "\n// Nodos para la segunda cadena\n";

    int contador_bases_T = 0;

    for(int j = 0; j < n; j++){
        contador_bases_T++;
        fp << "T" << contador_bases_T << " [label = \"" << alineamientoT[j] << "\" ];\n";            
    }

    //----------------------------------------------------------------------------------------------------
    fp << "\n// Alineación horizontal por fila\n\n// cadena S\n";
    //cadena 1 - S
    string rank_s = "{rank=same; ";
    int contador_gaps_2 = 0;
    string gap_s = "";
    int contador_bases_S2 = 0;

    for(int i = 0; i < n; i++){

        contador_bases_S2++;
        string base_S = "S" + to_string(contador_bases_S2);

        rank_s = rank_s + base_S + "; ";    

    }
    fp <<rank_s<<" }\n";


    fp << "\n// cadena T\n";
    //cadena 2 - T
    string rank_t = "{rank=same; ";
    //int contador_gapt_2 = 0;
    string gap_t = "";
    int contador_bases_T2 = 0;

    for(int j = 0; j < n; j++){

        contador_bases_T2++;
        string base_T = "T" + to_string(contador_bases_T2);

        rank_t = rank_t + base_T + "; ";    
    
        
    }
    fp <<rank_t<<" }\n";

    //----------------------------------------------------------------------------------------------------
    fp << "\n// Conexiones dentro de cada cadena\n\n";
    
    //cadena 1 - S
    string conexion_s = "";
    int contador_gaps_3 = 0;
    string gap_s2 = "";
    int contador_bases_S3 = 0;

    for(int i = 0; i < n-1; i++){

        contador_bases_S3++;
        string base_S2 = "S" + to_string(contador_bases_S3);

        conexion_s = conexion_s + base_S2 + " -- ";    

    }

    for(int i = n-1; i < n; i++){

        contador_bases_S3++;
        string base_S2 = "S" + to_string(contador_bases_S3);

        conexion_s = conexion_s + base_S2 + ";";    

        
    }
    fp <<conexion_s + "\n";
    
    // --------------------------------------------------------------- 
    //cadena 2 - T
    string conexion_t = "";
    string gap_t2 = "";
    int contador_bases_T3 = 0;

    for(int i = 0; i < n-1; i++){

        contador_bases_T3++;
        string base_T2 = "T" + to_string(contador_bases_T3);

        conexion_t = conexion_t + base_T2 + " -- ";    

    }

    for(int i = n-1; i < n; i++){

        contador_bases_T3++;
        string base_T2 = "T" + to_string(contador_bases_T3);

        conexion_t = conexion_t + base_T2 + ";";    
    
        
    }
    fp <<conexion_t + "\n";

    
    //----------------------------------------------------------------------------------------------------
    fp << "\n// Conexiones entre cadenas (si esque las letras coinciden)\n";
    int kelly = 0;

    for (int i = 0; i < n; i++) {

        if(alineamientoS[i] == '-' || alineamientoT[i] == '-'){
            //fp<<"";
            string baseS = "S" + to_string(i + 1);
            string baseT = "T" + to_string(i + 1);
                                                //linea discontinua y negra
            fp << baseS << " -- " << baseT << " [style=dashed, penwidth=3, color=black];\n";

        }else{
            kelly++;
            //letras iguales
            if (alineamientoS[i] == alineamientoT[i]) {
                string baseS = "S" + to_string(i + 1);
                string baseT = "T" + to_string(i + 1);
                                                    //linea gruesa y azul
                fp << baseS << " -- " << baseT << " [style=bold, color=blue];\n";
            }else{
            //letras diferentes
                string baseS = "S" + to_string(i + 1);
                string baseT = "T" + to_string(i + 1);
                                                    //linea roja
                fp << baseS << " -- " << baseT << " [style=bold, color=red];\n";
            }
        }


        
    }
    

    //in beetween ----------------------------------------------------------------------------------------

    fp << "}\n";

    fp.close();

    std::cout << "\nArchivo 'bonito.txt' generado correctamente.\n";
}




int main(int argc, char *argv[]){
    
    //leer archivo -> entrada_ejemplo = -C1 S.tex -C2 T.tex -u funU.tex -V -2
    ifstream file1(argv[2]);
    ifstream file2(argv[4]);
    //ifstream file3(argv[6]);
    string valor_penalidad_string = argv[8];

    string cadena1;
    file1 >> cadena1;
    file1.close();

    string cadena2;
    file2 >> cadena2;
    file2.close();

    string v;
    //file3 >> v;
    //file3.close();

    int valor_penalidad = stoi(valor_penalidad_string);
    valor_penalidad = valor_penalidad * -1;
    cout << "valor penalidad ~~ " << valor_penalidad << "\n"<< endl;

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

    std::string alineamientoS, alineamientoT;
    reconstruirAlineamiento(cadena1, cadena2, matriz_alineamiento, n - 2, m - 2, valor_penalidad, alineamientoS, alineamientoT);
    
    cout<<"\n\n";

    //visualizarAlineamiento(alineamientoS, alineamientoT);

    visualizarBonito(alineamientoS, alineamientoT);

    // crear imagen del grafo usando Graphviz    
    //system("dot -Tpng bbb.txt -o bbb.png");
    system("dot -Tpng bonito.txt -o bonito.png");

    return 0;
}