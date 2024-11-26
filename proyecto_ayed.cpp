#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
//const int MAX_LARGO = 1000;

/*abrir archivos y crear arreglos*/
int abrir_y_leer_archivo(char *arr, string nombre_archivo, int largo){
    ifstream archivo(nombre_archivo); //abre archivo
    if (!archivo.is_open()) { //control de errores si es que no se abre el archivo
        cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << endl;
        return 0;
    }

    int i = 0;
    //lee el archvivo caracter por caracter, maximo tamaño de 1000
    while (archivo >> arr[i] && i < largo)  { 
        i++;
    }
    archivo.close(); //se cierra el archivo despues de leer
    arr[i] = '\0'; //termina la cadena
    return i; //long de la secuencia leida
}
    
//valida que tamanos de los arreglos sean mayores a cero
void validar_tamanos(int m, int n){
    if (m == 0 || n == 0) {
        cerr << "Error: No se pudieron leer las secuencias." << endl;
    }    
}

/*emparejar bases, compara. Matrices*/
//implementacion de Needleman-Wunsch *
void compara_bases(char *prin, char *sec, string primer_archivo, string segundo_archivo, int gap, int largo){
    //leer las secuencias desde los archivos
    /*crea el arreglo con la cadena de cada uno de los archivos y devuelve sus tamanos*/
    int m = abrir_y_leer_archivo(prin, primer_archivo, largo);
    int n = abrir_y_leer_archivo(sec, segundo_archivo, largo);
    validar_tamanos(m,n); // valida que los tamanos no sean 0 (osea que exista algo en el archivo)

    int mayor = max(m + 1, n + 1); //determina la longitud maxima
    int matriz[100][100] = {0}; //se crea la matriz estatica

    //parametros del algoritmo
    int match = 1; //Match: Si las bases actuales son iguales "coinciden"
    int mismatch = -1; //Mismatch: Si las bases son diferentes "no coinciden"
    //Gap: Si se introduce un espacio (gap) para alinear

    //ahora inicializa la primera fila y columna de la matriz
    for (int i = 0; i <= m; i++) {
        matriz[i][0] = i*gap;     //*gap porq la primera fila y columna va con negativos    
    }

    for (int j = 0; j <= n; j++) {
        matriz[0][j] = j*gap;
    }

    //ahora se llena la matriz
    for (int i = 1; i < mayor; i++) {
        for (int j = 1; j < mayor; j++) {
            int arriba = matriz[i-1][j] + gap;
            int izq = matriz[i][j-1] + gap;
            int diagonal;
            //compara las bases para ver si coincide o no
            if (prin[i-1] == sec[j-1]) {
                diagonal = matriz [i-1][j-1] + match;
            } else {
                diagonal = matriz[i-1][j-1] + mismatch;
            } //hice lo mismo pero definiendo diagonal arriba
            
            matriz[i][j]= max(diagonal, max(arriba, izq));
            //maximo valor de las opciones posibles
            
        }
        
    }
    //ahora imprime la matriz de puntuaciones
    cout << "Matriz de puntuaciones:\n " << endl; 
    cout << "           ";

    for (int i = 0; i < m; i++) {
        cout << sec[i] << "     ";
    }

    cout << endl;
    cout << "      ";

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matriz [i][j]<< "    ";
        }
        cout << "\n";
        cout << "  " << prin[i] << "  ";
    }
    cout << endl;

    cout<<"estoy aqui, ya imprimio la matriz"<< endl;

    //RECONSTRUCCION DEL ALINEAMIENTO

    string alineamiento1 = ""; //secuencia1 alineada
    string alineamiento2 = ""; //secuencia2 alineada
//     //int posicion = 199; //variable de seguimiento de posicion actual 
//     //199 corresponde a la ultima posicion del arreglo y ahi comienza

//     //ahora la reconstruccion del alineamiento desde la matriz
// //  int posicion = n + m + 1; //variable de seguimiento de posicion actual. Corresponde a la ultima posicion del arreglo y ahi comienza
//      // se compara la matriz para el alineamiento

    int i = m;
    int j = n;

// //   int h = max(m,n);

//     // //para generar la imagen en graphiz
//     // ofstream archivo_dot("alineamiento.dot");
//     // if (!archivo_dot.is_open()) {
//     //     cerr << "Error al crear el archivo .dot" << endl;
//     // } else {
//     //     cout << "El archivo .dot se ha creado correctamente." << endl;
//     // }
//     // archivo_dot << "digraph Alineamiento {" << endl;
//     // archivo_dot << "rankdir=LR;" << endl;
//     // int nodo_id = 0;

//     //se compara la matriz para el alineamiento
    while (i > 0 || j > 0) {

        if (matriz[i][j] == matriz[i-1][j-1] + match) { //coincidencia
            if (prin[i-1] == sec[j-1]) {
                alineamiento1 = prin[i-1] + alineamiento1;
                alineamiento2 = sec[j-1] + alineamiento2;
                i--;
                j--;
            }
        cout<<"ahora aqui, ya se hizo el primer ciclo de if"<< endl;

        } else if (matriz[i][j] == matriz [i-1][j-1] + mismatch) { //no coinciden
            if (prin[i-1] != sec[j-1]) {
                alineamiento1 = prin[i-1] + alineamiento1;
                alineamiento2 = sec[j-1] + alineamiento2;
                i--;
                j--;
            }
        cout<<"cambio aqui, ahora en primer else if"<< endl;

        } else if (matriz[i][j] == matriz[i-1][j] + gap) { //gap en la segunda secuencia
            alineamiento1 = prin[i-1] + alineamiento1;
            alineamiento2 = '-' + alineamiento2;
            i--;
        cout<<"aqui, ahora en el segundo else if"<< endl;

        } else { //gap en la primera secuencia
            alineamiento1 = '-' + alineamiento1;
            alineamiento2 = sec[j-1] + alineamiento2;
            j--;
        }
        cout<<"estoy aqui, en el ultimo else"<< endl;
    }

    while (i > 0) {
        alineamiento1 = prin[i-1] + alineamiento1;
        alineamiento2 = '-' + alineamiento2;
        i--;
    }
    cout<<"estoy aqui, en el primer while"<< endl;

    while (j > 0) {
        alineamiento1 = '-' + alineamiento1;
        alineamiento2 = sec[j - 1] + alineamiento2;
        j--;
    }
    cout<<"estoy aqui, en el segundo while"<< endl;

    cout << "Alineamiento1: " << alineamiento1 << endl;
    cout << "ALineamiento2: " << alineamiento2 << endl;

//     // //deberia generar la imagen
//     // //no son las mismas lineas de codigo para windows o linux :)
//     // //generacion de la imagen con graphviz
//     // archivo_dot << "}" << endl; //cierra el grafo DOT
//     // archivo_dot.close(); //cierra el archivo DOT
//     // system("dot -Tpng alineamiento.dot -o alineamiento.png");
//     // system("start alineamiento.png");
//     // Generar el archivo DOT para Graphviz

    ofstream archivo("alineamiento.dot");
    archivo << "digraph Alineamiento {" << endl;
    archivo << "rankdir=LR;" << endl;
    archivo << "node [shape=box, style=filled, fillcolor=lightblue];" << endl;

    for (size_t k = 0; k < alineamiento1.size(); ++k) {
        archivo << "n" << k << " [label=\"" << alineamiento1[k] << "|" << alineamiento2[k] << "\"];" << endl;
        if (k > 0) {
            archivo << "n" << k - 1 << " -> n" << k << ";" << endl;
        }
    }

    archivo << "}" << endl;
    archivo.close();

    // Usar Graphviz para generar la imagen
    system("dot -Tpng -o alineamiento.png alineamiento_v2.dot");

    system("start alineamiento.png"); // Visualizar la imagen generada en Windows
}

int main(int argc, char const *argv[]) {
    /*inicializar arreglos*/
    const int largo = 100;
    char principal[largo] = {0};
    char secundaria[largo] = {0};
    int gap = -1; //en -2 para que no sea igual que el -1 por el mismatch de no coincidir

    //lee secuencias desde archivos
    string archivo_principal = "secuencia1.txt";
    string archivo_secundaria = "secuencia2.txt";
    compara_bases(principal, secundaria, archivo_principal, archivo_secundaria, gap, largo);

    return 0;
    
}




// void alinear(char* prin, char* sec, int m, int n, int** matriz, int match, int mismatch, int gap){
//     char alineamiento1[m + n + 1]; //secuencia1 alineada
//     char alineamiento2[m + n + 1]; //secuencia2 alineada

//     //ahora la reconstruccion del alineamiento desde la matriz
//     int posicion = n + m + 1; //variable de seguimiento de posicion actual. Corresponde a la ultima posicion del arreglo y ahi comienza
//     // se compara la matriz para el alineamiento
//     int i = m;
//     int j = n;
//     int h = max(m,n);

//     while (i > 0 || j > 0)
//     {
//         if (matriz[i + 1][j + 1] == matriz[i-1][j-1] + match) { //coincidencia
//             if (prin[i-1] == sec[j-1]) {
//                 alineamiento1[h] = prin[i-1] + alineamiento1;
//                 alineamiento2[h] = sec[j-1] + alineamiento2;
//                 i--;
//                 j--;
//             }

//         } else if (matriz[i][j] == matriz [i-1][j-1] + mismatch) { //no coinciden
//             if (prin[i-1] != sec[j-1]) {
//                 alineamiento1[h] = prin[i-1] + alineamiento1;
//                 alineamiento2[h] = sec[j-1] + alineamiento2;
//                 i--;
//                 j--;
//             }

//         } else if (matriz[i][j] == matriz[i-1][j] + gap) { //gap en la segunda secuencia
//             alineamiento1[h] = prin[i-1] + alineamiento1;
//             alineamiento2[h] = '-' + alineamiento2;
//             i--;

//         } else { //gap en la primera secuencia
//             alineamiento1[h] = '-' + alineamiento1;
//             alineamiento2[h] = sec[j-1] + alineamiento2;
//             j--;
//         }
//         h--
//     }
    

// }



//     

//     int i = m;
//     int j = n;
//     //para generar la imagen en graphiz
//     ofstream archivo_dot("alineamiento.dot");
//     archivo_dot << "digraph Alineamiento {" << endl;
//     archivo_dot << "rankdir=LR;" << endl;
//     int nodo_id = 0;

//     //se compara la matriz para el alineamiento

//     while (i > 0) {
//         alineamiento1 = prin[i-1] + alineamiento1;
//         alineamiento2 = '-' + alineamiento2;
//         i--;
//     }

//     while (j > 0) {
//         alineamiento1 = '-' + alineamiento1;
//         alineamiento2 = sec[j - 1] + alineamiento2;
//         j--;
//     }

//     cout << "Alineamiento1: " << alineamiento1 << endl;
//     cout << "ALineamiento2: " << alineamiento2 << endl;

//     //deberia generar la imagen
//     //no son las mismas lineas de codigo para windows o linux :)
//     system("dot -Tpng alineamiento.dot -o alineamiento.png");
//     system("start alineamiento.png");
//}
