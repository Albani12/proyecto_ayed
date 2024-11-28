# proyecto_ayed
Alineador de secuencias

Este programa está destinado a alinear secuencias de ADN según el algoritmo Needleman-Wunsch. El programa muestra la matriz resultante de acuerdo con el valor de penalización utilizado.
Advertencias:
Este programa admite un total de máximo 1000 caracteres.
Uso exclusivo para linux.
## Instalación
1. Clona este repositorio:
   ```bash
Clone https://github.com/Albani12/proyecto_ayed.git
2. Compila el programa:
g++ -o proyecto_ayed.cpp
3. Ejecuta:
./a.out -C1 <archivo_cadena1> -C2 <archivo_cadena2> -U <archivo_matriz> -V <valor_penalizacion>
##Uso:
Asegúrate de tener un archivo .txt con el siguiente formato.
 1 -1 -1
-1  1 -1
-1 -1  1
Las secuencias deben estar en formato .txt sin información adicional y en archivos separados.
Para generar la imagen usa:

dot -Tpng alineamiento.dot -o alineamiento.png

Ejemplo de uso:
./a.out -C1 secuencia2.txt -C2 secuencia1.txt -U matriz.txt -V -1
El programa permite ver la matriz con las secuencias y sus puntajes. Además, se mostrará el alineamiento y el mayor puntaje.
##Creditos:
Creado por Albani (https://github.com/Albani12) y Karin (https://github.com/Karin-Zuniga)
	
