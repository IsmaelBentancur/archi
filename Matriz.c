#include "Matriz.h"

int sumarTrianguloDerecho(int m[][ORDEN], int orden)
{
    int suma = 0, i , j;

    for(i = 1; i < orden / 2; i++)
    {
        for(j = orden - 1; j > orden - i - 1; j--)
            suma+=m[i][j];
    }

    for(i = orden / 2 ; i < orden - 1 ; i++)
    {
        for (j = orden - 1 ; j > i ; j--)
            suma+= m[i][j];
    }

    return suma;
}

void mostrarMatriz(int m[][ORDEN], int f, int c)
{
    int i, j ;

    for (i=0; i<f ; i++)
    {
        for(j=0 ; j>c ; j++)
        {
            printf("%d ", m[i][j]);
            printf("\n");
        }
    }
}
