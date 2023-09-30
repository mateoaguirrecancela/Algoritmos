// Practica 1 Algoritmos
// Autor 1: Mateo Aguirre Cancela    |   mateo.aguirre
// Autor 2: Martin del Rio Alvarez   |   martin.delrio.alvarez
// Grupo: 2.2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

double microsegundos(){ /*obtiene la hora del sistema en microsegundos*/
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Algoritmo 1
int sumaSubMax1(int v[], int n){
    int sumaMax = 0;
    int estaSuma;

    for (int i = 0; i < n; i++){
        estaSuma = 0;
        for (int j = i; j < n; j++){
            estaSuma += v[j];
            if (estaSuma > sumaMax){
                sumaMax = estaSuma;
            }
        }
    }

    return sumaMax;
}

// Algoritmo 2
int sumaSubMax2(int v[], int n){
    int estaSuma = 0;
    int sumaMax = 0;

    for (int j = 0; j < n; j++){
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

// Test 1
void test1(){
    int a[5] = {-9, 2, -5, -4, 6};
    int b[5] = {4, 0, 9, 2, 5};
    int c[5] = {-2, -1, -9, -7, -1};
    int d[5] = {9, -2, 1, -7, -8};
    int e[5] = {15, -2, -5, -4, 16};
    int f[5] = {7, -5, 6, 7, -7};

    printf("TEST 1\n");
    printf("sumaSubMax1\tsumaSubMax2\n");
    printf("%d\t\t", sumaSubMax1(a, 5));
    printf("%d\n", sumaSubMax2(a, 5));
    printf("%d\t\t", sumaSubMax1(b, 5));
    printf("%d\n", sumaSubMax2(b, 5));
    printf("%d\t\t", sumaSubMax1(c, 5));
    printf("%d\n", sumaSubMax2(c, 5));
    printf("%d\t\t", sumaSubMax1(d, 5));
    printf("%d\n", sumaSubMax2(d, 5));
    printf("%d\t\t", sumaSubMax1(e, 5));
    printf("%d\n", sumaSubMax2(e, 5));
    printf("%d\t\t", sumaSubMax1(f, 5));
    printf("%d\n", sumaSubMax2(f, 5));
}

// Test 2
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

void test2(){
    int n = 9;
    int v[n];
    printf("\n\nTEST 2\n");
    printf("\t\t\t\t\tsumaSubMax1\tsumaSubMax2\n");
    for (int i = 0; i <= n; i++){
        aleatorio(v, n);
        printf("[");
        for (int j = 0; j < n; j++){
            printf("%3d", v[j]);
        }
        printf(" ] \t\t");
        printf("%d\t\t", sumaSubMax1(v, n));
        printf("%d\n", sumaSubMax2(v, n));
    }
}

void test3(){
    int a = 9, n = 500;
    double inicio, final, t;
    int v[a];
    for (int i = 0; i <= a; i++){
        aleatorio(v, a);
    }
    printf("\n\nSumaSubMax 1\n");
    printf("\tn\t\tt(n)\t\tt(n)/n^1.8\tt(n)/n^2\tt(n)/n^2.2\n");
    while (n <= 32000){
        inicio = microsegundos();
        for (int j = 0; j < n; j++){
            sumaSubMax1(v, a);
        }
        final = microsegundos();
        t = final - inicio;
        printf("\t%d\t\t%f\t%.10f\t%.10f\t%.10f\n",
               n, t, t / (pow(n, 1.8)), t / (pow(n, 2)), t / (pow(n, 2.2)));
        n = n * 2;
    }
    n = 500;
    printf("\n\nSumaSubMax 2\n");
    printf("\tn\t\tt(n)\t\tt(n)/n^1.8\tt(n)/n^2\tt(n)/n^2.2\n");
    while (n <= 32000){
        inicio = microsegundos();
        for (int j = 0; j < n; j++){
            sumaSubMax2(v, a);
        }
        final = microsegundos();
        t = final - inicio;
        printf("\t%d\t\t%f\t%.10f\t%.10f\t%.10f\n",
               n, t, t / (pow(n, 1.8)), t / (pow(n, 2)), t / (pow(n, 2.2)));
        n = n * 2;
    }
}

// MAIN
int main(){
    inicializar_semilla();

    test1();
    test2();
    test3();

    return 0;
}