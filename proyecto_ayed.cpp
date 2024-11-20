#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX_LARGO = 100;

/*abrir archivos y crear arreglos*/
//le añadi para tener control de errores si es que no se abre el archivo
int abrir_y_leer_archivo(char *arr, string nombre_archivo){
    ifstream archivo(nombre_archivo); //abre archivo
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << endl;
        return 0;
    }

    int i = 0;
     //leer la secuencia completa
    while (archivo >> arr[i] && i < 100)  { //lee caracter por caracter, maximo tamaño de 1000
        i++;
    }
    archivo.close();
    arr[i] = '\0'; //termina la cadena
    return i;
}
    
//     int i = 0;
//     ifstream archivo;
//     archivo.open(nombre_archivo);
//     archivo >> arr;
//     while (arr[i] != 0)
//     {
//         i++;
//     }
//     cout << i << endl;
    
//     return i;
    
// }


/*emparejar bases, compara. Matrices*/
//implementacion de Needleman-Wunsch *
void compara_bases(char *prin, char *sec, string primer_archivo, string segundo_archivo, int gap){
    //leer las secuencias desde los archivos
    int m = abrir_y_leer_archivo(prin, primer_archivo);
    int n = abrir_y_leer_archivo(sec, segundo_archivo);

    if (m == 0 || n == 0) {
        cerr << "Error: No se pudieron leer las secuencias." << endl;
        return;
    }
        // int mayor;
    // if (m > n)
    // {
    //     mayor = m;
    // }
    // else
    // {
    //     mayor = n;
    // }

    int mayor = max(m, n); //determina la longitud maxima
    int matriz[100][100] = {0}; //se crea la matriz estarica

    //parametros del algoritmo
    int match = 1; //Match: Si las bases actuales son iguales "coinden"
    int mismatch = -1; //Mismatch: Si las bases son diferentes "no coinciden"
    //Gap: Si se introduce un espacio (gap) para alinear

    //ahora inicializa la primera fila y columna de la matriz
    for (int i = 0; i <= m; i++) {
        matriz[i][0] = i*gap;     //*gap porq la primera fila y columna va con negativos 
        //matriz[0][i] = -i;      
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
            //ahora compara las bases para ver si coincide o no
            if (prin[i-1] == sec[j-1]) {
                diagonal = matriz [i-1][j-1] + match;
            } else {
                diagonal = matriz[i-1][j-1] + mismatch;
            } //hice lo mismo pero definiendo diagonal arriba
            // if (prin[i] == sec[i]) {
            //     int diagonal = matriz[i-1][j-1] + match;
            // }
            // else
            // {
            //     int diagonal = matriz[i-1][j-1] + mismatch;
            // }
            matriz[i][j]= max({diagonal, arriba, izq});
            
        }
        
    }
    //ahora imprime la matriz de puntuaciones
    cout << "Matriz de puntuaciones: " << endl;
    for (int i = 0; i <=m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matriz [i][j]<< "/t";
        }
        cout << endl;
    }

    //ahora la reconstruccion del alineamiento desde la matriz
    string alineamiento1 = ""; //arreglo para la secuencia1 alineada
    string alineamiento2 = ""; //arreglo para la secuencia2 alineada
    int posicion = 199; //variable de seguimiento de posicion actual 
    //199 corresponde a la ultima posicion del arreglo y ahi comienza

    int i = m;
    int j = n;




}


int main(int argc, char const *argv[]) {
    /*inicializar arreglos*/
    const int largo = 100;
    char principal[largo] = {0};
    char secundaria[largo] = {0};
    int gap = -2; //en -2 para que no sea igual que el -1 por el mismatch

    //lee secuencias desde archivos
    string archivo_principal = "principal.txt";
    string archivo_secundaria = "secundaria.txt";
    int m = abrir_y_leer_archivo(principal, archivo_principal);
    int n = abrir_y_leer_archivo(secundaria, archivo_secundaria);

    if (m == 0 || n == 0) {
        cerr << "Error: No se pudieron leer las secuencias." << endl;
        return 0;
    }
    compara_bases(principal, secundaria, archivo_principal, archivo_secundaria, gap);


    // int i = 0;
    // string nombre = "prueba.txt";
    // int largo_real = abrir_y_leer_archivo(principal, nombre);
    // while (principal[i] != 0)
    // {
    //     cout << " " << principal[i];
    //     i++;
    // }
    // cout << endl;

 
    return 0;
}


//     se inicializa la primera fila y columna (rellenadas con los puntajes por gaps)
// se llena la matriz de puntuacion segun las tres opciones posibles:
//     1.emparejar los caracteres
//     2.insertar un gap en la secuencia principal
//     3.insertar un gap en la secuencia secundaria
//     for (int i = 1; i <= m; i++) {
//         for (int j = 1; j <= n; j++) {
//             calcular la puntuacion para la opcion de emparejar los caracteres
//             int diagonal;
//             if (prin[i - 1] == sec[j - 1]) {
//                 diagonal = matriz[i - 1][j - 1] + match; //coinciden, se suman puntos por match
//             } else {
//                 diagonal = matriz[i - 1][j - 1] + mismatch; //como no coinciden, se suman puntos por mismatch
//             }
            
//             se calcula la puntuacion por gap en la secuencia principal
//             int arriba = matriz[i - 1][j] + gap;
            
//             calcula la puntuacion por gap en la secuencia secundaria
//             int izquierda = matriz[i][j - 1] + gap;
            
//             slmacenar la maxima puntuacion de las tres opciones
//             matriz[i][j] = max(diagonal, max(arriba, izquierda));
//         }
//     }

//     reconstruccion del alineamiento desde la matriz de puntuacion
//     string alineamiento1 = "", alineamiento2 = "";
//     int i = m, j = n;

//     ahora hay que recorrerla para encontrar el alineamiento correcto :)
