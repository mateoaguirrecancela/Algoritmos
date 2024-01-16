#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define MAX 32000
#define UMBRAL 1


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
    if (promedio){
        printf("(*)\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
    else{
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / sub, t / cota, t / sobre);
    }
}

double logaritmo(double cota, int n){
    if(cota<0){
        return (n*log(n));
    }else{
        return (pow(n,cota));
    }
}

void tiemposEj(void (*algoritmo) (int*,int), void (*inicializacion) (int*,int), double sub, double cota, double sobre){
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

        tabla(n,t, pow(n,sub), logaritmo(cota, n), pow(n,sobre), promedio);
        n = n * 2;
    }
}


//Algoritmo de Ordenacion por Quicksort
void Fusion(int T[], int Izda, int Dcha, int Centro) {
    int i = Izda;
    int j = Centro + 1;
    int k = Izda;
    int Aux[Dcha+1]; // Vector auxiliar

    // Fusiona los subvectores ordenados T[Izda..Centro] y T[Centro+1..Dcha]
    while (i <= Centro && j <= Dcha) {
        if (T[i] <= T[j]) {
            Aux[k] = T[i];
            i++;
        } else {
            Aux[k] = T[j];
            j++;
        }
        k++;
    }

    // Copia los elementos restantes del subvector sin recorrer
    while (i <= Centro) {
        Aux[k] = T[i];
        i++;
        k++;
    }
    while (j <= Dcha) {
        Aux[k] = T[j];
        j++;
        k++;
    }

    // Copia los elementos de Aux a T
    for (k = Izda; k <= Dcha; k++) {
        T[k] = Aux[k];
    }
}

void OrdenacionPorFusionRecursivo(int T[], int Izda, int Dcha) {
    if (Izda + 1 < Dcha) {
        int Centro = (Izda + Dcha) / 2;
        OrdenacionPorFusionRecursivo(T, Izda, Centro);
        OrdenacionPorFusionRecursivo(T, Centro + 1, Dcha);
        Fusion(T, Izda, Centro, Dcha);
    }
}

void OrdenacionPorInsercion(int T[], int n) {
    int i, j, temp;

    for (i = 1; i < n; i++) {
        temp = T[i];
        j = i - 1;

        while (j >= 0 && T[j] > temp) {
            T[j + 1] = T[j];
            j--;
        }

        T[j + 1] = temp;
    }
}

void OrdenacionPorFusion(int T[], int n) {
    OrdenacionPorFusionRecursivo(T, 0, n - 1);
    OrdenacionPorInsercion(T, n);   //Se aplica Ordenación por Inserción al final
}


//Test 1
void test1(){
    int n = 17;
    int v[n];

    printf("TEST 1\n");
    printf("Inicializacion Aleatoria\n");

    aleatorio(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion por Fusion\n");
    OrdenacionPorFusion(v, n);
    imprimir_vector(v, n);
}

//Test 2
void test2(){
    int n = 20, v[n];

    printf("\n\nTEST 2\n");
    printf("Inicializacion Descente\n");
    descendente(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion por Fusion\n");
    OrdenacionPorFusion(v, n);
    imprimir_vector(v, n);
}

//Test 3
void test3(){
    int n = 20, v[n];

    printf("\n\nTEST 2\n");
    printf("Inicializacion Ascendente\n");
    ascendente(v, n);
    imprimir_vector(v, n);

    printf("Ordenacion por Fusion\n");
    OrdenacionPorFusion(v, n);
    imprimir_vector(v, n);
}

//Test Tiempos Ejecucion
void test4(){
    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    printf("Ordenacion por Fusion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^0.8\t\t t(n)/n\t     t(n)/n^1.2\n");
    tiemposEj(OrdenacionPorFusion, ascendente, 1, -1, 1.5);
    
    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("Ordenacion por Fusion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    tiemposEj(OrdenacionPorFusion, descendente, 1, -1, 1.5);
    
    printf("\n\nVECTOR DESORDENADO\n");
    printf("Ordenacion por Fusion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    tiemposEj(OrdenacionPorFusion, aleatorio, 1, -1, 1.5);
}


int main(){
    inicializar_semilla();

    test1();
    test2();
    test3();
    test4();

    return 0;
}