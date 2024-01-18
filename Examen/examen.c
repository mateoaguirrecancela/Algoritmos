// Examen de Practicas
// Autor: Mateo Aguirre Cancela    |   mateo.aguirre
// Grupo: 2.2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define MAX 64000


void imprimir_vector(int v[], int n){
    int i;
    printf("[");
    for (i = 0; i < n; i++){
        printf("%3d", v[i]);
    }
    printf(" ]\n");
}

void inicializar_semilla(){
    srand(time(NULL));
    /*se establece la semilla de una nueva serie de enteros pseudo-aleatorios*/
}

void aleatorio(int v[], int n){
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++){
        v[i] = (rand() % m) - n;
    } /* se generan números pseudoaleatorio entre -n y +n */
}

void descendente(int v[], int n) {
    int i;
    for (i=0; i < n; i++){
        v[i] = n-i;
    }
}

void ascendente(int v[], int n) {
    int i;
    for (i=0; i < n; i++){
        v[i] = i;
    }
}

double microsegundos(){ /*obtiene la hora del sistema en microsegundos*/
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tabla(int n,double t,double sub,double cota,double sobre,bool promedio){    
    if (promedio){
        printf("(*)\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
    else{
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
}

void tiemposEj(void (*algoritmo) (int*,int), void (*inicializacion) (int*,int),
                     double sub, double cota, double sobre){
    double inicio, final, t;
    bool promedio=false;
    int i, k = 1000, n=500;
    int v[MAX];

    while (n <= MAX){
        promedio = false;
        inicializacion(v, n);
        
        inicio = microsegundos();
        algoritmo(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; i++){
                inicializacion(v, n);
                algoritmo(v, n);
            }
            final = microsegundos();
            t = final - inicio;
            inicio = microsegundos();
            for (i = 0; i < k; i++){
                inicializacion(v, n);
            }
            final = microsegundos();
            t = (t - (final - inicio)) / k;
        }

        tabla(n,t, pow(n,sub), pow(n,cota), pow(n,sobre), promedio);
        n = n * 2;
    }
}


//Algoritmo de Ordenacion
void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void auxOrd(int v[], int izq, int der) {
    int piv, i, j;

    if (izq < der) {
        piv = v[izq + 1];
        intercambiar(&v[izq], &v[izq + 1]);
        i = izq + 1;
        j = der;

        while (i <= j) {
            while (i <= der && v[i] < piv) {
                i++;
            }

            while (v[j] > piv) {
                j--;
            }

            if (i <= j) {
                intercambiar(&v[i], &v[j]);
                i++;
                j--;
            }
        }

        intercambiar(&v[izq], &v[j]);
        auxOrd(v, izq, j - 1);
        auxOrd(v, j + 1, der);
    }
}

void ordenar (int v[], int n){
    auxOrd(v, 0, n-1);
}


//Test 1
void test1(){
    int n = 17;
    int v[n];

    printf("TEST 1\n");
    printf("Inicializacion Aleatoria\n");

    aleatorio(v, n);
    imprimir_vector(v, n);

    printf("Algoritmo de Ordenacion\n");
    ordenar(v, n);
    imprimir_vector(v, n);
}

//Test 2
void test2(){
    int n = 20, v[n];

    printf("\n\nTEST 2\n");
    printf("Inicializacion Descente\n");
    descendente(v, n);
    imprimir_vector(v, n);

    printf("Algoritmo de Ordenacion\n");
    ordenar(v, n);
    imprimir_vector(v, n);
}

//Test 3
void test3(){
    int n = 20, v[n];

    printf("\n\nTEST 2\n");
    printf("Inicializacion Ascendente\n");
    ascendente(v, n);
    imprimir_vector(v, n);

    printf("Algoritmo de Ordenacion\n");
    ordenar(v, n);
    imprimir_vector(v, n);
}

//Test Tiempos Ejecucion
void test4(){
    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    printf("Algoritmo de Ordenacion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.7\t    t(n)/n^1.99\t     t(n)/n^2.3\n");
    tiemposEj(ordenar, ascendente, 1.7, 1.99, 2.3);
    
    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("Algoritmo de Ordenacion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.7\t    t(n)/n^1.99\t     t(n)/n^2.3\n");
    tiemposEj(ordenar, descendente, 1.7, 1.99, 2.3);
    
    printf("\n\nVECTOR DESORDENADO\n");
    printf("Algoritmo de Ordenacion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^0.8\t     t(n)/n^1.1\t     t(n)/n^1.4\n");
    tiemposEj(ordenar, aleatorio, 0.8, 1.1, 1.4);
}


int main(){
    inicializar_semilla();

    test1();
    test2();
    test3();
    test4();

    return 0;
}