#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rows;
  int columns;
  double **data;
} Matrix;

Matrix* CreateNewMatrix(int n, int m);

Matrix* ReadMatrix(char *file_name);

void WriteMatrix(FILE* file_pointer, Matrix* matrix);

Matrix* Transpose(Matrix* matrix);

Matrix* Covariance(Matrix* matrix);

Matrix* Product(Matrix* m1, Matrix* m2);

Matrix* Mean(Matrix* matrix);

void DestroyMatrix(Matrix* matrix);

#endif