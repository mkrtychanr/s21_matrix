#ifndef SRC_S21_TOOLS_H_
#define SRC_S21_TOOLS_H_

#include "s21_matrix.h"

int is_valid_pointer(void *a);

int is_valid_size(matrix_t *a);

int is_valid_matrix(matrix_t *a);

int sum_and_sub(matrix_t *A, matrix_t *B, matrix_t *result, char operation);

#endif  // SRC_S21_TOOLS_H_
