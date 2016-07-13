#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "matrix.h"

void help(char *program_name) {
  printf("%s -i <input_filename> - o<output_filename>\n", program_name);
}

bool parse_args(int argc, char** argv, char **input_filename, char **output_filename) {
  if (argc < 3)  
    return false;
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i+1 < argc) {
      i++;
      *input_filename = argv[i];
    }
    if (strcmp(argv[i], "-o") == 0 && i+1 < argc) {
      i++;
      *output_filename = argv[i];
    }
  }
  return true;
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  if (!parse_args(argc, argv, &input_filename, &output_filename)) {
    help(argv[0]);
    exit(-1);
  }
  FILE *fout = NULL;
  if (!(fout = fopen(output_filename,"w")))  fout = stdout;
  Matrix *m1 = NULL, *covariance;
  
  m1 = ReadMatrix(input_filename);
  covariance = Covariance(m1);
  WriteMatrix(fout, covariance);
  if (!(fout == stdout)) {
    printf("Output was written in %s\n", output_filename);
    fclose(fout);
  }

  DestroyMatrix(m1);
  DestroyMatrix(covariance);
  return 0;
}
