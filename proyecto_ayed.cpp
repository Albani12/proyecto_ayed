#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;
const int MAX_LARGO = 1000; //tamaño maximo de secuencias
const int MAX_MATRIZ = 4;   // tamaño máximo de la matriz para A, T, C, G

/*abrir archivos y crear arreglos*/
//Funcion para abrir y leer un archivo, almacenando su contenido en un arreglo
int abrir_y_leer_archivo(char *arr, string nombre_archivo, int largo){
    ifstream archivo(nombre_archivo); //abre archivo
    if (!archivo.is_open()) { //verifica si ek arhcivo abre correctamente
        cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << endl;
        return 0;
    }

    int i = 0; //contador para la longitud de secuencia
    //lee el archvivo caracter por caracter, maximo tamaño de 1000 
    //o el final del archivo
    while (archivo >> arr[i] && i < largo)  { 
        i++; //se increment el contador
    }
    archivo.close(); //se cierra el archivo despues de leer
    arr[i] = '\0'; //termina la cadena
    return i; //longitud de la secuencia leida
}

//Función para cargar la matriz de emparejamiento y el valor V *DF*
void cargar_matriz_y_valor(const string archivo_matriz, int matriz[MAX_MATRIZ][MAX_MATRIZ]) {
    ifstream file(archivo_matriz);

    if (file.is_open()) {
         // Leer la matriz
        for (int i = 0; i < MAX_MATRIZ; i++) {
            for (int j = 0; j < MAX_MATRIZ; j++) {
                file >> matriz[i][j];

            }
        }
        file.close();
        
    } else {
        cerr << "Error al abrir el archivo de matriz." << endl;
    }
}


    
//valida que tamanos de los arreglos sean mayores a cero
//funcion para validar que las longitudes de las secuencias sean mayores a 0
void validar_tamanos(int m, int n){
    if (m == 0 || n == 0) {
        cerr << "Error: No se pudieron leer las secuencias." << endl;
    }    
}

void mostrar_alineamiento(char *alineamiento1, char *alineamiento2, int m, int n){
    for (int i = 0; i <= m + n + 1; i++)
    {
        if (alineamiento1 != 0)
        {
            cout << " " << alineamiento1[i] << " ";
        }
        
    }
    cout << endl;

    for (int i = 0; i <= m + n + 1; i++)
    {
        if (alineamiento2 != 0)
        {
            cout << " " << alineamiento2[i] << " ";
        }
        
        
    }
    cout << endl;
    
}

//Funcion principal que implementa el algoritmo de Needleman-Wunsch
void compara_bases(char *prin, char *sec, string primer_archivo, string segundo_archivo, int valorV, int largo, int matriz[MAX_MATRIZ][MAX_MATRIZ]){
    //leer las secuencias desde los archivos
    /*crea el arreglo con la cadena de cada uno de los archivos y devuelve sus tamanos*/

    int m = abrir_y_leer_archivo(prin, primer_archivo, largo);
    int n = abrir_y_leer_archivo(sec, segundo_archivo, largo);
    validar_tamanos(m,n); // valida que los tamanos no sean 0 (osea que exista algo en el archivo)

    
    //se crea la matriz estatica para almacenar las puntuaciones
    //le puse matrix porque matriz se llama la del parametro
    int matrix[MAX_LARGO][MAX_LARGO] = {0}; 

    //Parámetros del algoritmo, se leen desde la matriz que va de parámetro de entrada
    int match = matriz[0][0]; //Match: Si las bases actuales son iguales "coinciden"
    int mismatch = matriz[1][2]; //Mismatch: Si las bases son diferentes "no coinciden"
    int gap = valorV;


    
    //Ahora inicializa la primera fila y columna de la matriz
    for (int i = 0; i <= m; i++) {
        matrix[i][0] = i*gap;     //*gap porq la primera fila y columna va con negativos, se rellena la primera columna con gaps
    }

    for (int j = 0; j <= n; j++) {
        matrix[0][j] = j*gap; //rellena la primera fila con gaps
    }

    //Llena la matriz
    for (int i = 1; i <= m; i++) { //itera sobre filas
        for (int j = 1; j <= n; j++) { //itera sobre columnas

            int arriba = matrix[i-1][j] + gap;
            //costo de introducir un gap en la segunda secuencia

            int izq = matrix[i][j-1] + gap;
            //costo de introducir un gap en la primera secuencia

            int diagonal; 
            //la variable almacena el costo de coindicencia o no

            //compara las bases actuales para ver si coincide o no
            if (prin[i-1] == sec[j-1]) {
                diagonal = matrix [i-1][j-1] + match; //coinciden
            } else {
                diagonal = matrix[i-1][j-1] + mismatch; //no coinciden
            }
            
            matrix[i][j]= max(diagonal, max(arriba, izq));
            //almacena maximo valor de las 3 opciones posibles
            
        }
        
    }
    //Se imprime la matriz de puntuaciones
    cout << "Matriz de puntuaciones:\n " << endl; 
    cout << "           ";

    for (int i = 0; i < m; i++) { 
        cout << sec[i] << "     ";
    }

    cout << endl;
    cout << "      ";

    for (int i = 0; i <= m; i++) { //itera sobre filas
        for (int j = 0; j <= n; j++) { //itera sobre columnas
            cout << matrix [i][j]<< "    "; //imprime cada valor de la matriz
        }
        cout << "\n";
        cout << "  " << prin[i] << "  ";
    }
    cout << endl;

    cout<<"A continuacion se muestran los alineamientos:"<< endl;

    //RECONSTRUCCION DEL ALINEAMIENTO

    char alineamiento1[n + m + 1] = {0}; //arreglo para alinear la secuencia
    char alineamiento2[n + m + 1] = {0}; //arreglo para alinear la secuencia
    //ahora la reconstruccion del alineamiento desde la matriz
    int posicion = n + m + 1; //variable de seguimiento de posicion actual. Corresponde a la ultima posicion del arreglo y ahi comienza
    // se compara la matriz para el alineamiento
    int i = n + 2;
    int j = m + 2;
    int puntaje_final = matrix[i-1][j-1];
    

    while (j > 0 || i > 0)
    {
        int arriba = matrix[i-1][j];
        int izq = matrix[i][j-1];
        int diagonal = matrix[i-1][j-1];
        if (diagonal >= arriba && diagonal >= izq )
        {
            alineamiento1[posicion] = prin[i-1];
            alineamiento2[posicion] = sec[j-1];
            puntaje_final = puntaje_final + matrix[i-1][j-1];
            j--;
            i--;
            
        }
        else if (arriba > diagonal && arriba >= izq )
        {

            alineamiento1[posicion] = prin[i-1];
            alineamiento2[posicion] = '-';
            puntaje_final = puntaje_final + matrix[i-1][j];
            i--;
            
        }
        else if (izq > diagonal && izq > arriba)
        {
            alineamiento1[posicion] = '-';
            alineamiento2[posicion] =  sec[j-1];
            puntaje_final = puntaje_final + matrix[i][j-1];
            j--;
            
        }
        else
        {
            cout << "algo no funciona" << endl;
        }
        

        posicion--;
        
    }
    cout << "puntaje final: " << puntaje_final << endl;

    mostrar_alineamiento(alineamiento1, alineamiento2, m, n);

    //Se genera el arhivo .dot para la imagen en Graphiz
    ofstream archivo("alineamiento.dot");
    archivo << "graph Alineamiento {" << endl;  

    archivo << "orientation=L;" << endl; // Orientación de arriba hacia abajo
    archivo << "node [shape=box, style=filled, fillcolor=pink];" << endl;
    
    // Crear nodos para la secuencia 1 y la secuencia 2
    for ( size_t k = 0; k < n + m + 1; ++k) {
        if (alineamiento1[k] !=0)
        {
            archivo << "n1_" << k << " [label=\"" << alineamiento1[k] << "\"];" << endl; // Nodo de la secuencia 1
        }
        if (alineamiento2[k] != 0)
        {
            archivo << "n2_" << k << " [label=\"" << alineamiento2[k] << "\"];" << endl;
            archivo << "{ rank=same; n1_" << k << "; n2_" << k << "; }" << endl;
        }
        
         /// Nodo de la secuencia 2

        // Conectar los nodos de la secuencia 1 y 2
            // Conexión entre n1_k y n2_k si ambos son iguales y no son '-'
        if (alineamiento1[k] != '-' && alineamiento2[k] != '-' && alineamiento1[k] != 0 && alineamiento2[k] != 0 )// && alineamiento1[k] == alineamiento2[k]) 
        {
            archivo << "n1_" << k << " -- n2_" << k << " [color=blue];" << endl;
        }
        else if (alineamiento1[k] == '-' || alineamiento2[k] == '-' && alineamiento1[k] != 0 && alineamiento2[k] != 0) {
            archivo << "n1_" << k << " -- n2_" << k << " [color=red, style=dashed];" << endl; // Gap
        }

        // Conexiones adyacentes dentro de la secuencia 1 (siempre y cuando no se pase del límite)
        if (alineamiento1[k] != 0 && alineamiento2[k] != 0)
        {
            
            if (k < n + m) {
                archivo << "n1_" << k << " -- n1_" << k + 1 << " [color=gray, style=dashed];" << endl;
                archivo << "n2_" << k << " -- n2_" << k + 1 << " [color=gray, style=dashed];" << endl;
            }
            /* code */
        }
    }

    archivo << "}" << endl;
    archivo.close();
    
    // Usar Graphviz para generar la imagen
    //system("dot -Tpng -o alineamiento.png alineamiento.dot");
    //system("start alineamiento.png"); // Visualizar la imagen generada en Windows
}

int main(int argc, char const *argv[]) {

    if (argc != 9) {
        cerr << "Uso: " << argv[0] << " -C1 <archivo_cadena1> -C2 <archivo_cadena2> -U <archivo_matriz> -V <valor_penalizacion>" << endl;
        return 1;
    }

    char principal[MAX_LARGO];
    char secundaria[MAX_LARGO];
    int matriz[MAX_MATRIZ][MAX_MATRIZ];
    int valorV; // Inicializar el valor de penalización, puntaje de no emparejar

    // Leer los parámetros de entrada
    string archivo_principal, archivo_secundaria, archivo_matriz;
    

    for (int i = 1; i < argc; i++) { 
        if (string(argv[i]) == "-C1") {
            archivo_principal = argv[++i];  //lee el argumento como el archivo principal
        } else if (string(argv[i]) == "-C2") {
            archivo_secundaria = argv[++i]; //lee el argumento como el archivo secundaria
        } else if (string(argv[i]) == "-U") {
            archivo_matriz = argv[++i];
        } else if (string(argv[i]) == "-V") {
            valorV = atoi(argv[++i]); // Convertir el valor a entero
        }
    }

    // Leer las cadenas desde los archivos
    abrir_y_leer_archivo(principal, archivo_principal, MAX_LARGO);
    abrir_y_leer_archivo(secundaria, archivo_secundaria, MAX_LARGO);
    // Cargar la matriz de emparejamiento
    cargar_matriz_y_valor(archivo_matriz, matriz);
    // Llamar a la función para comparar las secuencias
    int gap = valorV; // Usar el valor de penalización como gap
    compara_bases(principal, secundaria, archivo_principal, archivo_secundaria, gap, MAX_LARGO, matriz); 

    return 0;
    
}
