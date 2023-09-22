#include <stdio.h>

// Algoritmo 1
int sumaSubMax1(int v[], int n)
{
    int sumaMax = 0;
    int estaSuma;

    for (int i = 0; i < n; i++)
    {
        estaSuma = 0;
        for (int j = i; j < n; j++)
        {
            estaSuma += v[j];
            if (estaSuma > sumaMax)
            {
                sumaMax = estaSuma;
            }
        }
    }

    return sumaMax;
}

// Algoritmo 2
int sumaSubMax2(int v[], int n)
{
    int estaSuma = 0;
    int sumaMax = 0;

    for (int j = 0; j < n; j++)
    {
        estaSuma += v[j];

        if (estaSuma > sumaMax)
        {
            sumaMax = estaSuma;
        }
        else if (estaSuma < 0)
        {
            estaSuma = 0;
        }
    }

    return sumaMax;
}

// Test 1
void test1()
{
    int a[5] = {-9, 2, -5, -4, 6};
    int b[5] = {4, 0, 9, 2, 5};
    int c[5] = {-2, -1, -9, -7, -1};
    int d[5] = {9, -2, 1, -7, -8};
    int e[5] = {15, -2, -5, -4, 16};
    int f[5] = {7, -5, 6, 7, -7};

    printf("%d\n", sumaSubMax1(a, 5));
    printf("%d\n", sumaSubMax1(b, 5));
    printf("%d\n", sumaSubMax1(c, 5));
    printf("%d\n", sumaSubMax1(d, 5));
    printf("%d\n", sumaSubMax1(e, 5));
    printf("%d\n", sumaSubMax1(f, 5));
}

// Test 2
void inicializar_semilla()
{
    srand(time(NULL));
    /* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void aleatorio(int v[], int n)
{
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
    {
        v[i] = (rand() % m) - n;
    } /* se generan números pseudoaleatorio entre -n y +n */
}

int main()
{

    test1();

    return 0;
}