#include <stdio.h>

//Algoritmo 1
int sumaSubMax1(int v[], int n) {
    int sumaMax = 0;
    int estaSuma;

    for (int i = 0; i < n; i++) {
        estaSuma = 0;
        for (int j = i; j < n; j++) {
            estaSuma += v[j];
            if (estaSuma > sumaMax){
                sumaMax = estaSuma;
            }
        }
    }

    return sumaMax;
}

//Algoritmo 2
int sumaSubMax2(int v[], int n) {
    int estaSuma = 0;
    int sumaMax = 0;

    for (int j = 0; j < n; j++) {
        estaSuma += v[j];

        if (estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if (estaSuma < 0){
            estaSuma = 0;
        }
    }

    return sumaMax;
}