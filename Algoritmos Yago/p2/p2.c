#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

/*
 * Algoritmos -> Práctica 2
 * Íker García Calviño <iker.gcalvino> -> grupo 4.4
 * Juan Toirán Freire <juan.tfreire> -> grupo 4.4
 */

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

void ord_shell(int v[], int n)
{
    bool seguir;
    int i, j, tmp = 0;
    int incremento = n;

    do
    {
        incremento = incremento / 2;
        for (i = incremento; i < n; i++)
        {
            tmp = v[i];
            j = i;
            seguir = true;
            while ((j - incremento >= 0) && seguir)
            {
                if (tmp < v[j - incremento])
                {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                }
                else
                {
                    seguir = false;
                }
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
}

void inicializar_semilla()
{
    srand(time(NULL));
}

void aleatorio(int v[], int n)
{ /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
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

double microsegundos()
{
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0)
    {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void print_vector(int v[], int n)
{
    int i;
    printf("  [");
    for (i = 0; i < n; i++)
    {
        printf("%3d", v[i]);
        if (i != n - 1)
        {
            printf(",");
        }
    }
    printf("]\n");
}

void vector_ord(int v[], int n)
{
    int i, cont = 0;
    for (i = 0; i < n; i++)
    {
        if (v[i] <= v[i + 1])
        {
            cont++;
        }
    }
    if (cont == n - 1)
    {
        printf("\t -> el vector está ordenado.\n");
    }
    else
    {
        printf("\t -> el vector no está ordenado.\n");
    }
}

void test_ins()
{
    int tam = 25;
    int v[tam];
    printf("Algoritmo Inserción:\n");
    printf(" 1. Vector ascendente:\n");
    ascendente(v, tam);
    print_vector(v, tam);
    ord_ins(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);

    printf(" 2. Vector descendente:\n");
    descendente(v, tam);
    print_vector(v, tam);
    ord_ins(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);

    printf(" 3. Vector aleatorio:\n");
    aleatorio(v, tam);
    print_vector(v, tam);
    ord_ins(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);
}

void test_shell()
{
    int tam = 25;
    int v[tam];
    printf("Algoritmo Shell:\n");
    printf(" 1. Vector ascendente:\n");
    ascendente(v, tam);
    print_vector(v, tam);
    ord_shell(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);

    printf(" 2. Vector descendente:\n");
    descendente(v, tam);
    print_vector(v, tam);
    ord_shell(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);

    printf(" 3. Vector aleatorio:\n");
    aleatorio(v, tam);
    print_vector(v, tam);
    ord_shell(v, tam);
    print_vector(v, tam);
    vector_ord(v, tam);
}

double tiempos(void (*alg)(int v[], int tamanho),
               void (*vector)(int v[], int tamanho), int tamanho, int k)
{
    double t1, t2, t, prima;
    int i;
    int *v;
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
        {
            vector(v, tamanho);
        }
        t2 = microsegundos();
        t = t2 - t1;
        t = (prima - t) / k;
    }
    free(v);
    return t;
}

void tiempo_ins()
{
    int k = 1000;
    double tiempo = 0.0;
    int n;
    printf("\nOrdenación por inserción:\n");
    printf("\tVector ascendente:\n\t - Cota subestimada (sub): n^(0.8)\n");
    printf("\t - Cota ajustada (aj): n\n");
    printf("\t - Cota sobreestimada (sob): n^(1.2)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_ins, ascendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 0.8)), tiempo / n,
               tiempo / (pow(n, 1.2)));
    }
    printf("\n\tVector descendente:\n\t - Cota subestimada (sub): n^(1.8)\n");
    printf("\t - Cota ajustada (aj): n^(2.0)\n");
    printf("\t - Cota sobreestimada (sob): n^(2.2)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 64000; n = n * 2) {
        tiempo = tiempos(ord_ins, descendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 1.8)), tiempo / (pow(n, 2)),
               tiempo / (pow(n, 2.2)));
    }
    printf("\n\tVector aleatorio:\n\t - Cota subestimada (sub): n^(1.8)\n");
    printf("\t - Cota ajustada (aj): n^(2.0))\n");
    printf("\t - Cota sobreestimada (sob): n^(2.2)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 128000; n = n * 2) {
        tiempo = tiempos(ord_ins, aleatorio, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 1.8)), tiempo / (pow(n, 2)),
               tiempo / (pow(n, 2.2)));
    }
}

void tiempo_shell()
{
    int k = 1000;
    double tiempo = 0.0;
    int n;
    printf("\nOrdenación por shell:\n");
    printf("\tVector ascendente:\n\t - Cota subestimada (sub): n^(0.8)\n");
    printf("\t - Cota ajustada (aj): n^(1.01)*log2(n)\n");
    printf("\t - Cota sobreestimada (sob): n^(1.2)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_shell, ascendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 0.8)),
               tiempo / (pow(n, 1.01) * log2(n)), tiempo / (pow(n, 1.2)));
    }
    printf("\n\tVector descendente:\n\t - Cota subestimada (sub): n^(1.0)\n");
    printf("\t - Cota ajustada (aj): n^(1.09)\n");
    printf("\t - Cota sobreestimada (sob): n^(1.3)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_shell, descendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / n, tiempo / (pow(n, 1.09)),
               tiempo / (pow(n, 1.3)));
    }
    printf("\n\tVector aleatorio:\n\t - Cota subestimada (sub): n^(1.0)\n");
    printf("\t - Cota ajustada (aj): n^(1.24))\n");
    printf("\t - Cota sobreestimada (sob): n^(1.4)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_shell, aleatorio, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / n, tiempo / (pow(n, 1.24)),
               tiempo / (pow(n, 1.4)));
    }
}

int main()
{
    inicializar_semilla();
    test_ins();
    test_shell();
    tiempo_ins();
    tiempo_shell();
    return 0;
}