#include <iostream>
#include <fstream>
#include <string>

//holi, si pude modificar

using namespace std;

/*Funcion menu?*/

/*abrir archivos y crear arreglos*/
void abrir_y_leer_archivo(char *arr, string nombre_archivo, int largo){
    int i = 0;
    ifstream archivo;
    archivo.open(nombre_archivo);
    for (int i = 0; i < largo; i++)
    {
        archivo >> arr[i];
    }
    
}

/*emparejar bases. Matrices*/
void compara_bases(char prin, char sec){
    
}

//ciclos


int main(int argc, char const *argv[])
{
    /*inicializar arreglos*/
    int largo = 100;
    char principal[largo] = {0};
    char secundaria[largo] = {0};
    int i = 0;
    string nombre = "prueba.txt";
    abrir_y_leer_archivo(principal, nombre, largo);
    while (principal[i] != 0)
    {
        cout << " " << principal[i];
        i++;
    }
    cout << endl;


    /*menu?*/ 
    return 0;
}
