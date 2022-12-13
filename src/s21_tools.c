#include "s21_tools.h"
#include <stdlib.h>

int is_valid_pointer(matrix_t *a) {
    return (a != NULL) ? SUCCESS : FAILURE;
}

int is_valid_size(matrix_t *a) {
    return (a -> rows > 0 && a -> columns > 0) ? SUCCESS : FAILURE;
}

int is_valid_matrix(matrix_t *a) {
    return (is_valid_pointer(a) == SUCCESS && is_valid_size(a) == SUCCESS) ? SUCCESS : FAILURE;
}