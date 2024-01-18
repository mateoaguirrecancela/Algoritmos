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

void intercambiar(int *a, int *b)
{
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

void auxord(int v[], int iz, int dr)
{
    int i = 0, j = 0;
    if (iz < dr)
    {
        j = dr;
        for (i = (dr - 1); i >= iz; i--)
        {
            if (v[i] > v[dr])
            {
                j = j - 1;
                intercambiar(&v[i], &v[j]);
            }
        }
        intercambiar(&v[j], &v[dr]);
        auxord(v, iz, j - 1);
        auxord(v, j + 1, dr);
    }
}

void ordenar(int v[], int n)
{
    auxord(v, 0, n - 1);
}

void test()
{
    int tam = 25;
    int v[tam];

    printf("Ordenar:\n");
    printf(" 1. Vector ascendente:\n");
    ascendente(v, tam);
    print_vector(v, tam);
    ordenar(v, tam);
    print_vector(v, tam);
    printf("\n 2. Vector descendente:\n");
    descendente(v, tam);
    print_vector(v, tam);
    ordenar(v, tam);
    print_vector(v, tam);
    printf("\n 3. Vector aleatorio:\n");
    aleatorio(v, tam);
    print_vector(v, tam);
    ordenar(v, tam);
    print_vector(v, tam);
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

void tiempo()
{
    int k = 1000;
    double tiempo = 0.0;
    int n;
    printf("\tVector ascendente:\n\t - Cota subestimada (sub): n^(1.6)\n");
    printf("\t - Cota ajustada (aj): n^(2.0)\n");
    printf("\t - Cota sobreestimada (sob): n^(2.25)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 32000; n = n * 2)
    {
        tiempo = tiempos(ordenar, ascendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 1.6)), tiempo / (pow(n, 2)),
               tiempo / (pow(n, 2.25)));
    }
    printf("\n\tVector descendente:\n\t - Cota subestimada (sub): n^(1.5)\n");
    printf("\t - Cota ajustada (aj): n^(2.0)\n");
    printf("\t - Cota sobreestimada (sob): n^(2.25)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 32000; n = n * 2)
    {
        tiempo = tiempos(ordenar, descendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 1.5)), tiempo / (pow(n, 2)),
               tiempo / (pow(n, 2.25)));
    }
    printf("\n\tVector aleatorio:\n\t - Cota subestimada (sub): n^(1.5)\n");
    printf("\t - Cota ajustada (aj): n^(2.0)\n");
    printf("\t - Cota sobreestimada (sob): n^(2.25)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 32000; n = n * 2)
    {
        tiempo = tiempos(ordenar, aleatorio, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 1.5)), tiempo / (pow(n, 2)),
               tiempo / (pow(n, 2.25)));
    }
}

int main()
{
    inicializar_semilla();
    test();
    tiempo();
    return 0;
}