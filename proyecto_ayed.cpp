#include <iostream>
#include <fstream>
#include <string>

//holi, si pude modificar

using namespace std;

/*Funcion menu?*/

/*abrir archivos y crear arreglos*/
int abrir_y_leer_archivo(char *arr, string nombre_archivo){
    int i = 0;
    ifstream archivo;
    archivo.open(nombre_archivo);
    archivo >> arr;
    while (arr[i] != 0)
    {
        i++;
    }
    cout << i << endl;
    
    return i;
    
}

/*emparejar bases. Matrices*/
void compara_bases(char *prin, char *sec, string primer_archivo, string segundo_archivo){
    int m = abrir_y_leer_archivo(prin, primer_archivo);
    int n = abrir_y_leer_archivo(prin, segundo_archivo);
    int matriz[m+1][n+1] = {0};
    int mayor;
    if (m > n)
    {
        mayor = m;
    }
    else
    {
        mayor = n;
    }
    
    
    for (int i = 1; i < mayor; i++)
    {
        matriz[i][0] = -i;      
        matriz[0][i] = -i;      
    }

    for (int i = 1; i < mayor; i++)
    {
        for (int j = 1; j < mayor; i++)
        {
            int arriba = matriz[i-1][j];
            int diagonal = matriz[i-1][j-1];
            int izq = matriz[i][j-1];

            
        }
        
    }
    

    
    
}


int main(int argc, char const *argv[])
{
    /*inicializar arreglos*/
    int largo = 100;
    char principal[largo] = {0};
    char secundaria[largo] = {0};
    int i = 0;
    string nombre = "prueba.txt";
    int largo_real = abrir_y_leer_archivo(principal, nombre);
    while (principal[i] != 0)
    {
        cout << " " << principal[i];
        i++;
    }
    cout << endl;


    /*menu?*/ 
    return 0;
}
