// Practica 3 Algoritmos
// Autor 1: Mateo Aguirre Cancela    |   mateo.aguirre
// Autor 2: Martin del Rio Alvarez   |   martin.delrio.alvarez
// Grupo: 2.2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define TAM 256000

struct monticulo{
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;


void intercambiar(int *a, int *b) { //a=b  b=a
    int temp = *a;
    *a = *b;
    *b = temp;
}

void hundir(pmonticulo m, int i) {
    int izq = 2 * i + 1;
    int der = 2 * i + 2;
    int menor = i;

    if (izq <= m->ultimo && m->vector[izq] < m->vector[menor]) {
        menor = izq;
    }

    if (der <= m->ultimo && m->vector[der] < m->vector[menor]) {
        menor = der;
    }

    if (menor != i) {
        intercambiar(&m->vector[i], &m->vector[menor]);
        hundir(m, menor);
    }
}

void crearMonticulo(int v[], int n, pmonticulo m){
    m->ultimo = n - 1;

    for (int i = (n - 1) / 2; i >= 0; i--) {
        hundir(m, i);
    }

    for (int i = 0; i < n; i++) {
        m->vector[i] = v[i];
    }
}

int quitarMenor(pmonticulo m) {
    if (m->ultimo == -1) {
        // Montículo vacío
        return -1;
    }

    int menor = m->vector[0];
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;

    hundir(m, 0);

    return menor;
}

void ordenarPorMonticulos(int v[], int n){
    pmonticulo m;
    int i;
    crearMonticulo(v, n, m);

    for (i = 0; i < n; i++){
        v[i]=quitarMenor(m);
    }
}

void mostrarMonticulo(pmonticulo m){
    int i;
    printf("[");
    for (i = 0; i <= m->ultimo; i++) {
        printf("%3d ", m->vector[i]);
    }
    printf("]\n");
}

void mostrarVector(int v[], int n){
    int i;
    printf("[");
    for(i = 0; i < n; i++){
        printf("%3d ", v[i]);
    }
    printf("]\n");
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
    for (i=n-1; i >=0; i--){
        v[n-1-i] = i;
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

void tabla(int n, double t, float cota, bool promedio){
    if (promedio){
        printf("(*)\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
        n, t, t / (cota-0.2), t / cota, t / (cota+0.2));
    }else{
        printf("\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
        n, t, t / (cota-0.2), t / cota, t / (cota+0.2));
    }
}


//TEST
void testOperaciones(){
    int n=10;
    int v[n];
    aleatorio(v, n);
    //int n = sizeof(v) / sizeof(v[0]);     calcular el numero de elementos del array
    pmonticulo m;
    int menor;

    crearMonticulo(v, n, m);

    printf("Crear Monticulo:\n");
    mostrarMonticulo(m);

    printf("Quitar Menor:\n");
    quitarMenor(m);
    mostrarMonticulo(m);

    ordenarPorMonticulos(v, n);
    printf("Ordenar por Monticulos:\n");
    mostrarVector(v, n);
}

//Orden Ascendente
void testAscendente(){
    int n=500, k=1000, v[32000];
    double inicio, final, t, ta;
    bool promedio=false;
    pmonticulo m;

    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    
    while(n<=32000){
        promedio=false;
        ascendente(v, n);
        
        inicio=microsegundos();
        ordenarPorMonticulos(v, n);
        final=microsegundos();
        t=final-inicio;

        if(t<500){
			promedio = true;
			inicio=microsegundos();
			for(int i=0;i<k;i++){
				ascendente(v, n);
				ordenarPorMonticulos(v,n);
			}
			final=microsegundos();
			t=(final-inicio)/k;
			inicio=microsegundos();
			for(int i=0;i<k;i++){
				ascendente(v, n);
			}
			final=microsegundos();
			t = t - ((final-inicio)/k);
		}

        //tabla(n, t, cota, promedio);

        n=n*2;
    }
}

//Orden Descendente
void testDescendente(){
    int n=500, k=1000, v[32000];
    double inicio, final, t;
    bool promedio=false;

    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    
    while(n<=32000){
        promedio=false;
        descendente(v, n);

        inicio=microsegundos();
        ordenarPorMonticulos(v, n);
        final=microsegundos();
        t=final-inicio;

        if(t<500){
			promedio = true;
			inicio=microsegundos();
			for(int i=0;i<k;i++){
				descendente(v, n);
				ordenarPorMonticulos(v,n);
			}
			final=microsegundos();
			t=(final-inicio)/k;
			inicio=microsegundos();
			for(int i=0;i<k;i++){
				descendente(v, n);
			}
			final=microsegundos();
			t = t - ((final-inicio)/k);
		}

        //tabla(n, t, cota, promedio);

        n=n*2;
    }
}

//Aleatorio
void testAleatorio(){
    int n=500, k=1000, v[32000];
    double inicio, final, t;
    bool promedio=false;

    printf("\n\nVECTOR EN ORDEN ALEATORIO\n");
    
    while(n<=32000){
        promedio=false;
        aleatorio(v, n);

        inicio=microsegundos();
        ordenarPorMonticulos(v, n);
        final=microsegundos();
        t=final-inicio;

        if(t<500){
			promedio = true;
			inicio=microsegundos();
			for(int i=0;i<k;i++){
				aleatorio(v, n);
				ordenarPorMonticulos(v,n);
			}
			final=microsegundos();
			t=(final-inicio)/k;
			inicio=microsegundos();
			for(int i=0;i<k;i++){
				aleatorio(v, n);
			}
			final=microsegundos();
			t = t - ((final-inicio)/k);
		}

        //tabla(n, t, cota, promedio);

        n=n*2;
    }
}



int main(){

    inicializar_semilla();
    testOperaciones();
    testAscendente();
    testDescendente();
    testAleatorio();

    return 0;
}