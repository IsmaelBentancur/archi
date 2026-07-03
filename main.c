#include <stdio.h>
#include <stdlib.h>
#include "socios.h"
#include "Matriz.h"

#define ARCH_DAT_SUCURSAL_C "Archivos/envios_sucursal_C.dat"
#define ARCH_TXT_SUCURSAL_D "Archivos/envios_sucursal_D.txt"
#define ARCH_TXT_UNIFICADOS "Archivos/envios_sucursal_unificado.txt"

void ejercicio1(void);
void ejercicio2(void);


int main()
{
    printf("==================== Ejercicio 1 ====================\n");
    ejercicio1();

    printf("==================== Ejercicio 2 ====================\n");
    ejercicio2();

    return 0;
}

void ejercicio1(void){
    fusionar_archivos_ALU(ARCH_DAT_SUCURSAL_C,ARCH_TXT_SUCURSAL_D,ARCH_TXT_UNIFICADOS);
}

void ejercicio2(void){
    int m[ORDEN][ORDEN] = { {1,2,3,4,5,6,7},
                            {1,2,3,4,5,6,7},
                            {1,2,3,4,5,6,7},
                            {1,2,3,4,5,6,7},
                            {1,2,3,4,5,6,7},
                            {1,2,3,4,5,6,7},
                            {1,2,3,4,5,6,7}
                          };
    mostrarMatriz(m,ORDEN,ORDEN);
    printf("\nLa suma del triangulo derecho es: %d\n", sumarTrianguloDerecho(m,ORDEN));
}
