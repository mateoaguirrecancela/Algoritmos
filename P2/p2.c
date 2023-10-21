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

double microsegundos(){ /*obtiene la hora del sistema en microsegundos*/
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tabla(int n, double t, bool promedio, int a){
    if(a==1){
        if (promedio){
            printf("(*)\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / (pow(n, 0.8)), t / n, t / (pow(n, 1.2)));
        }else{
            printf("\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / (pow(n, 0.8)), t / n, t / (pow(n, 1.2)));
        }
    }else if(a==2){
        if (promedio){
            printf("(*)\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / (pow(n, 1.8)), t / (pow(n, 2)), t / (pow(n, 2.2)));
        }else{
            printf("\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / (pow(n, 1.8)), t / (pow(n, 2)), t / (pow(n, 2.2)));
        }
    }else if(a==3){
        if (promedio){
            printf("(*)\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / (pow(n, 1)), t / (n*log(n)), t / (pow(n, 1.5)));
        }else{
            printf("\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / (pow(n, 1)), t / (n*log(n)), t / (pow(n, 1.5)));
        }
    }else if(a==4){
        if (promedio){
            printf("(*)\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / n, t / (pow(n, 1.2)), t / (pow(n, 1.4)));
        }else{
            printf("\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
                n, t, t / n, t / (pow(n, 1.2)), t / (pow(n, 1.4)));
        }
    }
}

// Algoritmo de Ordenacion por Insercion
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

// Algoritmo de Ordenacion Shell
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

// Test 1
void test1(){
    int n = 17;
    int i, v[n], w[n];

    printf("TEST 1\n");
    printf("Inicializacion Aleatoria\n");

    aleatorio(v, n);
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

// Test 2
void test2(){
    int n = 10, v[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 
    w[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

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

// Test 3
void test3(){
    int n = 10, v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 
    w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

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

// Test Tiempos Ejecucion
void test_ordo(){
    int i, j, k = 1000, n = 500;
    double inicio, final, t, t1;
    bool promedio = false;

    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");
    printf("Ordenacion por Insercion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^0.8\t\t t(n)/n\t     t(n)/n^1.2\n");
    while (n <= 32000){
        int v[n];
        promedio = false;
        for (i = 0; i < n; i++){
            v[i] = i;
        }

        inicio = microsegundos();
        ord_ins(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; ++i){
                for (j = 0; j < n; j++){
                    v[j] = j;
                }
                ord_ins(v, n);
            }
            final = microsegundos();
            t1 = final - inicio;
            t = t1 / k;
        }
        tabla(n, t, promedio, 1);

        n = n * 2;
    }
}

void test_ords(){
    int i, j, k = 1000, n = 500;
    double inicio, final, t, t1;
    bool promedio = false;

    printf("\nOrdenacion Shell\n");
    printf("\t    n\t\t   t(n)\t\t t(n)/n\t  t(n)/n*log(n)\t     t(n)/n^1.5\n");
    while (n <= 32000){
        int v[n];
        promedio = false;
        for (i = 0; i < n; i++){
            v[i] = i;
        }

        inicio = microsegundos();
        ord_shell(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; ++i){
                for (j = 0; j < n; j++){
                    v[j] = j;
                }
                ord_shell(v, n);
            }
            final = microsegundos();
            t1 = final - inicio;
            t = t1 / k;
        }
        tabla(n, t, promedio, 3);

        n = n * 2;
    }
}

void test_deso(){
    int i, j, s, k = 1000, n = 500;
    double inicio, final, t, t1;
    bool promedio = false;

    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("Ordenacion por Insercion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    while (n <= 32000){
        int v[n];
        promedio = false;
        j = n;
        for (i = 0; i < n; i++)
        {
            v[i] = j;
            j--;
        }
        inicio = microsegundos();
        ord_ins(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; ++i){
                s = n;
                for (j = 0; j < n; j++){
                    v[j] = s;
                    s--;
                }
                ord_ins(v, n);
            }
            final = microsegundos();
            t1 = final - inicio;
            t = t1 / k;
        }
        tabla(n, t, promedio, 2);
        n = n * 2;
    }
}

void test_dess(){
    int i, j, s, k = 1000, n = 500;
    double inicio, final, t, t1;
    bool promedio = false;
    
    printf("\nOrdenacion Shell\n");
    printf("\t    n\t\t   t(n)\t\t t(n)/n\t  t(n)/n*log(n)\t     t(n)/n^1.5\n");
    while (n <= 32000){
        int v[n];
        promedio = false;
        j = n;
        for (i = 0; i < n; i++){
            v[i] = j;
            j--;
        }
        inicio = microsegundos();
        ord_shell(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; ++i){
                s = n;
                for (j = 0; j < n; j++)
                {
                    v[j] = s;
                    s--;
                }
                ord_shell(v, n);
            }
            final = microsegundos();
            t1 = final - inicio;
            t = t1 / k;
        }
        tabla(n, t, promedio, 3);
        n = n * 2;
    }
}

void test_alto(){
    int i, k = 1000, n = 500;
    double inicio, final, t, t1;
    bool promedio = false;

    printf("\n\nVECTOR DESORDENADO\n");
    printf("Ordenacion por Insercion\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^1.8\t       t(n)/n^2\t     t(n)/n^2.2\n");
    while (n <= 32000){
        int v[n];
        promedio = false;
        aleatorio(v, n);

        inicio = microsegundos();
        ord_ins(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; ++i){
                aleatorio(v, n);
                ord_ins(v, n);
            }
            final = microsegundos();
            t1 = final - inicio;
            t = t1 / k;
        }
        tabla(n, t, promedio, 2);

        n = n * 2;
    }
}

void test_alts(){
    int i, k = 1000, n = 500;
    double inicio, final, t, t1;
    bool promedio = false;

    printf("\nOrdenacion Shell\n");
    printf("\t    n\t\t   t(n)\t\t t(n)/n\t     t(n)/n^1.2\t     t(n)/n^1.4\n");
    while (n <= 32000){
        int v[n];
        promedio = false;
        aleatorio(v, n);

        inicio = microsegundos();
        ord_shell(v, n);
        final = microsegundos();
        t = final - inicio;

        if (t < 500){
            promedio = true;
            inicio = microsegundos();
            for (i = 0; i < k; ++i)
            {
                aleatorio(v, n);
                ord_shell(v, n);
            }
            final = microsegundos();
            t1 = final - inicio;
            t = t1 / k;
        }
        tabla(n, t, promedio, 4);

        n = n * 2;
    }
}

int main()
{
    inicializar_semilla();

    test1();
    test2();
    test3();
    test_ordo();
    test_ords();
    test_deso();
    test_dess();
    test_alto();
    test_alts();

    return 0;
}