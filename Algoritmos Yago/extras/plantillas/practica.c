#include <time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

/*
 * Algoritmos
 * Íker García Calviño <iker.gcalvino> -> grupo 4.4
 */

void inicializar_semilla()
{
    srand(time(NULL));
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
}

void aleatorio(int v[], int n)
{ /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void print_vector(int v[], int n)
{
    int i;
    printf("  [");
    for (i = 0; i < n; i++)
    {
        printf("%3d", v[i]);
        if (i != n - 1)
            printf(",");
    }
    printf("]\n");
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double tiempos(void (*alg)(int v[], int tamanho),
               void (*vector)(int v[], int tamanho), int tamanho, int k)
{
    double t1, t2, t, prima;
    int *v;
    int i;
    v = malloc(tamanho * sizeof(int));
    vector(v, tamanho);

    t1 = microsegundos();
    alg(v, tamanho);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500)
    {
        printf("(*)");
        t1 = microsegundos();
        for (i = 0; i < k; i++)
        {
            vector(v, tamanho);
            alg(v, tamanho);
        }
        t2 = microsegundos();
        prima = t2 - t1;
        t1 = microsegundos();
        for (i = 0; i < k; i++)
            vector(v, tamanho);
        t2 = microsegundos();
        t = t2 - t1;
        t = (prima - t) / k;
    }
    free(v);
    return t;
}

int main()
{
    inicializar_semilla();

    return 0;
}