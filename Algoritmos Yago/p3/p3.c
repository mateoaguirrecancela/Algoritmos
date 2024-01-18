#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

/*
 * Algoritmos -> Práctica 3
 * Íker García Calviño <iker.gcalvino> -> grupo 4.4
 * Juan Toirán Freire <juan.tfreire> -> grupo 4.4
 */

/* Funciones auxiliares: */

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

void print_vector(int v[], int n)
{
    int i;
    printf("[");
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

/* Funciones P3: */

struct nodo
{
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};

typedef struct nodo *posicion;
typedef struct nodo *arbol;

static struct nodo *crearnodo(int e)
{
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL)
    {
        printf("memoria agotada\n");
        exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

arbol insertar(int e, arbol a)
{
    if (a == NULL)
        return crearnodo(e);
    else if (e < a->elem)
        a->izq = insertar(e, a->izq);
    else if (e > a->elem)
        a->der = insertar(e, a->der);
    else
        a->num_repeticiones++;
    return a;
}

arbol creararbol()
{
    return NULL;
}

int esarbolvacio(arbol a)
{
    if (a == NULL)
        return 1;
    else
        return 0;
}

posicion hijoizquierdo(arbol a)
{
    return a->izq;
}

posicion hijoderecho(arbol a)
{
    return a->der;
}

int elemento(posicion p)
{
    return p->elem;
}

int numerorepeticiones(posicion p)
{
    return p->num_repeticiones;
}

posicion buscar(int i, arbol a)
{
    if (a == NULL)
        return NULL;
    else if (i == elemento(a))
        return a;
    else if (i < elemento(a))
        return buscar(i, hijoizquierdo(a));
    else if (i > elemento(a))
        return buscar(i, hijoderecho(a));
    else
        return NULL;
}

arbol eliminararbol(arbol a)
{
    if (a != NULL)
    {
        a->izq = eliminararbol(hijoizquierdo(a));
        a->der = eliminararbol(hijoderecho(a));
        free(a);
    }
    return NULL;
}

int altura(arbol a)
{
    int alt = 0, altizq = 0, altder = 0;

    if (esarbolvacio(a))
        return -1;
    else if (esarbolvacio(hijoizquierdo(a)) && esarbolvacio(hijoderecho(a)))
        return 0;
    else
    {
        if (!esarbolvacio(hijoizquierdo(a)))
            altizq += altura(hijoizquierdo(a));
        if (!esarbolvacio(hijoderecho(a)))
            altder += altura(hijoderecho(a));
        if (altizq >= altder)
            alt = altizq;
        else
            alt = altder;
        return ++alt;
    }
}

void visualizar(arbol a)
{
    if (esarbolvacio(a))
        printf("()");
    else
    {
        if (!esarbolvacio(hijoizquierdo(a)))
        {
            printf("(");
            visualizar(hijoizquierdo(a));
            printf(")");
        }
        printf(" %d ", elemento(a));
        if (!esarbolvacio(hijoderecho(a)))
        {
            printf("(");
            visualizar(hijoderecho(a));
            printf(")");
        }
    }
}

void print_test()
{
    int i;
    posicion p;
    arbol a = creararbol();

    printf("arbol vacio: ");
    visualizar(a);
    printf(".\n");
    printf("altura del arbol: %i\n", altura(a));
    printf("inserto un 3\n");
    a = insertar(3, a);
    printf("inserto un 1\n");
    a = insertar(1, a);
    printf("inserto un 2\n");
    a = insertar(2, a);
    printf("inserto un 5\n");
    a = insertar(5, a);
    printf("inserto un 4\n");
    a = insertar(4, a);
    printf("inserto un 5\n");
    a = insertar(5, a);
    printf("arbol: ");
    visualizar(a);
    printf(".\n");
    printf("altura del arbol: %i\n", altura(a));
    for (i = 1; i <= 6; i++)
    {
        p = buscar(i, a);
        if (p != NULL)
            printf("busco %d y encuentro %d repetido: %d veces\n", i,
                   elemento(p), numerorepeticiones(p));
        else
            printf("busco %d y no encuentro nada\n", i);
    }
    printf("borro todos los nodos liberando la memoria:\n");
    a = eliminararbol(a);
    printf("arbol vacio: ");
    visualizar(a);
    printf(".\n");
    printf("altura del arbol: %i\n", altura(a));
}

double tiempos_ins(arbol (*alg)(int v, arbol a), int tamanho, int k, arbol arb)
{
    int i;
    double t1, t2, t;
    int *v = malloc(tamanho * sizeof(int));

    aleatorio(v, tamanho);
    t1 = microsegundos();
    for (i = 0; i < tamanho; i++)
        arb = alg(v[i], arb);
    t2 = microsegundos();
    t = t2 - t1;
    free(v);
    return t;
}

double tiempos_bus(arbol (*alg)(int v, arbol a), int tamanho, int k, arbol arb)
{
    int i, j;
    double t1, t2, t;
    int *v = malloc(tamanho * sizeof(int));

    aleatorio(v, tamanho);
    t1 = microsegundos();
    for (i = 0; i < tamanho; i++)
        alg(v[i], arb);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500)
    {
        printf("(*)");
        t1 = microsegundos();
        for (i = 0; i < k; i++)
            for (j = 0; i < tamanho; i++)
                alg(v[j], arb);
        t2 = microsegundos();
        t = t2 - t1;
    }
    free(v);
    return t;
}

void print_tabla()
{
    arbol arb = creararbol();
    int i, n, k = 1000, max = 1024000;
    int *v = malloc(max * sizeof(int));
    double tiempo = 0.0, tmax = 1500000.0;
    printf("\nInserción de n elementos:\n");
    printf("\t - Cota subestimada [f(n)]: n^(1.1)\n");
    printf("\t - Cota ajustada [g(n)]: n^(1.25)\n");
    printf("\t - Cota sobreestimada [h(n)]: n^(1.3)\n");
    printf("\t      n\t\t\t\t  t(n)\t\t\t    t(n)/f(n)\t\t    t(n)/g(n)\t\t"
           "    t(n)/h(n)\n");
    for (n = 8000; n <= max && tiempo <= tmax; n = n * 2) {
        tiempo = tiempos_ins(insertar, n, k, arb);
        if (tiempo >= 500) /* con n >= 8000 debería de imprimir siempre */
            printf("\t %8d\t\t %15.4f\t\t %14.12f\t\t %14.12f\t\t %14.12f\n",
                   n, tiempo, tiempo / pow(n, 1.1), tiempo / pow(n, 1.25),
                   tiempo / pow(n, 1.3));
        arb = eliminararbol(arb);
    }
    tiempo = 0.0;
    printf("\nBúsqueda de n elementos:\n");
    printf("\t - Cota subestimada [f(n)]: n^(1.1)\n");
    printf("\t - Cota ajustada [g(n)]: n^(1.25)\n");
    printf("\t - Cota sobreestimada [h(n)]: n^(1.3)\n");
    printf("\t      n\t\t\t\t  t(n)\t\t\t    t(n)/f(n)\t\t    t(n)/g(n)\t\t"
           "    t(n)/h(n)\n");
    for (n = 8000; n <= max && tiempo <= tmax; n = n * 2) {
        aleatorio(v, n);
        for (i = 0; i < n; i++)
            arb = insertar(v[i], arb);
        tiempo = tiempos_bus(buscar, n, k, arb);
        printf("\t %8d\t\t %15.4f\t\t %14.12f\t\t %14.12f\t\t %14.12f\n",
               n, tiempo, tiempo / pow(n, 1.1), tiempo / pow(n, 1.25),
               tiempo / pow(n, 1.3));
        arb = eliminararbol(arb);
    }
    free(v);
}

int main()
{
    inicializar_semilla();
    print_test();
    print_tabla();
    return 0;
}