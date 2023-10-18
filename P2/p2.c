// Practica 2 Algoritmos
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

//Algoritmo de Ordenacion por Insercion
void ord_ins(int v[], int n) {
    int i, j, x;
    for (i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

//Algoritmo de Ordenacion Shell
void ord_shell(int v[], int n) {
    int i, j, tmp, seguir, incremento = n;
    do {
        incremento = incremento / 2;
        for (i = incremento; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = 1;
            while (j - incremento >= 0 && seguir) {
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j -= incremento;
                } else {
                    seguir = 0;
                }
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
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

void imprimir_vector(int v[], int n){
    int i;
    printf("[");
    for (i = 0; i < n; i++){
        printf("%3d", v[i]);
    }
    printf(" ] \n");
}

//Test 1
void test1(){
    int n = 17;
    int i, v[n], w[n];

    printf("TEST 1\n");
    printf("Inicializacion Aleatoria\n");

    aleatorio(v, n);
    for (i = 0; i < n; i++) {
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
    int n=10, v[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, w[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    printf("\n\nTEST 2\n");
    printf("Inicializacion Descente\n");
    imprimir_vector(v, n);

    printf("Ordenacion por Insercion\n");
    ord_ins(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion Shell\n");
    ord_shell(w, n);
    imprimir_vector(w, n);
}

//Test 3
void test3(){
        int n=10, v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("\n\nTEST 2\n");
    printf("Inicializacion Ascendente\n");
    imprimir_vector(v, n);

    printf("Ordenacion por Insercion\n");
    ord_ins(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion Shell\n");
    ord_shell(w, n);
    imprimir_vector(w, n);
}

//Test Tiempos Ejecucion
void test_ord(){
    int i, n=500;
    double inicioo, inicios, finalo, finals, to, ts;
    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    printf("Ordenacion por Insercion\n");
    while (n <= 32000){
        int  v[n];
        for (i = 0; i < n; i++){
            v[i]=i;
        }
        inicioo=microsegundos();
        ord_ins(v, n);
        finalo=microsegundos();
        to=finalo-inicioo;

        printf("\t%d\t\t%f\t%f\t%f\t%f\n",
        n, to, to / (pow(n, 0.8)), to / n, to / (pow(n, 1.2)));
    
        n = n * 2;
    }

    n=500;
    printf("\nOrdenacion Shell\n");
    while (n <= 32000){
        int  v[n];
        for (i = 0; i < n; i++){
            v[i]=i;
        }
        inicios=microsegundos();
        ord_shell(v, n);
        finals=microsegundos();
        ts=finals-inicios;

        printf("\t%d\t\t%f\t%f\t%f\t%f\n",
        n, ts, ts / (pow(n, 0.8)), ts / n, ts / (pow(n, 1.2)));

        n = n * 2;
    }
}

void test_des(){
    int i,j,n=500;
    double inicioo, inicios, finalo, finals, to, ts;

    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("Ordenacion por Insercion\n");
    while (n <= 32000){
        int  v[n];
        j=n;
        for (i = 0; i < n; i++){
            v[i]=j;
            j--;
        }
        inicioo=microsegundos();
        ord_ins(v, n);
        finalo=microsegundos();
        to=finalo-inicioo;

        printf("\t%d\t\t%f\t%f\t%f\t%f\n",
        n, to, to / (pow(n, 0.8)), to / n, to / (pow(n, 1.2)));
    
        n = n * 2;
    }

    n=500;
    printf("\nOrdenacion Shell\n");
    while (n <= 32000){
        int  v[n];
        j=n;
        for (i = 0; i < n; i++){
            v[i]=j;
            j--;
        }
        inicios=microsegundos();
        ord_shell(v, n);
        finals=microsegundos();
        ts=finals-inicios;

        printf("\t%d\t\t%f\t%f\t%f\t%f\n",
        n, ts, ts / (pow(n, 0.8)), ts / n, ts / (pow(n, 1.2)));

        n = n * 2;
    }
}

void test_alt(){
    int n=500;
    double inicioo, inicios, finalo, finals, to, ts;
    
    printf("\n\nVECTOR DESORDENADO\n");
    printf("Ordenacion por Insercion\n");
    while (n <= 32000){
        int  v[n];

        aleatorio(v, n);
        
        inicioo=microsegundos();
        ord_ins(v, n);
        finalo=microsegundos();
        to=finalo-inicioo;

        printf("\t%d\t\t%f\t%f\t%f\t%f\n",
        n, to, to / (pow(n, 0.8)), to / n, to / (pow(n, 1.2)));
    
        n = n * 2;
    }

    n=500;
    printf("\nOrdenacion Shell\n");
    while (n <= 32000){
        int  v[n];

        aleatorio(v, n);
                
        inicios=microsegundos();
        ord_shell(v, n);
        finals=microsegundos();
        ts=finals-inicios;

        printf("\t%d\t\t%f\t%f\t%f\t%f\n",
        n, ts, ts / (pow(n, 0.8)), ts / n, ts / (pow(n, 1.2)));

        n = n * 2;
    }
}

int main(){
    inicializar_semilla();

    test1();
    test2();
    test3();
    test_ord();
    test_des();
    test_alt();

    return 0;
}