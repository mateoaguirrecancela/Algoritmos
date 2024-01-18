#include <time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#define UMBRAL 1

/*
 * Algoritmos -> Práctica 4
 * Íker García Calviño <iker.gcalvino> -> grupo 4.4
 * Juan Toirán Freire <juan.tfreire> -> grupo 4.4
 */

/* Funciones auxiliares: */

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

void vector_ord(int v[], int n)
{
    int i, cont = 0;
    for (i = 0; i < n; i++)
        if (v[i] <= v[i + 1])
            cont++;
    if (cont == n - 1)
        printf("  -> el vector está ordenado.\n");
    else
        printf("  -> el vector no está ordenado.\n");
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void ord_ins(int v[], int n)
{
    int i, x, j;

    for (i = 0; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

/* Algoritmo Quicksort: */

int numaleatorio(int M, int N)
{
    return (rand() % (N - M + 1) + M);
}

void intercambiar(int *a, int *b)
{
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

void rapida_aux(int v[], int izq, int der)
{
    int pivote, x, i, j;

    if ((izq + UMBRAL) <= der)
    {
        x = numaleatorio(izq, der);
        pivote = v[x];
        intercambiar(&v[izq], &v[x]);
        i = izq + 1;
        j = der;
        while (i <= j)
        {
            while (i <= der && v[i] < pivote)
                i = i + 1;
            while (v[j] > pivote)
                j = j - 1;
            if (i <= j)
            {
                intercambiar(&v[i], &v[j]);
                i = i + 1;
                j = j - 1;
            }
        }
        intercambiar(&v[izq], &v[j]);
        rapida_aux(v, izq, j - 1);
        rapida_aux(v, j + 1, der);
    }
}

void ord_rapida(int v[], int n)
{
    rapida_aux(v, 0, n - 1);
    if (UMBRAL > 1)
        ord_ins(v, n);
}

void test()
{
    int tam = 25;
    int v[tam];

    printf("Quicksort:\n");
    printf(" - Umbral = %d\n", UMBRAL);
    printf(" 1. Vector ascendente:\n");
    ascendente(v, tam);
    print_vector(v, tam);
    ord_rapida(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);
    printf("\n 2. Vector descendente:\n");
    descendente(v, tam);
    print_vector(v, tam);
    ord_rapida(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);
    printf("\n 3. Vector aleatorio:\n");
    aleatorio(v, tam);
    print_vector(v, tam);
    ord_rapida(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);
}

double tiempos(void (*alg)(int v[], int tamanho),
               void (*vector)(int v[], int tamanho),
               int tamanho, int k)
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

void tiempos_asc() {
    double tiempo = 0.0, tmax = 1500000.0;
    int n, k = 1000, max = 1024000;
    if (UMBRAL == 1) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.07\n");
        printf("\t - Cota sobreestimada (sob): n^1.25\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, ascendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.07), tiempo/pow(n, 1.25));
        }
    }
    if (UMBRAL == 10) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.09\n");
        printf("\t - Cota sobreestimada (sob): n*log(n)\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, ascendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.09), tiempo/(n * log(n)));
        }
    }
    if (UMBRAL == 100) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.09\n");
        printf("\t - Cota sobreestimada (sob): n*log(n)\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, ascendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.09), tiempo/(n * log(n)));
        }
    }
}

void tiempos_des() {
    double tiempo = 0.0, tmax = 1500000.0;
    int n, k = 1000, max = 1024000;
    if (UMBRAL == 1) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.07\n");
        printf("\t - Cota sobreestimada (sob): n^1.16\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, descendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.07), tiempo/pow(n, 1.16));
        }
    }
    if (UMBRAL == 10) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.16\n");
        printf("\t - Cota sobreestimada (sob): n^1.25\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, descendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.16), tiempo/pow(n, 1.25));
        }
    }
    if (UMBRAL == 100) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.16\n");
        printf("\t - Cota sobreestimada (sob): n^1.25\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, descendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.16), tiempo/pow(n, 1.25));
        }
    }
}

void tiempos_rnd() {
    double tiempo = 0.0, tmax = 1500000.0;
    int n, k = 1000, max = 1024000;
    if (UMBRAL == 1) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.08\n");
        printf("\t - Cota sobreestimada (sob): n*log(n)\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, aleatorio, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.08), tiempo/(n * log(n)));
        }
    }
    if (UMBRAL == 10) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n*log(n)\n");
        printf("\t - Cota sobreestimada (sob): n^1.2\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, aleatorio, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/(n * log(n)), tiempo/pow(n, 1.2));
        }
    }
    if (UMBRAL == 100) {
        printf("\t - Cota subestimada (sub): n\n");
        printf("\t - Cota ajustada (aj): n^1.09\n");
        printf("\t - Cota sobreestimada (sob): n*log(n)\n\n");
        printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
               "     t(n)/sob\n");
        for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
            tiempo = tiempos(ord_rapida, aleatorio, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
            n, tiempo, tiempo/n, tiempo/pow(n, 1.09), tiempo/(n * log(n)));
        }
    }
}

void tiempo_alg()
{
    printf("\nOrdenación rápida:\n");
    printf("\nPara un umbral = %d:\n", UMBRAL);
    printf("\n\tVector ascendente:\n");
    tiempos_asc();
    printf("\n\tVector descendente:\n");
    tiempos_des();
    printf("\n\tVector aleatorio:\n");
    tiempos_rnd();
}

int main()
{
    inicializar_semilla();
    test();
    tiempo_alg();
    return 0;
}