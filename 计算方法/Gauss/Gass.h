#include<stdlib.h>
#include <math.h>
#define MAXNUM 100
void init(double a[][MAXNUM],int n);
void Gauss (double a[][MAXNUM],int n);
void SelectColE(double a[][MAXNUM],int n);
void swapRow(double a[][MAXNUM],int m,int maxRowE,int n);
void printM(double a[][MAXNUM], int n);