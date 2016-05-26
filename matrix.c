#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix* CreateNewMatrix(int n, int m) {
  Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
  matrix->rows = n;
  matrix->columns = m;
  matrix->data = (double**)malloc(sizeof(double)*n);
  for (int i = 0; i < n; i++){
    matrix->data[i] = (double*)malloc(sizeof(double)*m);
  }
  return matrix;
}

Matrix* ReadMatrix(char *file_name) {
  double x;
  char flag;
  int r, c;
  FILE *fin;
  fin = fopen(file_name, "r");
  fscanf(fin, "%d", &r);
  fseek(fin, 1,SEEK_CUR);
  fscanf(fin, "%d", &c);
  fseek(fin, 1,SEEK_CUR);
  Matrix* matrix = CreateNewMatrix(r, c);
  for (int n = 0; n < matrix->rows; n++) {
    flag = 0;
    for (int m = 0; m < matrix->columns; m++) {
      fscanf(fin, "%lf", &x);
      fseek(fin, 1, SEEK_CUR);
      matrix->data[n][m] = x;
    }
    while (flag != '\n')
      fscanf(fin, "%c", &flag);
  }
  fclose(fin);
  printf("Matrix read from %s\n", file_name);
  return matrix;
}

void WriteMatrix(FILE* file_pointer, Matrix* matrix) {
  for (int n = 0; n < matrix->rows; n++) {
    for (int m = 0; m < matrix->columns; m++) {
      fprintf(file_pointer, "%lf ",matrix->data[n][m]);
      
    }
    fprintf(file_pointer, "\n");
  }
  fclose(stdout);
}

Matrix* Transpose(Matrix* matrix) {
  Matrix* transpose_matrix;
  transpose_matrix = CreateNewMatrix(matrix->columns, matrix->rows);
  for (int n = 0; n < transpose_matrix->rows; n++) {
    for (int m = 0; m < transpose_matrix->columns; m++) {
      transpose_matrix->data[n][m] = matrix->data[m][n];
    }
  }
  return transpose_matrix;
}

Matrix* Product(Matrix* m1, Matrix* m2) {
  if (m1->columns != m2->rows) {
    printf("Not Possible\n");
    return NULL;
  }
  Matrix* res = CreateNewMatrix(m1->rows, m2->columns);
  double element;
  for (int n = 0; n < res->rows; n++) {
    for (int m = 0; m < res->columns; m++) {
      element = 0;
      for(int i = 0; i < m2->rows; i++) {
        element += m1->data[n][i]*m2->data[i][m];
      }
      res->data[n][m] = element;
    }
  }
  return res;
}

Matrix* Mean(Matrix* matrix) {
  double* array_avg = (double*)malloc(sizeof(double)*matrix->columns);
  double sum = 0;
  Matrix* mean_matrix = CreateNewMatrix(matrix->rows, matrix->columns);
  for (int n = 0; n < matrix->columns; n++) {
    sum = 0;
    for (int m = 0; m < matrix->rows; m++) {
      sum += matrix->data[m][n];
    }
    array_avg[n] = sum/mean_matrix->rows;
  }
  for (int m = 0; m < mean_matrix->columns; m++) {
    for (int n = 0; n < mean_matrix->rows; n++) {
      mean_matrix->data[n][m] = matrix->data[n][m] - array_avg[m];
    }
  }
  return mean_matrix;
}

Matrix* Covariance(Matrix* matrix) {
  Matrix* covar_matrix = CreateNewMatrix(matrix->columns, matrix->columns);
  Matrix* mean_matrix = Mean(matrix);
  Matrix* transpose_matrix = Transpose(mean_matrix);
  Matrix* product = Product(transpose_matrix, mean_matrix);

  for (int n = 0; n < covar_matrix->rows; n++) {
    for (int m = 0; m < covar_matrix->columns; m++) {
      covar_matrix->data[n][m]= product->data[n][m]/(matrix->rows -1);
    }
  }
  return covar_matrix;
}