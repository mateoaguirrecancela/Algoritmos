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

matriz crearMatriz(int n){
    int i;
    matriz aux;
    if ((aux = malloc(n * sizeof(int *))) == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        if ((aux[i] = malloc(n * sizeof(int))) == NULL)
            return NULL;
    return aux;
}

void liberarMatriz(matriz m, int n){
    int i;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void imprimirMatriz(matriz m, int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%3d", m[i][j]);
        }
        printf("\n");
    }
}

void introducirValores(matriz m, int n, int p[n][n]){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            m[i][j] = p[i][j];
        }
    }
}

void dijkstra(matriz grafo, matriz distancias, int tam){
    int n, i, j, min, count, v = 0;
    int *noVisitados = malloc(tam * sizeof(int));
    for (n = 0; n < tam; n++){
        for (i = 0; i < tam; i++){
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;

        for (count = 0; count < tam - 2; count++){
            min = TAM_MAX;

            for (i = 0; i < tam; i++){
                if (noVisitados[i] && distancias[n][i] < min){
                    min = distancias[n][i];
                    v = i;
                }
            }

            noVisitados[v] = 0;

            for (j = 0; j < tam; j++){
                if (noVisitados[j] && distancias[n][j] > distancias[n][v] + grafo[v][j]){
                    distancias[n][j] = distancias[n][v] + grafo[v][j];
                }
            }
        }
    }
    free(noVisitados);
}

double microsegundos(){ /*obtiene la hora del sistema en microsegundos*/
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tabla(int n, double t, double sub, double cota, double sobre, bool promedio){
    if (promedio){
        printf("(*)\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
    else{
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
}

void inicializar_semilla(){
    srand(time(NULL));
    /*se establece la semilla de una nueva serie de enteros pseudo-aleatorios*/
}

// Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
// no dirigido con n nodos, representado por su matriz de adayencia
void iniMatriz(matriz m, int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n; j++){
            m[i][j] = rand() % TAM_MAX + 1;
        }
    }
    for (i = 0; i < n; i++){
        for (j = 0; j <= i; j++){
            if (i == j){
                m[i][j] = 0;
            }
            else{
                m[i][j] = m[j][i];
            }
        }
    }
}

void test(){
    int n = 5, n1 = 4;
    int p[5][5] = {{0, 1, 8, 4, 7}, {1, 0, 2, 6, 5}, {8, 2, 0, 9, 5}, {4, 6, 9, 0, 3}, {7, 5, 5, 3, 0}};
    int p1[4][4] = {{0, 1, 4, 7}, {1, 0, 2, 8}, {4, 2, 0, 3}, {7, 8, 3, 0}};

    matriz m, d, m1, d1;
    m = crearMatriz(n);
    introducirValores(m, n, p);
    d = crearMatriz(n);

    imprimirMatriz(m, n);
    printf("\n");
    dijkstra(m, d, n);
    imprimirMatriz(d, n);
    printf("\n");

    m1 = crearMatriz(n1);
    introducirValores(m1, n1, p1);
    d1 = crearMatriz(n1);

    imprimirMatriz(m1, n1);
    printf("\n");
    dijkstra(m1, d1, n1);
    imprimirMatriz(d1, n1);
    printf("\n");

    liberarMatriz(m, n);
    liberarMatriz(m1, n1);
    liberarMatriz(d, n);
    liberarMatriz(d1, n1);
}

void testComplejidad(){
    int i, n = 15, k = 1000;
    double inicio, final, t;
    bool promedio = false;
    matriz m, d; // inicializar el puntero a NULL

    m = crearMatriz(TAM_MAX); // asignar memoria
    d = crearMatriz(TAM_MAX); // asignar memoria

    printf("\nTabla para demostrar la complejidad de dijkstra O(n):\n");
    printf("\t     n\t\t   t(n)\t    t(n)/n^2.55\t   t(n)/n^2.825\t     t(n)/n^3.1\n");
    while (n <= TAM_MAX){
        promedio = false;
        iniMatriz(m, n);

        inicio = microsegundos();
        dijkstra(m, d, n);
        final = microsegundos();
        t = final - inicio;
        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; i++){
                iniMatriz(m, n);
                dijkstra(m, d, n);
            }
            final = microsegundos();
            t = final - inicio;
            inicio = microsegundos();
            for (i = 0; i < k; i++){
                iniMatriz(m, n);
            }
            final = microsegundos();
            t = (t - (final - inicio)) / k;
        }
        tabla(n, t, pow(n, 2.55), pow(n, 2.825), pow(n, 3.1), promedio);
        n = n * 2;
    }
    liberarMatriz(m, TAM_MAX);
    liberarMatriz(d, TAM_MAX);
}

int main(){
    inicializar_semilla();

    test();
    testComplejidad();

    return 0;
}