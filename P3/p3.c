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
    int i;
    for(i = 0; i < n; i++){
        m->vector[i]=v[i];
    }
    m->ultimo = n-1;
    for(i = (m->ultimo)/2; i >= 0; i--){
        hundir(m,i);
    }
}

int quitarMenor(pmonticulo m) {
    if (m->ultimo < 0) {    //vacio
        return -1;
    }

    int menor = m->vector[0];
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;

    hundir(m, 0);

    return menor;
}

void ordenarPorMonticulos(int v[], int n){
    pmonticulo m = malloc(sizeof(struct monticulo));    //inicializar monticulo
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
    }else{
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
        n, t, t / sub, t / cota, t / sobre);
    }
}

//COMPLEJIDAD
void comprobarComplejidad() {
    int i, n=1000, k=1000, v[256000];
    double inicio, final, t;
    bool promedio=false;
    pmonticulo m = NULL;                    //inicializar el puntero a NULL
    m = malloc(sizeof(struct monticulo));   //asignar memoria


    printf("\nTabla para demostrar la complejidad de crear monticulo O(n):\n");
    printf("\t     n\t\t   t(n)\t     t(n)/n^0.9\t\t t(n)/n\t     t(n)/n^1.2\n");
    while (n <= 256000) {
        promedio=false;
        ascendente(v,n);

        inicio = microsegundos();
        crearMonticulo(v,n,m);
        final = microsegundos();
        t = final - inicio;

        if(t < 500){
            promedio=true;
            inicio = microsegundos();
            for (i = 0; i < k; i++) {
                crearMonticulo(v,n,m);
            }
            final = microsegundos();
            t = (final - inicio)/k;
        }

        tabla(n, t, pow(n,0.9), n, (pow(n,1.2)), promedio);

        n=n*2;
    }
}

//TEST
void testOperaciones(){
    int i, n=10;
    int v[n];
    aleatorio(v, n);
    pmonticulo m = NULL;                    //inicializar el puntero a NULL
    m = malloc(sizeof(struct monticulo));   //asignar memoria

    crearMonticulo(v, n, m);

    printf("Crear Monticulo:\n");
    mostrarMonticulo(m);

    printf("Quitar Menor:\n");
    for(i=0;i<n;i++){
        quitarMenor(m);
        mostrarMonticulo(m);
    }

    ordenarPorMonticulos(v, n);
    printf("Ordenar por Monticulos:\n");
    mostrarVector(v, n);
}

//Orden Ascendente
void testAscendente(){
    int i, n=500, k=1000, v[128000];
    double inicio, final, t;
    bool promedio=false;

    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    printf("\t     n\t\t   t(n)\t    t(n)/n^0.92   t(n)/n*log(n)\t     t(n)/n^1.4\n");

    while(n<=128000){
        promedio=false;
        ascendente(v, n);
        
        inicio=microsegundos();
        ordenarPorMonticulos(v, n);
        final=microsegundos();
        t=final-inicio;

        if(t<500){
			promedio = true;
			inicio=microsegundos();
			for(i=0;i<k;i++){
				ascendente(v, n);
				ordenarPorMonticulos(v,n);
			}
			final=microsegundos();
			t=final-inicio;
			inicio=microsegundos();
			for(i=0;i<k;i++){
				ascendente(v, n);
			}
			final=microsegundos();
			t = (t - (final-inicio))/k;
		}

        tabla(n, t, pow(n,0.92), n*log(n), pow(n,1.4), promedio);

        n=n*2;
    }
}

//Orden Descendente
void testDescendente(){
    int i, n=500, k=1000, v[128000];
    double inicio, final, t;
    bool promedio=false;

    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("\t     n\t\t   t(n)\t    t(n)/n^0.92   t(n)/n*log(n)\t     t(n)/n^1.4\n");
    
    while(n<=128000){
        promedio=false;
        descendente(v, n);

        inicio=microsegundos();
        ordenarPorMonticulos(v, n);
        final=microsegundos();
        t=final-inicio;

        if(t<500){
			promedio = true;
			inicio=microsegundos();
			for(i=0;i<k;i++){
				descendente(v, n);
				ordenarPorMonticulos(v,n);
			}
			final=microsegundos();
			t=final-inicio;
			inicio=microsegundos();
			for(i=0;i<k;i++){
				descendente(v, n);
			}
			final=microsegundos();
			t = (t - (final-inicio))/k;
		}

        tabla(n, t, pow(n,0.92), n*log(n), pow(n,1.4), promedio);

        n=n*2;
    }
}

//Aleatorio
void testAleatorio(){
    int i, n=500, k=1000, v[128000];
    double inicio, final, t;
    bool promedio=false;

    printf("\n\nVECTOR EN ORDEN ALEATORIO\n");
    printf("\t     n\t\t   t(n)\t    t(n)/n^0.92   t(n)/n*log(n)\t     t(n)/n^1.4\n");
    
    while(n<=128000){
        promedio=false;
        aleatorio(v, n);

        inicio=microsegundos();
        ordenarPorMonticulos(v, n);
        final=microsegundos();
        t=final-inicio;

        if(t<500){
			promedio = true;
			inicio=microsegundos();
			for(i=0;i<k;i++){
				aleatorio(v, n);
				ordenarPorMonticulos(v,n);
			}
			final=microsegundos();
			t=final-inicio;
			inicio=microsegundos();
			for(i=0;i<k;i++){
				aleatorio(v, n);
			}
			final=microsegundos();
			t = (t - (final-inicio))/k;
		}

        tabla(n, t, pow(n,0.92), n*log(n), pow(n,1.4), promedio);

        n=n*2;
    }
}



int main(){

    inicializar_semilla();
    testOperaciones();
    comprobarComplejidad();
    testAscendente();
    testDescendente();
    testAleatorio();
    
    return 0;
}