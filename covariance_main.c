#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define FALSE 0
#define TRUE 1

int parse_args(int argc, char** argv, char **input_filename, char **output_filename) {
  if (argc >= 2){
    *input_filename = argv[1];
    if (argc == 3)
      *output_filename = argv[2];
    return TRUE;
  }
  else {
    printf("%s <input_filename> <output_filename>\n", argv[0]);
    return FALSE;
  }
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  if (!parse_args(argc, argv, &input_filename, &output_filename))  exit(-1);
  FILE *fout = stdout;
  Matrix *m1 = NULL, *covariance;
  m1 = ReadMatrix(input_filename);

  covariance = Covariance(m1);
  printf("Covariance matrix:\n");

  if (!(output_filename == NULL)) {
    fout = fopen(output_filename,"w");
    printf("Output written in %s\n", output_filename);
  }
  WriteMatrix(fout, covariance);
  fclose(fout);
  
  return 0;
}