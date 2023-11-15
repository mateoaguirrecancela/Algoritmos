// Practica 4 Algoritmos
// Autor 1: Mateo Aguirre Cancela    |   mateo.aguirre
// Autor 2: Martin del Rio Alvarez   |   martin.delrio.alvarez
// Grupo: 2.2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define TAM_MAX 1000

typedef int **matriz;

matriz crearMatriz(int n)
{
    int i;
    matriz aux;
    if ((aux = malloc(n * sizeof(int *))) == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        if ((aux[i] = malloc(n * sizeof(int))) == NULL)
            return NULL;
    return aux;
}
//Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
//no dirigido con n nodos, representado por su matriz de adayencia
void iniMatriz(matriz m, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            m[i][j] = rand() % TAM_MAX + 1;
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}
void liberarMatriz(matriz m, int n)
{
    int i;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void imprimirMatriz(matriz m, int n){
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%5d", m[i][j]);
        }
        printf("\n");
    }
}

void introducirValores(matriz m, int **p, int n){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            m[i][j]=p[i][j];
        }
    }
}

void dijkstra(matriz grafo, matriz distancias, int tam)
{
    int n, i, j, min, count, v = 0;
    int *noVisitados = malloc(tam * sizeof(int));
    for (n = 0; n < tam; n++)
    {
        for (i = 0; i < tam; i++)
        {
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;
        /*
        ...
        */
        for (count = 0; count < tam - 2; count++) {
            min = TAM_MAX;

            for (i = 0; i < tam; i++) {
                if (noVisitados[i] && distancias[n][i] < min) {
                    min = distancias[n][i];
                    v = i;
                }
            }

            noVisitados[v] = 0;

            for (j = 0; j < tam; j++) {
                if (noVisitados[j] && distancias[n][j] > distancias[n][v] + grafo[v][j]) {
                    distancias[n][j] = distancias[n][v] + grafo[v][j];
                }
            }
        }
    }
    free(noVisitados);
}

void test(){
    int n=5;
    int p[][5]={{0,1,8,4,7},{1,0,2,6,5},{8,2,0,9,5},{4,6,9,0,3},{7,5,5,3,0}};
    matriz m, d;
    m=crearMatriz(n);
    introducirValores(m, p, n);
    d=crearMatriz(n);

    imprimirMatriz(m, n);
    printf("\n");
    dijkstra(m, d, n);
    imprimirMatriz(m, n);
    printf("\n");
    imprimirMatriz(d, n);
    printf("\n");

    liberarMatriz(m, n);
}


void inicializar_semilla()
{
    srand(time(NULL));
    /*se establece la semilla de una nueva serie de enteros pseudo-aleatorios*/
}

void aleatorio(int v[], int n)
{
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
    {
        v[i] = (rand() % m) - n;
    } /* se generan números pseudoaleatorio entre -n y +n */
}


















int main(){
    inicializar_semilla();

    test();

    return 0;
}