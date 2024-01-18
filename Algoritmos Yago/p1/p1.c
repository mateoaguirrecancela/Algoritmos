#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

int fib1(int x) {
  if (x < 2) {
    return (x);
  } else {
    return ((fib1(x - 1) + fib1(x - 2)));
  }
}

int fib2(int x) {
  int i = 1;
  int j = 0;
  int k;
  for (k = 1; k <= x; k++) {
    j = i + j;
    i = j - i;
  }
  return (j);
}

int fib3(int x) {
  int i = 1;
  int j = 0;
  int k = 0;
  int h = 1;
  int t = 0;

  while (x > 0) {
    if (x % 2 == 1) {
      t = j * h;
      j = i * h + j * k + t;
      i = i * k + t;
    }
    t = h * h;
    h = 2 * k * h + t;
    k = k * k + t;
    x = x / 2;
  }
  return j;
}

double microsegundos() {
  struct timeval t;

  if (gettimeofday( & t, NULL) < 0) {
    return 0.0;
  }
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

void test1() {
  bool promedio = false;
  int k = 1000;
  double t1, t2, t, prima, x, y, z;
  int n, i;
  printf("\t\t\t\t\t\t\tCota subestimada: \t Cota exacta:\t    "
    "Cota sobreestimada:\n");
  printf("Alg. Fib1      n\t\t        t(n)\t\t  t(n)/1,1^n\t      "
    "t(n)/((1+sqrt(5))/2)^n\t   t(n)/2^n\n\n");

  for (n = 2; n <= 32; n = n * 2) {
    t1 = microsegundos();
    fib1(n);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500) {
      promedio = true;
      t1 = microsegundos();
      for (i = 0; i < k; i++) {
        fib1(n);
      }
      t2 = microsegundos();
      prima = t2 - t1;
      t = prima / k;
    } else {
      promedio = false;
    }
    x = t / (pow(1.1, n));
    y = t / (pow(((1 + sqrt(5)) / 2), n));
    z = t / (pow(2, n));
    if (promedio) {
      printf("(*)");
      printf("\t%8d\t \t%14.5f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n", n,t,x,y,z);
    } else {
      printf("\t%8d\t \t%14.5f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n", n,t,x,y,z);
    }
  }
}

void test2() {
  bool promedio = false;
  int k = 1000;
  double t1, t2, t, prima, x, y, z;
  int n, i;
  printf("\n");
  printf("\t\t\t\t\t\t\tCota subestimada: \t Cota exacta:\t    "
    "Cota sobreestimada:\n");
  printf("Alg. Fib2      n\t\t        t(n)\t\t  t(n)/n^0.8\t\t   "
    "t(n)/n\t\tt(n)/(n*log(n))\n\n");

  for (n = 1000; n <= 10000000; n = n * 10) {
    t1 = microsegundos();
    fib2(n);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500) {
      promedio = true;
      t1 = microsegundos();
      for (i = 0; i < k; i++) {
        fib2(n);
      }
      t2 = microsegundos();
      prima = t2 - t1;
      t = prima / k;
    } else {
      promedio = false;
    }
    x = t / (pow(n, 0.8));
    y = t / n;
    z = t / (n * log(n));
    if (promedio) {
      printf("(*)");
      printf("\t%8d\t \t%14.5f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n", n,t,x,y,z);
    } else {
      printf("\t%8d\t \t%14.5f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n", n,t,x,y,z);
    }
  }
}

void test3() {
  bool promedio = false;
  int k = 1000;
  double t1, t2, t, prima, x, y, z;
  int n, i;
  printf("\n");
  printf("\t\t\t\t\t\t\tCota subestimada: \t Cota exacta:\t    "
    "Cota sobreestimada:\n");
  printf("Alg. Fib3      n\t\t        t(n)\t\tt(n)/sqrt(log(n))\t"
    "t(n)/log(n))\t\t    t(n)/n^0.5\n\n");

  for (n = 1000; n <= 10000000; n = n * 10) {
    t1 = microsegundos();
    fib3(n);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500) {
      promedio = true;
      t1 = microsegundos();
      for (i = 0; i < k; i++) {
        fib3(n);
      }
      t2 = microsegundos();
      prima = t2 - t1;
      t = prima / k;
    } else {
      promedio = false;
    }
    x = t / (sqrt(log(n)));
    y = t / (log(n));
    z = t / (pow(n, 0.5));
    if (promedio) {
      printf("(*)");
      printf("\t%8d\t \t%14.5f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n", n,t,x,y,z);
    } else {
      printf("\t%8d\t \t%14.5f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n", n,t,x,y,z);
    }
  }
}

int main() {
  test1();
  test2();
  test3();
  return 0;
}