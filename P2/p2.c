// Practica 2 Algoritmos
// Autor 1: Mateo Aguirre Cancela    |   mateo.aguirre
// Autor 2: Martin del Rio Alvarez   |   martin.delrio.alvarez
// Grupo: 2.2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define MAX 32000


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

void tabla(int n, double t, double sub, double cota, double sobre, bool promedio){
    if(cota<0){ cota=n*log(n); }
    
    if (promedio){
        printf("(*)\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
    else{
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
}

void tiemposEj(void (*algoritmo) (int*,int), void (*inicializacion) (int*,int), double sub, double cota, double sobre){
    double inicio, final, t;
    bool promedio=false;
    int i, k = 1000, n=500;
    int v[MAX];

    while (n <= MAX){
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


//Algoritmo de Ordenacion por Insercion
void ord_ins(int v[], int n){
    int i, j, x;
    for (i = 1; i < n; i++){
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x){
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

//Algoritmo de Ordenacion Shell
void ord_shell(int v[], int n){
    int i, j, tmp, seguir, incremento = n;
    do{
        incremento = incremento / 2;
        for (i = incremento; i < n; i++){
            tmp = v[i];
            j = i;
            seguir = 1;
            while (j - incremento >= 0 && seguir){
                if (tmp < v[j - incremento]){
                    v[j] = v[j - incremento];
                    j -= incremento;
                }
                else{
                    seguir = 0;
                }
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
}


//Test 1
void test1(){
    int n = 17;
    int i, v[n], w[n];

    printf("TEST 1\n");
    printf("Inicializacion Aleatoria\n");

    aleatorio(v, n);
    //Copiar vector
    for (i = 0; i < n; i++){
        w[i] = v[i];
    }
    imprimir_vector(v, n);

    printf("Ordenacion por Insercion\n");
    ord_ins(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion Shell\n");
    ord_shell(w, n);
    imprimir_vector(w, n);
}

//Test 2
void test2(){
    int n = 20, v[n];

    printf("\n\nTEST 2\n");
    printf("Inicializacion Descente\n");
    descendente(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion por Insercion\n");
    ord_ins(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion Shell\n");
    descendente(v, n);
    ord_shell(v, n);
    imprimir_vector(v, n);
}

//Test 3
void test3(){
    int n = 20, v[n];

    printf("\n\nTEST 2\n");
    printf("Inicializacion Ascendente\n");
    ascendente(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion por Insercion\n");
    ord_ins(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion Shell\n");
    ascendente(v, n);
    ord_shell(v, n);
    imprimir_vector(v, n);
}

//Test Tiempos Ejecucion
void test4(){
    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    printf("Ordenacion por Insercion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^0.8\t\t t(n)/n\t     t(n)/n^1.2\n");
    tiemposEj(ord_ins, ascendente, 0.8, 1, 1.2);
    
    printf("\nOrdenacion Shell\n");
    printf("\t    n\t\t   t(n)\t\t t(n)/n\t  t(n)/n*log(n)\t     t(n)/n^1.5\n");
    tiemposEj(ord_shell, ascendente, 1, -1, 1.5);

    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("Ordenacion por Insercion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    tiemposEj(ord_ins, descendente, 1.8, 2, 2.2);
    
    printf("\nOrdenacion Shell\n");
    printf("\t    n\t\t   t(n)\t\t t(n)/n\t  t(n)/n*log(n)\t     t(n)/n^1.5\n");
    tiemposEj(ord_shell, descendente, 1, -1, 1.5);

    printf("\n\nVECTOR DESORDENADO\n");
    printf("Ordenacion por Insercion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    tiemposEj(ord_ins, aleatorio, 1.8, 2, 2.2);

    printf("\nOrdenacion Shell\n");
    printf("\t    n\t\t   t(n)\t\t t(n)/n\t     t(n)/n^1.2\t     t(n)/n^1.4\n");
    tiemposEj(ord_shell, aleatorio, 1, 1.2, 1.4);
}


int main()
{
    inicializar_semilla();

    test1();
    test2();
    test3();
    test4();

    return 0;
}