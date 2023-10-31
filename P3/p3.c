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

void ordenarPorMonticulos(int v[], int n){
    pmonticulo m;
    int i;
    crearMonticulo(v, n, m);

    for (i = 0; i < n; i++){
        v[i]=quitarMenor(m);
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


double microsegundos(){ /*obtiene la hora del sistema en microsegundos*/
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

//TEST
void testOperaciones(){
    int datos[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(datos) / sizeof(datos[0]);    //calcular el numero de elementos del array
    pmonticulo m;
    int i, menor;

    crearMonticulo(datos, n, m);

    printf("Crear Monticulo:\n");
    printf("[");
    for (i = 0; i <= m->ultimo; i++) {
        printf("%3d ", m->vector[i]);
    }
    printf("]");
    printf("\n");

    printf("Quit Menor:\n");
    printf("[");
    while (m->ultimo >= 0) {
        menor = quitarMenor(m);
        printf("%3d ", menor);
    }
    printf("]");
    printf("\n");

    return 0;
}


//Orden Ascendente



//Orden Descendente



//Aleatorio