// Practica 1 Algoritmos
// Autor 1: Mateo Aguirre Cancela    |   mateo.aguirre
// Autor 2: Martin del Rio Alvarez   |   martin.delrio.alvarez
// Grupo: 2.2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

#define MAX 32000


void imprimirVector(int n, int v[n]){
    int i;
    printf("[");
    for (i = 0; i < n; i++){
        printf("%3d", v[i]);
    }
    printf(" ]");
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

void tiemposEj(int (*algoritmo) (int*,int), void (*inicializacion) (int*,int), double sub, double cota, double sobre){
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

        tabla(n,t, pow(n, sub), pow(n, cota), pow(n, sobre), promedio);
        n = n * 2;
    }
}


//Algoritmo 1
int sumaSubMax1(int v[], int n){
    int sumaMax = 0;
    int estaSuma;
    int i, j;

    for (i = 0; i < n; i++){
        estaSuma = 0;
        for (j = i; j < n; j++){
            estaSuma += v[j];
            if (estaSuma > sumaMax){
                sumaMax = estaSuma;
            }
        }
    }

    return sumaMax;
}

//Algoritmo 2
int sumaSubMax2(int v[], int n){
    int estaSuma = 0;
    int sumaMax = 0;
    int j;

    for (j = 0; j < n; j++){
        estaSuma += v[j];

        if (estaSuma > sumaMax){
            sumaMax = estaSuma;
        }
        else if (estaSuma < 0){
            estaSuma = 0;
        }
    }

    return sumaMax;
}

//Test 1
void test1(){
    int a[5] = {-9, 2, -5, -4, 6};
    int b[5] = {4, 0, 9, 2, 5};
    int c[5] = {-2, -1, -9, -7, -1};
    int d[5] = {9, -2, 1, -7, -8};
    int e[5] = {15, -2, -5, -4, 16};
    int f[5] = {7, -5, 6, 7, -7};

    printf("TEST 1\n");
    printf("Secuencia\t\tsumaSubMax1\tsumaSubMax2\n");
    imprimirVector(5, a);
    printf("\t%d\t\t", sumaSubMax1(a, 5));
    printf("%d\n", sumaSubMax2(a, 5));
    imprimirVector(5, b);
    printf("\t%d\t\t", sumaSubMax1(b, 5));
    printf("%d\n", sumaSubMax2(b, 5));
    imprimirVector(5, c);
    printf("\t%d\t\t", sumaSubMax1(c, 5));
    printf("%d\n", sumaSubMax2(c, 5));
    imprimirVector(5, d);
    printf("\t%d\t\t", sumaSubMax1(d, 5));
    printf("%d\n", sumaSubMax2(d, 5));
    imprimirVector(5, e);
    printf("\t%d\t\t", sumaSubMax1(e, 5));
    printf("%d\n", sumaSubMax2(e, 5));
    imprimirVector(5, f);
    printf("\t%d\t\t", sumaSubMax1(f, 5));
    printf("%d\n", sumaSubMax2(f, 5));
}

//Test 2
void test2(){
    int i, n = 9;
    int v[n];
    printf("\n\nTEST 2\n");
    printf("Secuencia\t\t\t\tsumaSubMax1\tsumaSubMax2\n");

    for (i=0; i<10; i++){
        aleatorio(v, n);
        imprimirVector(n,v);
        printf("\t\t%d\t\t", sumaSubMax1(v, n));
        printf("%d\n", sumaSubMax2(v, n));
    }    
}

void test3(){   
    printf("\n\nSumaSubMax 1\n");
    printf("\t     n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    tiemposEj(sumaSubMax1, aleatorio, 1.8, 2, 2.2);

    printf("\n\nSumaSubMax 2\n");
    printf("\t     n\t\t   t(n)\t     t(n)/n^0.8\t\t t(n)/n\t     t(n)/n^1.2\n");
    tiemposEj(sumaSubMax2, aleatorio, 0.8, 1, 1.2);
}

// MAIN
int main(){
    inicializar_semilla();

    test1();
    test2();
    test3();

    return 0;
}